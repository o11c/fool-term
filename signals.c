#define _GNU_SOURCE
#include "signals.h"

#include <sys/ptrace.h>
#include <sys/uio.h>

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "util.h"


void fool_expand_signal_handlers(const sigset_t *signals, const fool_sigs_simple *simple, fool_sigs *handlers)
{
#define MAYBE_ASSIGN(sig, what)         \
    do                                  \
    {                                   \
        if (sigismember(signals, sig))  \
        {                               \
            handlers->sigs[sig] = what; \
        }                               \
    }                                   \
    while (0);
    MAYBE_ASSIGN(SIGHUP, simple->crash);
    MAYBE_ASSIGN(SIGINT, simple->crash);
    MAYBE_ASSIGN(SIGQUIT, simple->crash);
    MAYBE_ASSIGN(SIGILL, simple->crash);
    MAYBE_ASSIGN(SIGABRT, simple->crash);
    MAYBE_ASSIGN(SIGFPE, simple->crash);
    MAYBE_ASSIGN(SIGKILL, simple->crash);
    MAYBE_ASSIGN(SIGSEGV, simple->crash);
    MAYBE_ASSIGN(SIGPIPE, simple->crash);
    MAYBE_ASSIGN(SIGALRM, simple->crash);
    MAYBE_ASSIGN(SIGTERM, simple->crash);
    MAYBE_ASSIGN(SIGUSR1, simple->crash);
    MAYBE_ASSIGN(SIGUSR2, simple->crash);
    MAYBE_ASSIGN(SIGCHLD, simple->child);
    MAYBE_ASSIGN(SIGCONT, simple->cont);
    MAYBE_ASSIGN(SIGSTOP, simple->stop);
    MAYBE_ASSIGN(SIGTSTP, simple->stop);
    MAYBE_ASSIGN(SIGTTIN, simple->stop);
    MAYBE_ASSIGN(SIGTTOU, simple->stop);
    MAYBE_ASSIGN(SIGBUS, simple->crash);
    MAYBE_ASSIGN(SIGPROF, simple->crash);
    MAYBE_ASSIGN(SIGSYS, simple->crash);
    MAYBE_ASSIGN(SIGTRAP, simple->crash);
    MAYBE_ASSIGN(SIGURG, simple->urg);
    MAYBE_ASSIGN(SIGVTALRM, simple->crash);
    MAYBE_ASSIGN(SIGXCPU, simple->crash);
    MAYBE_ASSIGN(SIGXFSZ, simple->crash);
#ifdef SIGEMT
    MAYBE_ASSIGN(SIGEMT, simple->crash);
#endif
    MAYBE_ASSIGN(SIGSTKFLT, simple->crash);
    MAYBE_ASSIGN(SIGIO, simple->crash);
    MAYBE_ASSIGN(SIGPWR, simple->crash);
#ifdef SIGLOST
    MAYBE_ASSIGN(SIGLOST, simple->crash);
#endif
    MAYBE_ASSIGN(SIGWINCH, simple->winch);
    for (int sig = SIGRTMIN; sig <= SIGRTMAX; ++sig)
    {
        MAYBE_ASSIGN(sig, simple->crash);
    }
}

void fool_install_signal_handlers(const sigset_t *signals, const fool_sigs *handlers, fool_sigs *chain)
{
    for (int sig = 1; sig < NSIG; ++sig)
    {
        if (!sigismember(signals, sig))
            continue;
        if (!handlers->sigs[sig].sa_flags && !handlers->sigs[sig].sa_handler)
            continue;
        (void)sigaction(sig, &handlers->sigs[sig], &chain->sigs[sig]);
    }
}

static void raise_default(int sig)
{
    struct sigaction cur, def = {};
    def.sa_handler = SIG_DFL;
    sigset_t old, one;
    sigemptyset(&one);
    sigaddset(&one, sig);
    // Perform the default action associated with this signal.
    sigaction(sig, &def, &cur);
    pthread_sigmask(SIG_UNBLOCK, &one, &old);
    raise(sig);
    pthread_sigmask(SIG_SETMASK, &old, NULL);
    sigaction(sig, &cur, NULL);
}

