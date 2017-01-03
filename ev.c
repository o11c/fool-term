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

#define ESC "\x1b"
#define DCS ESC"P"
#define SOS ESC"X"
#define SOS ESC"X"
#define CSI ESC"["
#define ST ESC"\\"
#define OSC ESC"]"
#define PM ESC"^"
#define APC ESC"_"

//#define ESC"[!p"ESC"[?3;4l"ESC"[4l"ESC">"
//#define RESET_STRING ESC"c"ESC"]104\a"ESC"[!p"ESC"[?3;4l"ESC"[4l"ESC">"
const char *INIT_STRING =
    "\n"
    ESC"Z"
    "\5"
    ESC" F"
    ESC"="
    DCS"$q""\"q"ST
    DCS"$q""\"p"ST
    DCS"$q""r"ST
    DCS"$q""s"ST
    DCS"$q""m"ST
    DCS"$q"" q"ST
    DCS"+q""436f;636f6c6f7273 "ST
    CSI"?1;1;S"
    CSI">0;1T"
    CSI">2;3t"
    CSI"c"
    CSI">c"
    // CSI 2/4/12/20 h
    // CSI ? Pm h
    CSI"?1004h"
    CSI"?1035l"
    CSI"?2004h"
    // CSI m
    CSI">4;2m"
    CSI"5n"
    CSI"6n"
    CSI"?6n"
    CSI"?15n"
    CSI"?25n"
    CSI"?26n"
    CSI"?53n"
    CSI"?55n"
    CSI"?56n"
    CSI"?62n"
    CSI"?63;12345n"
    CSI"?75n"
    CSI"?85n"
    CSI"$2p"
    CSI"$4p"
    CSI"$12p"
    CSI"$20p"
    CSI"?1$p"
    CSI"?2$p"
    CSI"?3$p"
    CSI"?4$p"
    CSI"?5$p"
    CSI"?6$p"
    CSI"?7$p"
    CSI"?8$p"
    CSI"?9$p"
    CSI"?10$p"
    CSI"?12$p"
    CSI"?18$p"
    CSI"?19$p"
    CSI"?25$p"
    CSI"?30$p"
    CSI"?35$p"
    CSI"?38$p"
    CSI"?40$p"
    CSI"?41$p"
    CSI"?42$p"
    CSI"?44$p"
    CSI"?45$p"
    CSI"?46$p"
    CSI"?47$p"
    CSI"?66$p"
    CSI"?67$p"
    CSI"?69$p"
    CSI"?95$p"
    CSI"?1000$p"
    CSI"?1001$p"
    CSI"?1002$p"
    CSI"?1003$p"
    CSI"?1004$p"
    CSI"?1005$p"
    CSI"?1006$p"
    CSI"?1007$p"
    CSI"?1010$p"
    CSI"?1011$p"
    CSI"?1015$p"
    CSI"?1034$p"
    CSI"?1035$p"
    CSI"?1036$p"
    CSI"?1037$p"
    CSI"?1039$p"
    CSI"?1040$p"
    CSI"?1041$p"
    CSI"?1042$p"
    CSI"?1043$p"
    CSI"?1044$p"
    CSI"?1047$p"
    CSI"?1048$p"
    CSI"?1049$p"
    CSI"?1050$p"
    CSI"?1051$p"
    CSI"?1052$p"
    CSI"?1053$p"
    CSI"?1060$p"
    CSI"?1061$p"
    CSI"?2004$p"
    CSI"11t"
    CSI"13t"
    CSI"14t"
    CSI"18t"
    CSI"19t"
    CSI"20t"
    CSI"21t"
    CSI"0x"
    CSI"1x"
    CSI"1;12345;2;3;4;5*y"
    CSI"'|"
    OSC"4;0;?"ST
    /*
    OSC"4;1;?"ST
    OSC"4;2;?"ST
    OSC"4;3;?"ST
    OSC"4;4;?"ST
    OSC"4;5;?"ST
    OSC"4;6;?"ST
    OSC"4;7;?"ST
    OSC"4;8;?"ST
    OSC"4;9;?"ST
    OSC"4;10;?"ST
    OSC"4;11;?"ST
    OSC"4;12;?"ST
    OSC"4;13;?"ST
    OSC"4;14;?"ST
    OSC"4;15;?"ST
    OSC"4;16;?"ST
    OSC"4;17;?"ST
    OSC"4;18;?"ST
    OSC"4;19;?"ST
    OSC"4;20;?"ST
    OSC"4;21;?"ST
    OSC"4;22;?"ST
    OSC"4;23;?"ST
    OSC"4;24;?"ST
    OSC"4;25;?"ST
    OSC"4;26;?"ST
    OSC"4;27;?"ST
    OSC"4;28;?"ST
    OSC"4;29;?"ST
    OSC"4;30;?"ST
    OSC"4;31;?"ST
    OSC"4;32;?"ST
    OSC"4;33;?"ST
    OSC"4;34;?"ST
    OSC"4;35;?"ST
    OSC"4;36;?"ST
    OSC"4;37;?"ST
    OSC"4;38;?"ST
    OSC"4;39;?"ST
    OSC"4;40;?"ST
    OSC"4;41;?"ST
    OSC"4;42;?"ST
    OSC"4;43;?"ST
    OSC"4;44;?"ST
    OSC"4;45;?"ST
    OSC"4;46;?"ST
    OSC"4;47;?"ST
    OSC"4;48;?"ST
    OSC"4;49;?"ST
    OSC"4;50;?"ST
    OSC"4;51;?"ST
    OSC"4;52;?"ST
    OSC"4;53;?"ST
    OSC"4;54;?"ST
    OSC"4;55;?"ST
    OSC"4;56;?"ST
    OSC"4;57;?"ST
    OSC"4;58;?"ST
    OSC"4;59;?"ST
    OSC"4;60;?"ST
    OSC"4;61;?"ST
    OSC"4;62;?"ST
    OSC"4;63;?"ST
    OSC"4;64;?"ST
    OSC"4;65;?"ST
    OSC"4;66;?"ST
    OSC"4;67;?"ST
    OSC"4;68;?"ST
    OSC"4;69;?"ST
    OSC"4;70;?"ST
    OSC"4;71;?"ST
    OSC"4;72;?"ST
    OSC"4;73;?"ST
    OSC"4;74;?"ST
    OSC"4;75;?"ST
    OSC"4;76;?"ST
    OSC"4;77;?"ST
    OSC"4;78;?"ST
    OSC"4;79;?"ST
    OSC"4;80;?"ST
    OSC"4;81;?"ST
    OSC"4;82;?"ST
    OSC"4;83;?"ST
    OSC"4;84;?"ST
    OSC"4;85;?"ST
    OSC"4;86;?"ST
    OSC"4;87;?"ST
    OSC"4;88;?"ST
    OSC"4;89;?"ST
    OSC"4;90;?"ST
    OSC"4;91;?"ST
    OSC"4;92;?"ST
    OSC"4;93;?"ST
    OSC"4;94;?"ST
    OSC"4;95;?"ST
    OSC"4;96;?"ST
    OSC"4;97;?"ST
    OSC"4;98;?"ST
    OSC"4;99;?"ST
    OSC"4;100;?"ST
    OSC"4;101;?"ST
    OSC"4;102;?"ST
    OSC"4;103;?"ST
    OSC"4;104;?"ST
    OSC"4;105;?"ST
    OSC"4;106;?"ST
    OSC"4;107;?"ST
    OSC"4;108;?"ST
    OSC"4;109;?"ST
    OSC"4;110;?"ST
    OSC"4;111;?"ST
    OSC"4;112;?"ST
    OSC"4;113;?"ST
    OSC"4;114;?"ST
    OSC"4;115;?"ST
    OSC"4;116;?"ST
    OSC"4;117;?"ST
    OSC"4;118;?"ST
    OSC"4;119;?"ST
    OSC"4;120;?"ST
    OSC"4;121;?"ST
    OSC"4;122;?"ST
    OSC"4;123;?"ST
    OSC"4;124;?"ST
    OSC"4;125;?"ST
    OSC"4;126;?"ST
    OSC"4;127;?"ST
    OSC"4;128;?"ST
    OSC"4;129;?"ST
    OSC"4;130;?"ST
    OSC"4;131;?"ST
    OSC"4;132;?"ST
    OSC"4;133;?"ST
    OSC"4;134;?"ST
    OSC"4;135;?"ST
    OSC"4;136;?"ST
    OSC"4;137;?"ST
    OSC"4;138;?"ST
    OSC"4;139;?"ST
    OSC"4;140;?"ST
    OSC"4;141;?"ST
    OSC"4;142;?"ST
    OSC"4;143;?"ST
    OSC"4;144;?"ST
    OSC"4;145;?"ST
    OSC"4;146;?"ST
    OSC"4;147;?"ST
    OSC"4;148;?"ST
    OSC"4;149;?"ST
    OSC"4;150;?"ST
    OSC"4;151;?"ST
    OSC"4;152;?"ST
    OSC"4;153;?"ST
    OSC"4;154;?"ST
    OSC"4;155;?"ST
    OSC"4;156;?"ST
    OSC"4;157;?"ST
    OSC"4;158;?"ST
    OSC"4;159;?"ST
    OSC"4;160;?"ST
    OSC"4;161;?"ST
    OSC"4;162;?"ST
    OSC"4;163;?"ST
    OSC"4;164;?"ST
    OSC"4;165;?"ST
    OSC"4;166;?"ST
    OSC"4;167;?"ST
    OSC"4;168;?"ST
    OSC"4;169;?"ST
    OSC"4;170;?"ST
    OSC"4;171;?"ST
    OSC"4;172;?"ST
    OSC"4;173;?"ST
    OSC"4;174;?"ST
    OSC"4;175;?"ST
    OSC"4;176;?"ST
    OSC"4;177;?"ST
    OSC"4;178;?"ST
    OSC"4;179;?"ST
    OSC"4;180;?"ST
    OSC"4;181;?"ST
    OSC"4;182;?"ST
    OSC"4;183;?"ST
    OSC"4;184;?"ST
    OSC"4;185;?"ST
    OSC"4;186;?"ST
    OSC"4;187;?"ST
    OSC"4;188;?"ST
    OSC"4;189;?"ST
    OSC"4;190;?"ST
    OSC"4;191;?"ST
    OSC"4;192;?"ST
    OSC"4;193;?"ST
    OSC"4;194;?"ST
    OSC"4;195;?"ST
    OSC"4;196;?"ST
    OSC"4;197;?"ST
    OSC"4;198;?"ST
    OSC"4;199;?"ST
    OSC"4;200;?"ST
    OSC"4;201;?"ST
    OSC"4;202;?"ST
    OSC"4;203;?"ST
    OSC"4;204;?"ST
    OSC"4;205;?"ST
    OSC"4;206;?"ST
    OSC"4;207;?"ST
    OSC"4;208;?"ST
    OSC"4;209;?"ST
    OSC"4;210;?"ST
    OSC"4;211;?"ST
    OSC"4;212;?"ST
    OSC"4;213;?"ST
    OSC"4;214;?"ST
    OSC"4;215;?"ST
    OSC"4;216;?"ST
    OSC"4;217;?"ST
    OSC"4;218;?"ST
    OSC"4;219;?"ST
    OSC"4;220;?"ST
    OSC"4;221;?"ST
    OSC"4;222;?"ST
    OSC"4;223;?"ST
    OSC"4;224;?"ST
    OSC"4;225;?"ST
    OSC"4;226;?"ST
    OSC"4;227;?"ST
    OSC"4;228;?"ST
    OSC"4;229;?"ST
    OSC"4;230;?"ST
    OSC"4;231;?"ST
    OSC"4;232;?"ST
    OSC"4;233;?"ST
    OSC"4;234;?"ST
    OSC"4;235;?"ST
    OSC"4;236;?"ST
    OSC"4;237;?"ST
    OSC"4;238;?"ST
    OSC"4;239;?"ST
    OSC"4;240;?"ST
    OSC"4;241;?"ST
    OSC"4;242;?"ST
    OSC"4;243;?"ST
    OSC"4;244;?"ST
    OSC"4;245;?"ST
    OSC"4;246;?"ST
    OSC"4;247;?"ST
    OSC"4;248;?"ST
    OSC"4;249;?"ST
    OSC"4;250;?"ST
    OSC"4;251;?"ST
    OSC"4;252;?"ST
    OSC"4;253;?"ST
    OSC"4;254;?"ST
    OSC"4;255;?"ST
    */
    OSC"5;0;?"ST
    OSC"5;1;?"ST
    OSC"5;2;?"ST
    OSC"5;3;?"ST
    OSC"5;4;?"ST
    OSC"10;?"ST
    OSC"11;?"ST
    OSC"12;?"ST
    OSC"13;?"ST
    OSC"14;?"ST
    OSC"15;?"ST
    OSC"16;?"ST
    OSC"17;?"ST
    OSC"18;?"ST
    OSC"19;?"ST
    "\r"ESC"[K"
