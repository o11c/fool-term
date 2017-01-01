#define _GNU_SOURCE // for asprintf
#include "ev.h"

#include <sys/ioctl.h>

#include <errno.h>
#include <poll.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "buffer.h"
#include "signals.h"
#include "util.h"

static_assert(ATOMIC_POINTER_LOCK_FREE == 2, "ATOMIC_POINTER_LOCK_FREE == 2");
static_assert(ATOMIC_INT_LOCK_FREE == 2, "ATOMIC_INT_LOCK_FREE == 2");
static_assert(ATOMIC_BOOL_LOCK_FREE == 2, "ATOMIC_BOOL_LOCK_FREE == 2");

//#define RESET_STRING "\033c\033]104\a\033[!p\033[?3;4l\033[4l\033>"
#define RESET_STRING "\r\n\x0f\x1b[m\x1b(B\x1b%G\x1b>\r\x1b[K"


// Binary compatibility is *not* needed here, since only pointers are exposed.
struct fool_io
{
    fool_fd rfd, wfd;
    fool_buffer buf;
    fool_options opts;

    struct termios rfd_termios_saved;
    struct termios wfd_termios_saved;
    bool rfd_termios_is_saved;
    bool wfd_termios_is_saved;
    int winch_counter;

    _Atomic(fool_io *) next;
    fool_io *prev;
};


static _Atomic(int) winch_counter = ATOMIC_VAR_INIT(0);
static _Atomic(bool) signals_initialized = ATOMIC_VAR_INIT(false);
static pthread_mutex_t signals_lock = PTHREAD_MUTEX_INITIALIZER;

static fool_sigs chain;

/*
    This forms a semi-lock-free semi-doubly-linked list.

    Locks are required for mutation, but only atomics are required
    to traverse the list.

    The supported operations are:
    * Insert a node at the beginning.
    * Remove an arbitrary node.
    * Iterate while inhibiting mutation.
*/
static _Atomic(fool_io *) head_link;
static pthread_mutex_t mutation_lock_actual = PTHREAD_MUTEX_INITIALIZER;
static _Atomic(int) mutation_lock_preventer = ATOMIC_VAR_INIT(0);
static sem_t mutation_lock_notifier;


static void crash_handler(int sig, siginfo_t *info, void *context)
{
    (void)sig;
    (void)context;

    (void)atomic_fetch_add(&mutation_lock_preventer, 1);
    for (fool_io *io = atomic_load(&head_link); io != NULL; io = atomic_load(&io->next))
    {
        fool_io_crash(io);
    }
    int x = atomic_fetch_add(&mutation_lock_preventer, -1);
    fool_psiginfo(info, NULL);
    fool_do_chain(info, &chain);
    if (x-1 == 0)
    {
        // In theory, we only need to do this if someone is blocked in
        // a call to sem_wait(). However, by far the most common case is
        // that fool_do_chain() will terminate the process.
        sem_post(&mutation_lock_notifier);
    }
}

static void winch_handler(int sig, siginfo_t *info, void *context)
{
    (void)sig;
    (void)info;
    (void)context;

    (void)atomic_fetch_add(&winch_counter, 1);
}

static void really_init_signals()
{
    sem_init(&mutation_lock_notifier, 0, 0U);

    fool_sigs_simple simple = {};
    fool_sigs handlers;
    sigset_t all_signals;

    sigemptyset(&simple.crash.sa_mask);
    sigemptyset(&simple.winch.sa_mask);
    sigfillset(&all_signals);

    simple.crash.sa_flags |= SA_SIGINFO;
    simple.winch.sa_flags |= SA_SIGINFO;

    simple.crash.sa_sigaction = crash_handler;
    simple.winch.sa_sigaction = winch_handler;

    fool_expand_signal_handlers(&all_signals, &simple, &handlers);
    fool_install_signal_handlers(&all_signals, &handlers, &chain);
}

static void init_signals()
{
    if (atomic_load(&signals_initialized))
        return;
    pthread_mutex_lock(&signals_lock);
    // Someone else may have acquired the mutex and initialized the mutex
    // after we did the first load and before we got the lock.
    if (atomic_load(&signals_initialized))
        goto out;
    really_init_signals();
    atomic_store(&signals_initialized, true);
out:
    pthread_mutex_unlock(&signals_lock);
}