void fool_do_chain(siginfo_t *info, const fool_sigs *chain)
{
    const struct sigaction *sa = &chain->sigs[info->si_signo];
    if (sa->sa_flags & SA_SIGINFO)
    {
        sigset_t old;
        pthread_sigmask(SIG_BLOCK, &sa->sa_mask, &old);
        (sa->sa_sigaction)(info->si_signo, info, NULL);
        pthread_sigmask(SIG_SETMASK, &old, NULL);
    }
    else if (sa->sa_handler == SIG_IGN)
    {
        // Do nothing!
        // If this is SIGCHLD, technically we should wait, but why
        // would you ever add a SIGCHLD handler in that case?
    }
    else if (sa->sa_handler != SIG_DFL)
    {
        sigset_t old;
        pthread_sigmask(SIG_BLOCK, &sa->sa_mask, &old);
        (sa->sa_handler)(info->si_signo);
        pthread_sigmask(SIG_SETMASK, &old, NULL);
    }
    else
    {
        raise_default(info->si_signo);
    }
}

static void put_str(char **buf, const char *s)
{
    size_t sz = strlen(s);
    memcpy(*buf, s, sz);
    *buf += sz;
}

static void put_int(char **buf, int64_t v)
{
    uint64_t uv = v;
    if (v < 0)
    {
        uv = -uv;
    }
    // no need for a \0 terminator
    char tmp[1+20];
    char *p = tmp + sizeof(tmp);
    do
    {
        *--p = '0' + (uv % 10);
        uv /= 10;
    }
    while (uv);

    if (v < 0)
    {
        *--p = '-';
    }
    size_t len = (tmp + sizeof(tmp)) - p;
    memcpy(*buf, p, len);
    *buf += len;
}

static void put_hex(char **buf, uint64_t uv)
{
    // no need for a \0 terminator
    char tmp[2+16];
    char *p = tmp + sizeof(tmp);
    do
    {
        *--p = "0123456789abcdef"[uv % 16];
        uv /= 16;
    }
    while (uv);

    *--p = 'x';
    *--p = '0';

    size_t len = (tmp + sizeof(tmp)) - p;
    memcpy(*buf, p, len);
    *buf += len;
}

static const char *ptrace_event_name(int ev)
{
    switch (ev)
    {
    case PTRACE_EVENT_FORK:
        return "PTRACE_EVENT_FORK";
    case PTRACE_EVENT_VFORK:
        return "PTRACE_EVENT_VFORK";
    case PTRACE_EVENT_CLONE:
        return "PTRACE_EVENT_CLONE";
    case PTRACE_EVENT_EXEC:
        return "PTRACE_EVENT_EXEC";
    case PTRACE_EVENT_VFORK_DONE:
        return "PTRACE_EVENT_VFORK_DONE";
    case PTRACE_EVENT_EXIT:
        return "PTRACE_EVENT_EXIT";
    case PTRACE_EVENT_SECCOMP:
        return "PTRACE_EVENT_SECCOMP";
    default:
        return NULL;
    }
}