;
const char *RESET_STRING =
    "\r\n"
    "\x0f"
    ESC"[m"
    ESC"(B"
    ESC"%G"
    ESC">"
    ESC" F"
    CSI">0;1;2;3T"
    //CSI"3g"
    CSI"?1004l"
    CSI"?1035h"
    CSI"?2004l"
    CSI"!p"
    CSI">4m"
    OSC"104;?"ST
    "\r"ESC"[K"
;


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
    if (strncmp(opt->term, "rxvt", 4) == 0)
        opt->csi_dollar = true;


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
    fool_write_harder(rvp->wfd, INIT_STRING, strlen(INIT_STRING));
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
    int args[16] = {};
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
        case ' ': assert (nargs == 0); return FOOL_MASK_KEYPAD | ' '; break;
        case 'A': if (nargs == 0) return FOOL_MASK_KEYPAD | FOOL_KEY_UP; break;
        case 'B': if (nargs == 0) return FOOL_MASK_KEYPAD | FOOL_KEY_DOWN; break;
        case 'C': if (nargs == 0) return FOOL_MASK_KEYPAD | FOOL_KEY_RIGHT; break;
        case 'D': if (nargs == 0) return FOOL_MASK_KEYPAD | FOOL_KEY_LEFT; break;
        case 'E': if (nargs == 0) return FOOL_MASK_KEYPAD | FOOL_KEY_BEGIN; break;
        case 'F': if (nargs == 0) return FOOL_MASK_KEYPAD | FOOL_KEY_END; break;
        case 'H': if (nargs == 0) return FOOL_MASK_KEYPAD | FOOL_KEY_HOME; break;
        case 'I': if (nargs == 0) return FOOL_MASK_KEYPAD | FOOL_KEY_TAB; break;
        case 'M': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | FOOL_KEY_ENTER; break;
        case 'P': if (nargs <= 1) return parse_mask(args[0]) | FOOL_KEY_F(1); break;
        case 'Q': if (nargs <= 1) return parse_mask(args[0]) | FOOL_KEY_F(2); break;
        case 'R': if (nargs <= 1) return parse_mask(args[0]) | FOOL_KEY_F(3); break;
        case 'S': if (nargs <= 1) return parse_mask(args[0]) | FOOL_KEY_F(4); break;
        case 'X': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | '='; break;
        case 'j': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | '*'; break;
        case 'k': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | '+'; break;
        case 'l': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | ','; break;
        case 'm': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | '-'; break;
        case 'n': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | '.'; break;
        case 'o': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | '/'; break;
        case 'p': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | '0'; break;
        case 'q': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | '1'; break;
        case 'r': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | '2'; break;
        case 's': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | '3'; break;
        case 't': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | '4'; break;
        case 'u': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | '5'; break;
        case 'v': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | '6'; break;
        case 'w': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | '7'; break;
        case 'x': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | '8'; break;
        case 'y': if (nargs <= 1) return parse_mask(args[0]) | FOOL_MASK_KEYPAD | '9'; break;
        }
        break;
    case FOOL_EVENT_OTHER_DCS:
        if (size >= 3)
        {
            if (data[0] == '0' || data[0] == '1')
            {
                // status strings reports
                // termcap/terminfo strings reports
                if (data[1] == '$' || data[1] == '+')
                {
                    if (data[2] == 'r')
                    {
                        return FOOL_EVENT_NOTHING;
                    }
                }
            }
            char *p = (char *)memchr(data, '!', size-1);
            if (p && p[1] == '~')
            {
                // memory checksum reports (whole or complete)
                return FOOL_EVENT_NOTHING;
            }
        }
        break;
    case FOOL_EVENT_OTHER_SOS:
        break;
    case FOOL_EVENT_OTHER_CSI:
        if (lib == '[' && !tib)
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
        if ((lib == '>' && nargs == 3) || (lib == '?' && nargs >= 1))
        {
            if (!tib && last == 'c')
            {
                // primary device attributes report
                // secondary device attributes report
                return FOOL_EVENT_NOTHING;
            }
        }
        if ((!lib || lib == '?') && tib == '$' && last == 'y' && nargs == 2)
        {
            // ansi mode report
            // private mode report
            return FOOL_EVENT_NOTHING;
        }
        if (((!lib && nargs == 2) || (lib == '?' && nargs >= 2 && nargs <= 3)) && last == 'R')
        {
            // collides with F3 in some modes
            if (lib || args[0] != 1)
            {
                // ansi mode report
                // private mode report
                return FOOL_EVENT_NOTHING;
            }
        }
        if (((!lib && nargs == 1) || lib == '?') && !tib && last == 'n' && nargs >= 1 && nargs <= 4)
        {
            // device status report
            return FOOL_EVENT_NOTHING;
        }
        if (!lib && tib == '*' && last == '{' && nargs == 1)
        {
            // macro space report
            return FOOL_EVENT_NOTHING;
        }
        if (!lib && !tib && last == 't' && (nargs == 1 || nargs == 3))
        {
            // window reports
            return FOOL_EVENT_NOTHING;
        }
        if (lib == '?' && !tib && last == 'S' && nargs == 3)
        {
            // sixel reports
            return FOOL_EVENT_NOTHING;
        }
        if (!lib && !tib && last == 'x' && nargs == 7)
        {
            // ??? not in xterm, but in others
            return FOOL_EVENT_NOTHING;
        }
        if (lib == '?' && last == 'x' && nargs == 0)
        {
            // ??? not in xterm, but in others
            return FOOL_EVENT_NOTHING;
        }

        if (lib || tib)
            break;

        switch (last)
        {
        case 'A': if (nargs <= 2) return parse_mask(args[args[0] == 1]) | FOOL_KEY_UP; break;
        case 'B': if (nargs <= 2) return parse_mask(args[args[0] == 1]) | FOOL_KEY_DOWN; break;
        case 'C': if (nargs <= 2) return parse_mask(args[args[0] == 1]) | FOOL_KEY_RIGHT; break;
        case 'D': if (nargs <= 2) return parse_mask(args[args[0] == 1]) | FOOL_KEY_LEFT; break;
        case 'E': if (nargs <= 2) return parse_mask(args[args[0] == 1]) | FOOL_KEY_BEGIN; break;
        case 'F': if (nargs <= 2) return parse_mask(args[args[0] == 1]) | FOOL_KEY_END; break;
        case 'H': if (nargs <= 2) return parse_mask(args[args[0] == 1]) | FOOL_KEY_HOME; break;
        case 'I': if (nargs == 0) return FOOL_EVENT_FOCUS_GAINED; break;
        case 'O': if (nargs == 0) return FOOL_EVENT_FOCUS_LOST; break;
        case 'P': if (nargs == 1 + (args[0] == 1)) return parse_mask(args[nargs - 1]) | FOOL_KEY_F(1); break;
        case 'Q': if (nargs == 1 + (args[0] == 1)) return parse_mask(args[nargs - 1]) | FOOL_KEY_F(2); break;
        case 'R': if (io->opts.csi_dollar) break; if (nargs == 1 + (args[0] == 1)) return parse_mask(args[nargs - 1]) | FOOL_KEY_F(3); break;
        case 'S': if (nargs == 1 + (args[0] == 1)) return parse_mask(args[nargs - 1]) | FOOL_KEY_F(4); break;
        case 'X': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_MASK_KEYPAD | '='; break;
        case 'j': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_MASK_KEYPAD | '*'; break;
        case 'k': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_MASK_KEYPAD | '+'; break;
        case 'l': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_MASK_KEYPAD | ','; break;
        case 'm': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_MASK_KEYPAD | '-'; break;
        case 'n': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_MASK_KEYPAD | '.'; break;
        case 'o': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_MASK_KEYPAD | '/'; break;
        case 'p': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_MASK_KEYPAD | '0'; break;
        case 'q': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_MASK_KEYPAD | '1'; break;
        case 'r': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_MASK_KEYPAD | '2'; break;
        case 's': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_MASK_KEYPAD | '3'; break;
        case 't': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_MASK_KEYPAD | '4'; break;
        case 'u':
            if (nargs != 2)
                break;
            if (args[0] == 1)
            {
                return parse_mask(args[1]) | FOOL_MASK_KEYPAD | '5';
            }
            return parse_mask(args[1]) | args[0];

        case 'v': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_MASK_KEYPAD | '6'; break;
        case 'w': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_MASK_KEYPAD | '7'; break;
        case 'x': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_MASK_KEYPAD | '8'; break;
        case 'y': if (nargs == 2 && args[0] == 1) return parse_mask(args[1]) | FOOL_MASK_KEYPAD | '9'; break;
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
            case 27:
                if (nargs == 3)
                {
                    int32_t rv = parse_mask(args[1]) | args[2];
                    if (0x20 <= args[2] && args[2] <= 0x10FFFF)
                        rv &= ~FOOL_MASK_SHIFT;
                    return rv;
                }
                break;
            case 28: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(15);
            case 29: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(16);
            case 31: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(17);
            case 32: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(18);
            case 33: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(19);
            case 34: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(20);
            case 42: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(21);
            case 43: if (nargs <= 2) return parse_mask(args[1]) | FOOL_KEY_F(22);
            case 200: if (nargs == 1) return FOOL_EVENT_PASTE_BEGIN;
            case 201: if (nargs == 1) return  FOOL_EVENT_PASTE_END;
            }
        }
        break;
    case FOOL_EVENT_OTHER_OSC:
        if (size >= 3)
        {
            if (data[0] == 'l' || data[0] == 'L')
            {
                // window and icon title reports
                return FOOL_EVENT_NOTHING;
            }
            if (data[0] == '4' && data[1] == ';')
            {
                // color palette reports
                return FOOL_EVENT_NOTHING;
            }
            if (data[0] == '1' && ('0' <= data[1] && data[1] <= '9') && data[2] == ';')
            {
                // "dynamic" colors reports
                return FOOL_EVENT_NOTHING;
            }
        }
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
            if (0x20 <= tmp && tmp <= 0x3f)
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
    case FOOL_EVENT_NOTHING:
        rv = "nothing";
        break;
    case FOOL_EVENT_EOF:
        rv = "eof";
        break;
    case FOOL_EVENT_TIMEOUT:
        rv = "timeout";
        break;
    case FOOL_EVENT_PASTE_BEGIN:
        rv = "paste_begin";
        break;
    case FOOL_EVENT_PASTE_END:
        rv = "paste_end";
        break;
    case FOOL_EVENT_FOCUS_GAINED:
        rv = "focus_gained";
        break;
    case FOOL_EVENT_FOCUS_LOST:
        rv = "focus_lost";
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
    case FOOL_KEY_BEGIN:
        rv = "begin";
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