fool_io *fool_io_open2(fool_fd rfd, fool_fd wfd, fool_options *opt, size_t opt_size)
{
    // Setup
    fool_io rv = {};
    rv.rfd = rfd;
    rv.wfd = wfd;

    opt_size = MIN(opt_size, sizeof(rv.opts));
    memset(&rv.opts, 0, sizeof(rv.opts));
    if (opt && opt_size)
        memcpy(&rv.opts, opt, opt_size);
    opt = &rv.opts;


    // Canonicalize options
    if (rfd == wfd)
    {
        opt->no_close_read |= opt->no_close_write;
        opt->no_close_write = true;
    }
    opt->no_close_read |= rfd <= 2;
    opt->no_close_write |= wfd <= 2;
    if (opt->term == NULL)
        opt->term = getenv("TERM");
    if (opt->term == NULL)
        return NULL;
    if (opt->esc_delay < -1)
        return NULL;
    if (opt->esc_delay == 0)
    {
        char *e = getenv("ESCDELAY");
        if (e && *e)
        {
            opt->esc_delay = strtol(e, &e, 10);
            if (*e)
                opt->esc_delay = 0;
            if (opt->esc_delay == 0)
                opt->esc_delay = 1000;
        }
    }
    if (0 > opt->encoding || opt->encoding >= FOOL_MAX_ENCODINGS)
        return NULL;


    // Execute operations
    if (!opt->no_signals)
    {
        init_signals();
    }
    if (!opt->no_tty_ioctl)
    {
        struct termios tios;
        rv.rfd_termios_is_saved = 0 == tcgetattr(rfd, &rv.rfd_termios_saved);
        if (!rv.rfd_termios_is_saved)
            goto error;
        if (rfd != wfd)
        {
            rv.wfd_termios_is_saved = 0 == tcgetattr(wfd, &rv.wfd_termios_saved);
            if (!rv.wfd_termios_is_saved)
                goto error;
        }

        // This is the same as cfmakeraw, but split into input and output
        // (and also conditionalized).
        tios = rv.rfd_termios_saved;
        tios.c_cc[VMIN] = !opt->nonblocking;
        tios.c_cc[VTIME] = 0;

        if (!opt->keep_input_break)
        {
            tios.c_iflag &= ~IGNBRK;
            tios.c_iflag &= ~BRKINT;
        }
        tios.c_iflag &= ~PARMRK;
        tios.c_iflag &= ~ISTRIP;
        tios.c_iflag &= ~INLCR;
        tios.c_iflag &= ~IGNCR;
        tios.c_iflag &= ~ICRNL;
        if (!opt->keep_input_xon_xoff)
        {
            tios.c_iflag &= ~IXON;
        }
        tios.c_lflag &= ~ECHO;
        tios.c_lflag &= ~ECHONL;
        tios.c_lflag &= ~ICANON;
        if (!opt->keep_input_sig)
        {
            tios.c_lflag &= ~ISIG;
        }
        tios.c_lflag &= ~IEXTEN;
        tios.c_cflag &= ~CSIZE;
        tios.c_cflag |= CS8;
        tios.c_cflag &= ~PARENB;
        if (rfd != wfd)
        {
            if (0 != tcsetattr(rfd, TCSAFLUSH, &tios))
                goto error;
            if (0 != tcgetattr(wfd, &tios))
                goto error;
        }
        // (there are other flags, but they are only checked if this is set)
        tios.c_oflag &= ~OPOST;
        if (0 != tcsetattr(rfd, TCSAFLUSH, &tios))
            goto error;
    }
    rv.winch_counter = -1;

    // Allocate and return
    fool_io *rvp = (fool_io *)memdup(&rv, sizeof(rv));
    if (!rvp)
        goto error;

    if (!opt->no_signals)
    {
        // Only adding to the head of the list. No need to worry about the
        // mutation lock being nonzero already. We *do*, however, need to
        // prevent destructors from mutating the list.
        pthread_mutex_lock(&mutation_lock_actual);
        rvp->prev = NULL;
        fool_io *head = atomic_load(&head_link);
        do
        {
            atomic_store(&rvp->next, head);
        }
        while (!atomic_compare_exchange_weak(&head_link, &head, rvp));
        if (head)
            head->prev = rvp;
        pthread_mutex_unlock(&mutation_lock_actual);
    }
    return rvp;

    // Error handler
    // (only needed for failures during the last two stages).
error:
    if (rv.wfd_termios_is_saved)
       (void)tcsetattr(wfd, TCSAFLUSH, &rv.wfd_termios_saved);
    if (rv.rfd_termios_is_saved)
       (void)tcsetattr(rfd, TCSAFLUSH, &rv.rfd_termios_saved);
    return NULL;
}

void fool_io_close(fool_io *io)
{
    if (io == NULL)
        return;
    pthread_mutex_lock(&mutation_lock_actual);
    _Atomic(fool_io *) *prev_next = io->prev ? &io->prev->next : &head_link;
    atomic_store(prev_next, atomic_load(&io->next));
    while (atomic_load(&mutation_lock_preventer) != 0)
    {
        (void)sem_wait(&mutation_lock_notifier);
    }
    pthread_mutex_unlock(&mutation_lock_actual);
    fool_io_crash(io);
    fool_buffer_clear(&io->buf);
    free(io);
}
void fool_io_crash(fool_io *io)
{
    if (io == NULL)
        return;
    if (io->wfd_termios_is_saved)
       (void)tcsetattr(io->wfd, TCSAFLUSH, &io->wfd_termios_saved);
    if (io->rfd_termios_is_saved)
       (void)tcsetattr(io->rfd, TCSAFLUSH, &io->rfd_termios_saved);

    fool_write_harder(io->wfd, RESET_STRING, strlen(RESET_STRING));

    if (!io->opts.no_close_read)
        close(io->rfd);
    if (!io->opts.no_close_write)
        close(io->wfd);
}

static int fill_buffer(fool_io *io)
{
    char buf[4096];
    ssize_t rv = read(io->rfd, buf, sizeof(buf));
    if (rv > 0)
    {
        fool_buffer_append(&io->buf, buf, buf + rv);
        return 0;
    }
    if (rv == 0)
        return FOOL_EVENT_EOF;
    switch (errno)
    {
    case EAGAIN:
#if EWOULDBLOCK != EAGAIN
    case EWOULDBLOCK:
#endif
    case EINTR:
        return FOOL_EVENT_TIMEOUT;

    // This happens if you ignore SIGHUP
    case EIO:
    // No case EPIPE: it occurs only from write(), not read().
        return FOOL_EVENT_EOF;
    default:
        perror("read");
        abort();
    }
}

