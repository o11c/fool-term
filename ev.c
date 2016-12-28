#define _GNU_SOURCE // for asprintf
#include "ev.h"

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
    simple.crash.sa_sigaction = winch_handler;

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
    if (opt->esc_delay < -1)
        return NULL;
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
    if (!io->opts.no_close_read)
        close(io->rfd);
    if (!io->opts.no_close_write)
        close(io->wfd);
}

static bool fill_buffer(fool_io *io)
{
    char buf[4096];
    ssize_t rv = read(io->rfd, buf, sizeof(buf));
    if (rv > 0)
        fool_buffer_append(&io->buf, buf, buf + rv);
    return rv > 0;
}

int32_t fool_event_get(fool_io *io, fool_event *ev)
{
    fool_event tmp;
    if (!ev)
        ev = &tmp;
    memset(ev, '\0', sizeof(*ev));
    strcpy(ev->utf8, "bug");

    size_t sz = fool_buffer_size(&io->buf);

    if (!sz && !fill_buffer(io))
    {
        ev->basic = FOOL_EVENT_EOF;
        return ev->basic;
    }

    ev->basic = (uint8_t)fool_buffer_at(&io->buf, 0);
    fool_buffer_cut(&io->buf, 1);

    if (ev->basic & 0x80)
    {
        ev->basic &= ~0x80;
        ev->basic |= FOOL_MASK_META;
    }
    switch (ev->basic & 0x7f)
    {
    case '\x1b':
        ev->basic = FOOL_KEY_ESC;
        break;
    case '\t':
        ev->basic = FOOL_KEY_TAB;
        break;
    case '\r':
        ev->basic = FOOL_KEY_ENTER;
        break;
    case '\x7f':
        // ev->basic = FOOL_MASK_CTRL | (ev->basic - 0x40);
        ev->basic = FOOL_KEY_BACKSPACE;
        break;
    default:
        if ((ev->basic & 0x7f) < 0x20)
        {
            ev->basic += 0x40;
            ev->utf8[0] = ev->basic & 0x7f;
            ev->utf8[1] = 0;
            ev->utf8[2] = 0;
            ev->utf8[3] = 0;
            ev->basic |= FOOL_MASK_CTRL;
        }
        else
        {
            ev->utf8[0] = ev->basic & 0x7f;
            ev->utf8[1] = 0;
            ev->utf8[2] = 0;
            ev->utf8[3] = 0;
        }
    }
    return ev->basic;
}

const char *fool_event_string(fool_io *io, fool_event *ev, int variant)
{
    (void)io;
    (void)variant;
    const char *rv = NULL;
    int32_t evb = ev->basic;

    if (FOOL_EVENT_IS_SPECIAL(evb))
    {
        switch (evb)
        {
        case FOOL_EVENT_EOF:
            return "eof";
        case FOOL_EVENT_TIMEOUT:
            return "timeout";
        default:
            return "unknown-special-this-is-a-bug";
        }
    }

    const char *shift = evb & FOOL_MASK_SHIFT ? "S-" : "";
    const char *alt = evb & FOOL_MASK_ALT ? "A-" : "";
    const char *ctrl = evb & FOOL_MASK_CTRL ? "C-" : "";
    const char *meta = evb & FOOL_MASK_META ? "M-" : "";
    const char *lmb = evb & FOOL_MASK_LMB ? "1-" : "";
    const char *mmb = evb & FOOL_MASK_MMB ? "2-" : "";
    const char *rmb = evb & FOOL_MASK_RMB ? "3-" : "";
    assert ((evb & ~FOOL_MOD_MASK) == (evb & FOOL_KEY_MASK));
    evb &= FOOL_KEY_MASK;
    char fn[10] = "";
    switch (evb)
    {
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
        free(ev->extra);
        ev->extra = NULL;
        (void)asprintf((char **)&ev->extra,
            "%s%s%s%s"
            "%s%s%s"
            "%s%s",
            shift, alt, ctrl, meta,
            lmb, mmb, rmb,
            rv, fn
        );
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