static const char *signal_name(int si_signo)
{
    switch (si_signo)
    {
    case SIGHUP:
        return "SIGHUP";
    case SIGINT:
        return "SIGINT";
    case SIGQUIT:
        return "SIGQUIT";
    case SIGILL:
        return "SIGILL";
    case SIGABRT:
        return "SIGABRT";
    case SIGFPE:
        return "SIGFPE";
    case SIGKILL:
        return "SIGKILL";
    case SIGSEGV:
        return "SIGSEGV";
    case SIGPIPE:
        return "SIGPIPE";
    case SIGALRM:
        return "SIGALRM";
    case SIGTERM:
        return "SIGTERM";
    case SIGUSR1:
        return "SIGUSR1";
    case SIGUSR2:
        return "SIGUSR2";
    case SIGCHLD:
        return "SIGCHLD";
    case SIGCONT:
        return "SIGCONT";
    case SIGSTOP:
        return "SIGSTOP";
    case SIGTSTP:
        return "SIGTSTP";
    case SIGTTIN:
        return "SIGTTIN";
    case SIGTTOU:
        return "SIGTTOU";
    case SIGBUS:
        return "SIGBUS";

        static_assert(SIGPOLL == SIGIO, "SIGPOLL == SIGIO");
    case SIGPROF:
        return "SIGPROF";
    case SIGSYS:
        return "SIGSYS";
    case SIGTRAP:
        return "SIGTRAP";
    case SIGURG:
        return "SIGURG";
    case SIGVTALRM:
        return "SIGVTALRM";
    case SIGXCPU:
        return "SIGXCPU";
    case SIGXFSZ:
        return "SIGXFSZ";

        static_assert (SIGIOT == SIGABRT, "SIGIOT == SIGABRT");
#ifdef SIGEMT
    case SIGEMT:
        return "SIGEMT";
#endif
    case SIGSTKFLT:
        return "SIGSTKFLT";
    case SIGIO:
        return "SIGIO";

        static_assert (SIGCLD == SIGCHLD, "SIGCLD == SIGCHLD");
    case SIGPWR:
        return "SIGPWR";

#ifdef SIGINFO
        static_assert (SIGINFO == SIGPWR, "SIGINFO == SIGPWR");
#endif
#ifdef SIGLOST
    case SIGLOST:
        return "SIGLOST";
#endif
    case SIGWINCH:
        return "SIGWINCH";

        static_assert (SIGUNUSED == SIGSYS, "SIGUNUSED == SIGSYS");
    default:
        // These are not constants, but their strings are.
        if (si_signo == SIGRTMIN)
            return "SIGRTMIN";
        if (si_signo == SIGRTMAX)
            return "SIGRTMAX";
        return NULL;
    }
}

static const char *signal_code(int si_signo, int si_code)
{
    switch (si_signo)
    {
    case SIGILL:
        switch (si_code)
        {
        case ILL_ILLOPC:
            return "ILL_ILLOPC";
        case ILL_ILLOPN:
            return "ILL_ILLOPN";
        case ILL_ILLADR:
            return "ILL_ILLADR";
        case ILL_ILLTRP:
            return "ILL_ILLTRP";
        case ILL_PRVOPC:
            return "ILL_PRVOPC";
        case ILL_PRVREG:
            return "ILL_PRVREG";
        case ILL_COPROC:
            return "ILL_COPROC";
        case ILL_BADSTK:
            return "ILL_BADSTK";
        }
        break;
    case SIGFPE:
        switch (si_code)
        {
        case FPE_INTDIV:
            return "FPE_INTDIV";
        case FPE_INTOVF:
            return "FPE_INTOVF";
        case FPE_FLTDIV:
            return "FPE_FLTDIV";
        case FPE_FLTOVF:
            return "FPE_FLTOVF";
        case FPE_FLTUND:
            return "FPE_FLTUND";
        case FPE_FLTRES:
            return "FPE_FLTRES";
        case FPE_FLTINV:
            return "FPE_FLTINV";
        case FPE_FLTSUB:
            return "FPE_FLTSUB";
        }
        break;
    case SIGSEGV:
        switch (si_code)
        {
        case SEGV_MAPERR:
            return "SEGV_MAPERR";
        case SEGV_ACCERR:
            return "SEGV_ACCERR";
#ifdef SEGV_BNDERR
        case SEGV_BNDERR:
            return "SEGV_BNDERR";
#endif
#ifdef SEGV_PKUERR
        case SEGV_PKUERR:
            return "SEGV_PKUERR";
#endif
        }
        break;
    case SIGBUS:
        switch (si_code)
        {
        case BUS_ADRALN:
            return "BUS_ADRALN";
        case BUS_ADRERR:
            return "BUS_ADRERR";
        case BUS_OBJERR:
            return "BUS_OBJERR";
        case BUS_MCEERR_AR:
            return "BUS_MCEERR_AR";
        case BUS_MCEERR_AO:
            return "BUS_MCEERR_AO";
        }
        break;
    case SIGTRAP:
        switch (si_code)
        {
        case TRAP_BRKPT:
            return "TRAP_BRKPT";
        case TRAP_TRACE:
            return "TRAP_TRACE";
#ifdef TRAP_BRANCH
        case TRAP_BRANCH:
            return "TRAP_BRANCH";
#endif
#ifdef TRAP_HWBKPT
        case TRAP_HWBKPT:
            return "TRAP_HWBKPT";
#endif
        }
        break;
    case SIGCHLD:
        switch (si_code)
        {
        case CLD_EXITED:
            return "CLD_EXITED";
        case CLD_KILLED:
            return "CLD_KILLED";
        case CLD_DUMPED:
            return "CLD_DUMPED";
        case CLD_TRAPPED:
            return "CLD_TRAPPED";
        case CLD_STOPPED:
            return "CLD_STOPPED";
        case CLD_CONTINUED:
            return "CLD_CONTINUED";
        }
        break;
    case SIGIO:
        switch (si_code)
        {
        case POLL_IN:
            return "POLL_IN";
        case POLL_OUT:
            return "POLL_OUT";
        case POLL_MSG:
            return "POLL_MSG";
        case POLL_ERR:
            return "POLL_ERR";
        case POLL_PRI:
            return "POLL_PRI";
        case POLL_HUP:
            return "POLL_HUP";
        }
        break;
    case SIGSYS:
        switch (si_code)
        {
#ifdef SYS_SECCOMP
        case SYS_SECCOMP:
            return "SYS_SECCOMP";
#endif
        }
        break;
    }

    switch (si_code)
    {
    case SI_USER:
        return "SI_USER";
    case SI_KERNEL:
        return "SI_KERNEL";
    case SI_QUEUE:
        return "SI_QUEUE";
    case SI_TIMER:
        return "SI_TIMER";
    case SI_MESGQ:
        return "SI_MESGQ";
    case SI_ASYNCIO:
        return "SI_ASYNCIO";
    case SI_SIGIO:
        return "SI_SIGIO";
    case SI_TKILL:
        return "SI_TKILL";
    case SI_ASYNCNL:
        return "SI_ASYNCNL";
    default:
        return NULL;
    }
}