static bool getb(fool_io *io, size_t offset, int32_t *out)
{
    while (!fool_buffer_has(&io->buf, offset))
    {
        // This will DTRT if io->opt.nonblocking.
        int err = fill_buffer(io);
        if (err)
        {
            *out = err;
            return false;
        }
    }
    *out = fool_buffer_at(&io->buf, offset);
    return true;
}

static int32_t low_bits(int32_t val, int bits)
{
    return val & ((1 << bits) - 1);
}

static size_t get_utf8(fool_io *io, size_t offset, int32_t *out)
{
    int32_t c[6];
#define bits (7 - n)
    int n;
    if (!getb(io, offset, &c[0]))
    {
        *out = c[0];
        return 0;
    }
    if ((c[0] & 0x80) == 0x00)
    {
        *out = c[0];
        return 1;
    }
    else if ((c[0] & 0xe0) == 0xc0)
        n = 2; // bits=5
    else if ((c[0] & 0xf0) == 0xe0)
        n = 3; // bits=4
    else if ((c[0] & 0xf8) == 0xf0)
        n = 4; // bits=3
    else if ((c[0] & 0xfc) == 0xf8)
        n = 5; // bits=2
    else if ((c[0] & 0xfe) == 0xfc)
        n = 6; // bits=1
    else
        goto utf8_error;
    for (int i = 1; i < n; ++i)
    {
        if (!getb(io, offset + i, &c[i]))
        {
            *out = c[i];
            return false;
        }
        if ((c[i] & 0xc0) != 0x80)
            goto utf8_error;
    }
    int32_t rv = low_bits(c[0], bits);
    for (int i = 1; i < n; ++i)
    {
        rv <<= 6;
        rv |= c[i] & 0x3f;
    }
    // overlong encoding
    switch (n)
    {
    case 2:
        if (rv < 0x0080)
            goto utf8_error;
        break;
    case 3:
        if (rv < 0x0800)
            goto utf8_error;
        break;
    case 4:
        if (rv < 0x00010000)
            goto utf8_error;
        break;
    case 5:
        if (rv < 0x00200000)
            goto utf8_error;
        break;
    case 6:
        if (rv < 0x04000000)
            goto utf8_error;
        break;
    }
    // unicode maximum
    if (rv > 0x10ffff)
        goto utf8_error;
    // surrogates
    if (0xd800 <= rv && rv <= 0xdfff)
        goto utf8_error;
    *out = rv;
    return n;
#undef bits
utf8_error:
    // like python errors='surrogateescape'
    *out = 0xdc00 | c[0];
    return 1;
}

static size_t get_8bit(fool_io *io, size_t offset, int32_t *out)
{
    return getb(io, offset, out);
}

static size_t get_euc(fool_io *io, size_t offset, int32_t *out)
{
    int32_t c[4];
    if (!getb(io, offset, &c[0]))
    {
        *out = c[0];
        return 0;
    }

    int n = 1;
    if (c[0] == 0x8e)
    {
        n = 4;
    }
    else if (c[0] == 0x8f)
    {
        n = 3;
    }
    else if (0xa1 <= c[0] && c[0] <= 0xfe)
    {
        n = 2;
    }
    int rv = c[0];
    for (int i = 1; i < n; ++i)
    {
        if (!getb(io, offset, &c[i]))
        {
            *out = c[i];
            return 0;
        }
        if (!(0xa1 <= c[0] && c[0] <= 0xfe))
        {
            goto euc_error;
        }
        c[0] <<= 8;
        rv |= c[i];
    }
    *out = rv;
    return n;

euc_error:
    *out = c[0];
    return 1;
}
static size_t get(fool_io *io, size_t offset, int32_t *out)
{
    // Note, in certain modes, the get_* functions are called directly.
    switch (io->opts.encoding)
    {
    case FOOL_UTF8:
        return get_utf8(io, offset, out);
    case FOOL_8BIT:
        return get_8bit(io, offset, out);
#define FOOL_EUC 2
    case FOOL_EUC:
        return get_euc(io, offset, out);
    default:
        abort();
    }
}

static bool fool_io_wait(fool_io *io, int delay)
{
    struct pollfd pfd = {};
    pfd.fd = io->rfd;
    pfd.events = POLLIN;
    int rv = poll(&pfd, 1, delay);
    return rv > 0;
}

static bool maybe_wait(fool_io *io, size_t offset)
{
    if (!fool_buffer_has(&io->buf, offset))
    {
        if (!fool_io_wait(io, io->opts.esc_delay))
            return false;
    }
    return true;
}

static void text_event(fool_io *io, fool_event *ev, size_t begin, size_t end)
{
    size_t size = end - begin;
    assert (size <= 4);
    memset(ev->utf8 + size, '\0', 4 - size);
    memcpy(ev->utf8, io->buf.begin + begin, size);
}

static int32_t parse_mask(int v)
{
    int32_t rv = 0;
    if (1 <= v && v <= 16)
    {
        v--;
        // Terminals that are aware of *some* modifier, but not which,
        // will return no mask bits. Treat that as meta to extend the
        // possible keybindings, even though it can't be combined.
        if (!v)
            return FOOL_MASK_META;
        if (v & 1) rv |= FOOL_MASK_SHIFT;
        if (v & 2) rv |= FOOL_MASK_ALT;
        if (v & 4) rv |= FOOL_MASK_CTRL;
        if (v & 8) rv |= FOOL_MASK_META;
    }
    return rv;
}

static int32_t adjust_event(fool_io *io, int32_t evb, char *data, size_t size)
{
    (void)io;
    assert (size != 0);
    char lib = '\0';
    char tib = '\0';
    char last = data[size - 1];
    int args[2] = {};
    size_t nargs = 0;
    if (evb == FOOL_EVENT_OTHER_SS3 || evb == FOOL_EVENT_OTHER_CSI)
    {
        char *tmp = data;
        if ((0x3c <= *tmp && *tmp <= 0x3f) || *tmp == '[')
            lib = *(tmp++);
        if (size >= 2 && 0x20 <= data[size - 2] && data[size - 2] <= 0x2f)
            tib = data[size - 2];
        size_t nsc = 0;
        for (size_t i = !!lib; i < size - 1 - !!tib; ++i)
        {
            nsc += data[i] == ';';
            if (data[i] == ';' || ('0' <= data[i] && data[i] <= '9'))
                continue;
            return evb;
        }
        if (nsc + 1 > sizeof(args)/sizeof(args[0]))
            return evb;
        while (nargs < sizeof(args)/sizeof(args[0]))
        {
            if (*tmp == (tib ? tib : last))
                break;
            args[nargs] = strtol(tmp, &tmp, 10);
            ++nargs;
            if (*tmp == ';')
            {
                ++tmp;
            }
            else
            {
                assert (*tmp == (tib ? tib : last));
            }
        }
    }

    switch (evb)
    {
    case FOOL_EVENT_OTHER_ISO2022:
        break;
    case FOOL_EVENT_OTHER_SS3:
        if (lib || tib)
            break;
        switch (last)
        {
        case 'A': if (nargs == 0) return FOOL_MASK_KEYPAD | FOOL_KEY_UP; break;
        case 'B': if (nargs == 0) return FOOL_MASK_KEYPAD | FOOL_KEY_DOWN; break;
        case 'C': if (nargs == 0) return FOOL_MASK_KEYPAD | FOOL_KEY_RIGHT; break;
        case 'D': if (nargs == 0) return FOOL_MASK_KEYPAD | FOOL_KEY_LEFT; break;
        case 'E': if (nargs == 0) return FOOL_MASK_KEYPAD | FOOL_KEY_CENTER; break;
        case 'F': if (nargs == 0) return FOOL_MASK_KEYPAD | FOOL_KEY_END; break;
        case 'H': if (nargs == 0) return FOOL_MASK_KEYPAD | FOOL_KEY_HOME; break;
        case 'P': if (nargs <= 1) return parse_mask(args[0]) | FOOL_KEY_F(1); break;
        case 'Q': if (nargs <= 1) return parse_mask(args[0]) | FOOL_KEY_F(2); break;
        case 'R': if (nargs <= 1) return parse_mask(args[0]) | FOOL_KEY_F(3); break;
        case 'S': if (nargs <= 1) return parse_mask(args[0]) | FOOL_KEY_F(4); break;
        case 'o': if (nargs == 0) return FOOL_MASK_KEYPAD | '/'; break;
        case 'j': if (nargs == 0) return FOOL_MASK_KEYPAD | '*'; break;
        case 'm': if (nargs == 0) return FOOL_MASK_KEYPAD | '-'; break;
        case 'k': if (nargs == 0) return FOOL_MASK_KEYPAD | '+'; break;
        case 'M': if (nargs == 0) return FOOL_MASK_KEYPAD | FOOL_KEY_ENTER; break;
        }
        break;
    case FOOL_EVENT_OTHER_DCS:
        break;
    case FOOL_EVENT_OTHER_SOS:
        break;
    case FOOL_EVENT_OTHER_CSI:
        if (lib == '[')
        {
            switch (last)
            {
            case 'A': if (nargs == 0) return FOOL_KEY_F(1); break;
            case 'B': if (nargs == 0) return FOOL_KEY_F(2); break;
            case 'C': if (nargs == 0) return FOOL_KEY_F(3); break;
            case 'D': if (nargs == 0) return FOOL_KEY_F(4); break;
            case 'E': if (nargs == 0) return FOOL_KEY_F(5); break;
            }
            break;
        }
        if (lib || tib)
            break;

        switch (last)
        {
        case 'A': if (nargs == 0 || (nargs == 2 && args[0] == 1)) return parse_mask(args[1]) | FOOL_KEY_UP; break;
        case 'B': if (nargs == 0 || (nargs == 2 && args[0] == 1)) return parse_mask(args[1]) | FOOL_KEY_DOWN; break;
        case 'C': if (nargs == 0 || (nargs == 2 && args[0] == 1)) return parse_mask(args[1]) | FOOL_KEY_RIGHT; break;
        case 'D': if (nargs == 0 || (nargs == 2 && args[0] == 1)) return parse_mask(args[1]) | FOOL_KEY_LEFT; break;
        case 'E': if (nargs == 0 || (nargs == 2 && args[0] == 1)) return parse_mask(args[1]) | FOOL_KEY_CENTER; break;
        case 'F': if (nargs == 0 || (nargs == 2 && args[0] == 1)) return parse_mask(args[1]) | FOOL_KEY_END; break;
        case 'H': if (nargs == 0 || (nargs == 2 && args[0] == 1)) return parse_mask(args[1]) | FOOL_KEY_HOME; break;
        case 'P': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_KEY_F(1); break;
        case 'Q': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_KEY_F(2); break;
        case 'R': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_KEY_F(3); break;
        case 'S': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_KEY_F(4); break;
        case 'u':
            if (nargs != 2)
                break;
            return parse_mask(args[1]) | args[0];
        case 'z':
            switch (args[0])
            {
            case 224: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(1);
            case 225: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(2);
            case 226: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(3);
            case 227: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(4);
            case 228: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(5);
            case 229: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(6);
            case 230: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(7);
            case 231: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(8);
            case 232: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(9);
            case 233: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(10);
            case 192: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(11);
            case 193: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(12);
            case 2: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_INSERT;
            case 3: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_DELETE;
            case 214: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_HOME;
            case 220: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_END;
            case 216: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_PAGEUP;
            case 222: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_PAGEDOWN;
            }
        case '@':
            if (nargs != 1)
                break;
            args[1] = 6;
            goto rxvt_mods;
        case '^':
            if (nargs != 1)
                break;
            args[1] = 5;
            goto rxvt_mods;
        case '$':
            if (nargs != 1)
                break;
            args[1] = 2;
            goto rxvt_mods;
        case '~':
        rxvt_mods:
            switch (args[0])
            {
            case 1: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_HOME;
            case 2: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_INSERT;
            case 3: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_DELETE;
            case 4: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_END;
            case 5: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_PAGEUP;
            case 6: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_PAGEDOWN;
            case 11: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(1);
            case 12: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(2);
            case 13: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(3);
            case 14: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(4);
            case 15: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(5);
            case 17: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(6);
            case 18: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(7);
            case 19: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(8);
            case 20: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(9);
            case 21: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(10);
            case 23: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(11);
            case 24: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(12);
            case 25: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(13);
            case 26: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(14);
            case 28: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(15);
            case 29: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(16);
            case 31: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(17);
            case 32: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(18);
            case 33: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(19);
            case 34: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(20);
            case 42: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(21);
            case 43: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(22);
            }
        }
        break;
    case FOOL_EVENT_OTHER_OSC:
        break;
    case FOOL_EVENT_OTHER_PM:
        break;
    case FOOL_EVENT_OTHER_APC:
        break;
    }
    return evb;
}