#ifdef __linux__
void fool_psiginfo(const siginfo_t *info, const char *s)
{
#define S(expr)     put_str(&bufp, expr)
#define I(expr)     put_int(&bufp, expr)
#define X(expr)     put_hex(&bufp, expr)
    char buf[sizeof(
            "SIGRTMIN+12345678901234567890: "
            "si_code=PTRACE_EVENT_VFORK_DONE<<8|SIGTRAP, "
            // SIGCHLD uses the most fields
            "si_pid=12345678901234567890, "
            "si_uid=12345678901234567890, "
            "si_status=12345678901234567890, "
            "si_utime=12345678901234567890, "
            "si_stime=12345678901234567890, "
    )];
    char *bufp = buf;
    const char *tmp;

    tmp = signal_name(info->si_signo);
    if (tmp)
    {
        S(tmp);
    }
    // SIGRTMIN and SIGRTMAX themselves are handled in signal_name()
    else if (SIGRTMIN < info->si_signo && info->si_signo < SIGRTMAX)
    {
        int diff_min = SIGRTMIN - info->si_signo;
        int diff_max = SIGRTMAX - info->si_signo;
        if (diff_min < diff_max)
        {
            S("SIGRTMIN+");
            I(diff_min);
        }
        else
        {
            S("SIGRTMAX-");
            I(diff_max);
        }
    }
    else
    {
        S("(SIG)");
        I(info->si_signo);
    }
    S(": ");

    S("si_code=");
    tmp = signal_code(info->si_signo, info->si_code);
    if (tmp)
    {
        S(tmp);
    }
    else if (info->si_code >= (1 << 8))
    {
        assert ((info->si_code & ~0xff00) == SIGTRAP);
        tmp = ptrace_event_name(info->si_code >> 8);
        if (tmp)
        {
            S(tmp);
        }
        else
        {
            I(info->si_code >> 8);
        }
        S("<<8|SIGTRAP");
    }
    else
    {
        I(info->si_code);
    }
    S(", ");

    switch (info->si_code)
    {
    case SI_USER:
    case SI_TKILL:
    case SI_QUEUE:
    case SI_MESGQ:
        // Note pid/uid can be falsified for SI_QUEUE/SI_MESGQ, but not SI_USER/SI_TKILL
        // (actually, there's nothing special about SI_QUEUE at all).
        S("si_pid=");
        I(info->si_pid);
        S(", ");

        S("si_uid=");
        I(info->si_uid);
        S(", ");

        if (info->si_code == SI_QUEUE || info->si_code == SI_MESGQ)
        {
            // It's impossible to know whether si_int or si_ptr is wanted.
            // On a 32-bit or little-endian system, they'll be the same,
            // and on a 64-bit big-endian system, the user can mentally
            // discard the 8 trailing zeroes.
            S("si_ptr=");
            X((uintptr_t)info->si_ptr);
            S(", ");
        }
        break;
    case SI_TIMER:
        S("si_overrun=");
        I(info->si_overrun);
        S(", ");

        S("si_timerid=");
        I(info->si_timerid);
        S(", ");
        break;
    default:
        // For ptrace-based SIGTRAPs.
        if (info->si_code >= (1 << 8))
        {
            // Here, pid/uid cannot be falsified.
            S("si_pid=");
            I(info->si_pid);
            S(", ");

            S("si_uid=");
            I(info->si_uid);
            S(", ");
        }
        if (info->si_code <= 0 || info->si_code >= 0x80)
            break;
        switch (info->si_signo)
        {
        case SIGCHLD:
            // Here, pid/uid cannot be falsified.
            S("si_pid=");
            I(info->si_pid);
            S(", ");

            S("si_uid=");
            I(info->si_uid);
            S(", ");

            S("si_status=");
            I(info->si_status);
            S(", ");

            S("si_utime=");
            I(info->si_utime);
            S(", ");

            S("si_stime=");
            I(info->si_stime);
            S(", ");
            break;
        case SIGILL:
        case SIGFPE:
        case SIGSEGV:
        case SIGBUS:
        case SIGTRAP:
            // But not ptrace-based SIGTRAPs.
            S("si_addr=");
            X((uintptr_t)info->si_addr);
            S(", ");

#ifdef si_trapno
            S("si_trapno=");
            I(info->si_trapno);
            S(", ");
#endif

            if (info->si_signo == SIGBUS)
            {
                if (info->si_code == BUS_MCEERR_AO || info->si_code == BUS_MCEERR_AR)
                {
                    S("si_addr_lsb=");
                    I(info->si_addr_lsb);
                    S(", ");
                }
            }
            if (info->si_signo == SIGSEGV)
            {
#ifdef SEGV_BNDERR
                if (info->si_code == SEGV_BNDERR)
                {
                    S("si_lower=");
                    X((uintptr_t)info->si_lower);
                    S(", ");

                    S("si_upper=");
                    X((uintptr_t)info->si_upper);
                    S(", ");
                }
#endif
#ifdef SEGV_PKUERR
                if (info->si_code == SEGV_PKUERR)
                {
                    S("si_pkey=");
                    I(info->si_pkey);
                    S(", ");
                }
#endif
            }
            break;
        case SIGIO:
            S("si_band=");
            I(info->si_band);
            S(", ");

            S("si_fd=");
            I(info->si_fd);
            S(", ");
            break;
        case SIGSYS:
            S("si_call_addr=");
            X((uintptr_t)info->si_call_addr);
            S(", ");

            S("si_syscall=");
            I(info->si_syscall);
            S(", ");

            S("si_arch=");
            I(info->si_arch);
            S(", ");

            S("si_errno=");
            I(info->si_errno);
            S(", ");
            break;
        }
        break;
    }

    assert (bufp[-2] == ',');
    assert (bufp[-1] == ' ');
    // If writing to a terminal with OPOST off, this is necessary.
    bufp[-2] = '\r';
    bufp[-1] = '\n';
    if (s && *s)
    {
        struct iovec iov[3];
        iov[0].iov_base = (char *)s;
        iov[0].iov_len = strlen(s);
        iov[1].iov_base = (char *)": ";
        iov[1].iov_len = 2;
        iov[2].iov_base = buf;
        iov[2].iov_len = bufp - buf;
        (void)fool_writev_harder(STDERR_FILENO, iov, 3);
    }
    else
    {
        (void)fool_write_harder(STDERR_FILENO, buf, bufp - buf);
    }
#undef S
#undef I
#undef X
}
#else
# error "Sorry, safe_psiginfo not implemented for your OS yet."
# error "You can probably use the Linux implementation as a guide."
#endif