static void memory_event(fool_io *io, fool_event *ev, size_t begin, size_t end, bool alloc)
{
    size_t size = end - begin;
    int32_t evb = adjust_event(io, ev->basic, io->buf.begin + begin, size);
    if (evb != ev->basic)
    {
        ev->basic = evb;
        if (FOOL_EVENT_IS_TEXT(evb & FOOL_KEY_MASK))
        {
            if ((evb & FOOL_KEY_MASK) < 0x80)
            {
                ev->utf8[0] = 0x00 | ((evb >> 0) & 0x7f);
                ev->utf8[1] = 0;
                ev->utf8[2] = 0;
                ev->utf8[3] = 0;
            }
            else if ((evb & FOOL_KEY_MASK) < 0x800)
            {
                ev->utf8[0] = 0xc0 | ((evb >> 6) & 0x1f);
                ev->utf8[1] = 0x80 | ((evb >> 0) & 0x3f);
                ev->utf8[2] = 0;
                ev->utf8[3] = 0;
            }
            else if ((evb & FOOL_KEY_MASK) < 0x10000)
            {
                ev->utf8[0] = 0xe0 | ((evb >> 12) & 0x0f);
                ev->utf8[1] = 0x80 | ((evb >> 6) & 0x3f);
                ev->utf8[2] = 0x80 | ((evb >> 0) & 0x3f);
                ev->utf8[3] = 0;
            }
            else if ((evb & FOOL_KEY_MASK) < 0x00200000)
            {
                ev->utf8[0] = 0xf0 | ((evb >> 18) & 0x07);
                ev->utf8[1] = 0x80 | ((evb >> 12) & 0x3f);
                ev->utf8[2] = 0x80 | ((evb >> 6) & 0x3f);
                ev->utf8[3] = 0x80 | ((evb >> 0) & 0x3f);
            }
            else
            {
                abort();
            }
        }
        return;
    }
    if (!alloc || io->opts.no_extra)
        return;
    char *rv = (char *)malloc(size + 1);
    memcpy(rv, io->buf.begin + begin, size);
    rv[size] = '\0';
    ev->extra = rv;
}

static bool check_winch(fool_io *io, fool_event *ev)
{
    int x = atomic_load(&winch_counter);
    if (x != io->winch_counter)
    {
        io->winch_counter = x;
        ev->basic = FOOL_EVENT_WINCH;
        ev->coords[0] = 80;
        ev->coords[1] = 25;
        if (!io->opts.no_tty_ioctl)
        {
            struct winsize wsz = {};
            if (0 == ioctl(io->wfd, TIOCGWINSZ, &wsz))
            {
                ev->coords[0] = wsz.ws_col;
                ev->coords[1] = wsz.ws_row;
            }
        }
        return true;
    }
    return false;
}

int32_t fool_event_get(fool_io *io, fool_event *ev)
{
    bool force_alt = false;
    size_t offset0, offset = 0, got;
    fool_event tmp_ev;
    if (!ev)
        ev = &tmp_ev;
    memset(ev, '\0', sizeof(*ev));
    strcpy(ev->utf8, "bug");
    ev->extra = NULL;

    if (check_winch(io, ev))
        return ev->basic;

    /*
        \e [\x20-\x2f]+[\x30-\x7e]              iso 2022 (and others)
        \e P .* \e \\                           dcs
        \e X .* \e \\                           sos
        \e [ [\x20-\x3f]* [\x40–\x7e]           csi (end on $ in RXVT)
        \e ] .* \e \\                           osc (buggy for output on TERM=linux)
        \e ^ .* \e \\                           pm
        \e _ .* \e \\                           apc
        \e .                                    otherwise (excluding above)
        \e                                      only in last case
        .

        // {
        \e } .* \0                              terminology private (breaks iso 2022 GR=G2 lock)
        replace \e \\ with \a                   xterm ST

        also allow 8bit controls, including mixed ones.

        But, do *not* interpret an incomplete 8-bit control as such.
    */
    if (true)
    {
        got = get(io, offset, &ev->basic);
        if (!got)
            goto hell;
        offset += got;
    }
    if (ev->basic == '\x1b')
    {
        if (!maybe_wait(io, offset))
            goto esc_timeout;
        got = get(io, offset, &ev->basic);
        if (!got)
            goto hell;
        if (ev->basic == '\x1b')
        {
            offset += got;
            force_alt = true;
        }
        else
        {
            text_event(io, ev, offset, offset+got);
            ev->basic = '\x1b';
            got = 1;
            goto no_text;
        }
    }

    // TODO fix this!
    assert (got <= 4);
    if (0x00 <= ev->basic && ev->basic <= 0x1f)
        goto no_text;
    if (0x7f <= ev->basic && ev->basic <= 0x9f)
        goto no_text;
    if (0xdc80 <= ev->basic && ev->basic <= 0xdc9f)
        goto no_text;
    text_event(io, ev, offset-got, offset);

no_text:
    if (io->opts.no_c1)
    {
        if (0x80 <= ev->basic && ev->basic <= 0x9f)
            goto esc_timeout;
        if (0xdc80 <= ev->basic && ev->basic <= 0xdc9f)
            goto esc_timeout;
    }

    offset0 = offset;
    switch (ev->basic)
    {
    case '\x1b':
        // if (!force_alt), we have already waited.
        if (force_alt && !maybe_wait(io, offset))
            goto esc_timeout;
        got = get(io, offset, &ev->basic);
        if (!got)
            goto hell;
        offset += got;
        switch (ev->basic)
        {
        case 0x20 ... 0x2f:
            if (force_alt)
                goto esc_error;
            ev->basic = FOOL_EVENT_OTHER_ISO2022;
            while (true)
            {
                int tmp;
                got = get(io, offset, &tmp);
                if (!got)
                {
                    ev->basic = tmp;
                    goto hell;
                }
                offset += got;
                if (0x20 <= tmp && tmp <= 0x2f)
                    continue;
                if (0x30 <= tmp && tmp <= 0x7e)
                {
                    memory_event(io, ev, offset0, offset, ev != &tmp_ev);
                    goto ret;
                }
                goto esc_error;
            }
        case 'O':
            goto ss3;
        case 'P':
            if (force_alt)
                goto esc_error;
            if (!maybe_wait(io, offset))
                break;
            goto dcs;
        case 'X':
            if (force_alt)
                goto esc_error;
            if (!maybe_wait(io, offset))
                break;
            goto sos;
        case '[':
            // Here is where force_alt is *wanted*.
            if (!maybe_wait(io, offset))
                break;
            goto csi;
        case ']':
            if (force_alt)
                goto esc_error;
            if (!maybe_wait(io, offset))
                break;
            goto osc;
        case '^':
            if (force_alt)
                goto esc_error;
            if (!maybe_wait(io, offset))
                break;
            goto pm;
        case '_':
            if (force_alt)
                goto esc_error;
            if (!maybe_wait(io, offset))
                break;
            goto apc;
        }
        force_alt = true;
        break;
    case 0x8f:
    case 0xdc8f:
    ss3:
        if (io->opts.no_ss3 || !maybe_wait(io, offset))
            goto esc_timeout;
        ev->basic = FOOL_EVENT_OTHER_SS3;
        goto finish_csi;
    case 0x90:
        if (!maybe_wait(io, offset))
            goto esc_timeout;
    case 0xdc90:
    dcs:
        ev->basic = FOOL_EVENT_OTHER_DCS;
        goto want_st;
    case 0x98:
        if (!maybe_wait(io, offset))
            goto esc_timeout;
    case 0xdc98:
    sos:
        ev->basic = FOOL_EVENT_OTHER_SOS;
        goto want_st;
    case 0x9b:
        if (!maybe_wait(io, offset))
            goto esc_timeout;
    case 0xdc9b:
    csi:
        ev->basic = FOOL_EVENT_OTHER_CSI;
        goto finish_csi;
    case 0x9d:
        if (!maybe_wait(io, offset))
            goto esc_timeout;
    case 0xdc9d:
    osc:
        ev->basic = FOOL_EVENT_OTHER_OSC;
        goto want_st;
    case 0x9e:
        if (!maybe_wait(io, offset))
            goto esc_timeout;
    case 0xdc9e:
    pm:
        ev->basic = FOOL_EVENT_OTHER_PM;
        goto want_st;
    case 0x9f:
        if (!maybe_wait(io, offset))
            goto esc_timeout;
    case 0xdc9f:
    apc:
        ev->basic = FOOL_EVENT_OTHER_APC;
        goto want_st;
    default:
        break;
    }

    if (false)
    {
        // This label is reached:
        // * when encountering any of the 3 forms of CSI
        // * when encountering any of the 3 forms of SS3, if enabled
    finish_csi:
        offset0 = offset;
        while (true)
        {
            int tmp;
            got = get(io, offset, &tmp);
            if (!got)
            {
                ev->basic = tmp;
                goto hell;
            }
            offset += got;
            // Break on the first iteration if SS3 shouldn't take arguments.
            if (ev->basic == FOOL_EVENT_OTHER_SS3 && io->opts.no_long_ss3)
            {
                memory_event(io, ev, offset0, offset, ev != &tmp_ev);
                break;
            }
            if (ev->basic == FOOL_EVENT_OTHER_CSI && io->opts.csi_dollar && tmp == '$')
            {
                memory_event(io, ev, offset0, offset, ev != &tmp_ev);
                break;
            }
            if (tmp == '[' && !io->opts.no_csi_lsqb)
                continue;
            if (0x30 <= tmp && tmp <= 0x3f)
                continue;
            if (0x40 <= tmp && tmp <= 0x7e)
            {
                memory_event(io, ev, offset0, offset, ev != &tmp_ev);
                break;
            }
            goto esc_error;
        }
    }

    if (false)
    {
        // This label is reached:
        // * when encountering any of the 3 forms of DCS, SOS, OSC, PM, APC
    want_st:
        // ev->basic is already set
        offset0 = offset;
        while (true)
        {
            // We want to omit the terminator, so use the old offset.
            size_t offset1 = offset;
            int tmp;
            got = get(io, offset, &tmp);
            if (!got)
            {
                ev->basic = tmp;
                goto hell;
            }
            offset += got;
            if (!io->opts.no_osc_bel && tmp == '\a' && ev->basic == FOOL_EVENT_OTHER_OSC)
            {
                memory_event(io, ev, offset0, offset1, ev != &tmp_ev);
                break;
            }
            if (tmp == 0x9c || tmp == 0xdc9c)
            {
                if (io->opts.no_c1)
                    continue;
                memory_event(io, ev, offset0, offset1, ev != &tmp_ev);
                break;
            }
            if (tmp == 0x1b)
            {
                got = get(io, offset, &tmp);
                if (!got)
                {
                    ev->basic = tmp;
                    goto hell;
                }
                offset += got;
                if (tmp != '\\')
                    goto esc_error;
                memory_event(io, ev, offset0, offset1, ev != &tmp_ev);
                break;
            }
            if (0x00 <= tmp && tmp <= 0x1f)
                goto esc_error;
            if (0x80 <= tmp && tmp <= 0x9f)
                goto esc_error;
            if (0xdc80 <= tmp && tmp <= 0xdc9f)
                goto esc_error;
            continue;
        }
    }

    if (false)
    {
        // This label is reached:
        // * if esc preceded an escape sequence that does not allow alt
        // * whenever an escape sequence hits an invalid character
    esc_error:
        ev->basic = '\x1b';
        // Do not change force_alt.
        offset = 1;
    }

    if (false)
    {
        // This label is reached:
        // * after timing out \e
        // * after timing out \e \e
        // * after timing out any *encoded* C1 control
        // * if interpreting raw C1 controls are disabled but one is seen
    esc_timeout:
        ;
    }

    // It's possible that a wait failed because we got SIGWINCH.
    // In this case, retrying will likely work.
    // TODO - is this actually reachable, or do they all goto hell?
    if (check_winch(io, ev))
        return ev->basic;

    if (force_alt)
    {
        ev->basic |= FOOL_MASK_ALT;
    }
    if (0x80 <= (ev->basic & FOOL_KEY_MASK) && (ev->basic & FOOL_KEY_MASK) <= (io->opts.force_meta ? 0xff : io->opts.no_c1 ? 0x7f : 0x9f))
    {
        ev->basic &= ~0x80;
        ev->basic |= FOOL_MASK_META;
    }
    switch (ev->basic & FOOL_KEY_MASK)
    {
    case '\x1b': // ^[
        ev->basic = (ev->basic&~FOOL_KEY_MASK) | FOOL_KEY_ESC;
        break;
    case '\t': // ^I
        ev->basic = (ev->basic&~FOOL_KEY_MASK) | FOOL_KEY_TAB;
        break;
    case '\r': // ^M
        ev->basic = (ev->basic&~FOOL_KEY_MASK) | FOOL_KEY_ENTER;
        break;
    case '\x7f': // ^?
        ev->basic = (ev->basic&~FOOL_KEY_MASK) | FOOL_KEY_BACKSPACE;
        break;
    default:
        if ((ev->basic & FOOL_KEY_MASK) < 0x20)
        {
            ev->basic += 0x40;
            ev->utf8[0] = ev->basic & 0x7f;
            ev->utf8[1] = 0;
            ev->utf8[2] = 0;
            ev->utf8[3] = 0;
            ev->basic |= FOOL_MASK_CTRL;
        }
    }
ret:
    fool_buffer_cut(&io->buf, offset);
    return ev->basic;
hell:
    (void)check_winch(io, ev);
    return ev->basic;
}

const char *fool_event_string(fool_io *io, fool_event *ev, int variant)
{
    (void)io;
    (void)variant;
    const char *rv = NULL;
    int32_t evb = ev->basic;

    const char *keypad = evb & FOOL_MASK_KEYPAD ? "K-" : "";
    const char *shift = evb & FOOL_MASK_SHIFT ? "S-" : "";
    const char *alt = evb & FOOL_MASK_ALT ? "A-" : "";
    const char *ctrl = evb & FOOL_MASK_CTRL ? "C-" : "";
    const char *meta = evb & FOOL_MASK_META ? "M-" : "";
    const char *lmb = evb & FOOL_MASK_LMB ? "1-" : "";
    const char *mmb = evb & FOOL_MASK_MMB ? "2-" : "";
    const char *rmb = evb & FOOL_MASK_RMB ? "3-" : "";
    assert ((evb & ~FOOL_MOD_MASK) == (evb & FOOL_KEY_MASK));
    evb &= FOOL_KEY_MASK;
    char fn[13] = "";
    char *fnp = fn;
    switch (evb)
    {
    case FOOL_EVENT_EOF:
        rv = "eof";
        break;
    case FOOL_EVENT_TIMEOUT:
        rv = "timeout";
        break;
    case FOOL_EVENT_WINCH:
        rv = "winch\u00a0";
        sprintf(fn, "%hux%hu", ev->coords[0], ev->coords[1]);
        break;
    case FOOL_EVENT_OTHER_ISO2022:
        rv = "other-iso2022\u00a0";
        fnp = (char *)ev->extra;
        break;
    case FOOL_EVENT_OTHER_SS3:
        rv = "other-ss3\u00a0";
        fnp = (char *)ev->extra;
        break;
    case FOOL_EVENT_OTHER_DCS:
        rv = "other-dcs\u00a0";
        fnp = (char *)ev->extra;
        break;
    case FOOL_EVENT_OTHER_SOS:
        rv = "other-sos\u00a0";
        fnp = (char *)ev->extra;
        break;
    case FOOL_EVENT_OTHER_CSI:
        rv = "other-csi\u00a0";
        fnp = (char *)ev->extra;
        break;
    case FOOL_EVENT_OTHER_OSC:
        rv = "other-osc\u00a0";
        fnp = (char *)ev->extra;
        break;
    case FOOL_EVENT_OTHER_PM:
        rv = "other-pm\u00a0";
        fnp = (char *)ev->extra;
        break;
    case FOOL_EVENT_OTHER_APC:
        rv = "other-apc\u00a0";
        fnp = (char *)ev->extra;
        break;

    case FOOL_KEY_ESC:
        rv = "escape";
        break;
    case FOOL_KEY_TAB:
        rv = "tab";
        break;
    case FOOL_KEY_ENTER:
        rv = "enter";
        break;
    case FOOL_KEY_BACKSPACE:
        rv = "backspace";
        break;
    case FOOL_KEY_INSERT:
        rv = "insert";
        break;
    case FOOL_KEY_DELETE:
        rv = "delete";
        break;
    case FOOL_KEY_HOME:
        rv = "home";
        break;
    case FOOL_KEY_END:
        rv = "end";
        break;
    case FOOL_KEY_PAGEUP:
        rv = "pageup";
        break;
    case FOOL_KEY_PAGEDOWN:
        rv = "pagedown";
        break;
    case FOOL_KEY_UP:
        rv = "up";
        break;
    case FOOL_KEY_DOWN:
        rv = "down";
        break;
    case FOOL_KEY_RIGHT:
        rv = "right";
        break;
    case FOOL_KEY_LEFT:
        rv = "left";
        break;
    case FOOL_KEY_CENTER:
        rv = "center";
        break;
    case ' ':
        rv = "space";
        break;
    default:
        if (FOOL_EVENT_IS_TEXT(evb))
        {
            rv = ev->utf8;
            free(ev->extra);
            ev->extra = NULL;
        }
        else if (evb >= FOOL_KEY_F0)
        {
            rv = "f";
            sprintf(fn, "%d", evb - FOOL_KEY_F0);
        }
        else
        {
            rv = "unknown-key-this-is-a-bug";
        }
    }
    if (ev->basic >= FOOL_KEY_ALLOC)
    {
        if (fnp == fn)
        {
            free(ev->extra);
        }
        ev->extra = NULL;
        (void)asprintf((char **)&ev->extra,
            "%s"
            "%s%s%s%s"
            "%s%s%s"
            "%s%s",
            keypad,
            shift, alt, ctrl, meta,
            lmb, mmb, rmb,
            rv, fnp
        );
        if (fnp != fn)
        {
            free(fnp);
        }
        rv = (char *)ev->extra;
        if (rv == NULL)
        {
            rv = "memory-allocation-failure";
        }
    }
    return rv;
}

void fool_event_free(fool_io *io, fool_event *ev)
{
    (void)io;
    free(ev->extra);
    ev->extra = NULL;
}
