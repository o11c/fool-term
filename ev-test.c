#include "ev.h"

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include "signals.h"
#include "util.h"


static fool_sigs chain;

// TODO integrate this into the library proper
// the problem is that we should handle *multiple* fool_ios
static fool_io *io_for_cleanup = NULL;
static void crash_handler(int sig, siginfo_t *info, void *context)
{
    (void)sig;
    (void)context;
    fool_io_crash(io_for_cleanup);
    fool_psiginfo(info, NULL);
    fool_do_chain(info, &chain);
}

static void do_signals()
{
    struct sigaction act = {};
    act.sa_sigaction = crash_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_flags |= SA_SIGINFO;

    sigset_t all_signals;

    fool_sigs_simple simple = {};
    fool_sigs handlers;

    sigfillset(&all_signals);
    simple.crash = act;
    fool_expand_signal_handlers(&all_signals, &simple, &handlers);
    fool_install_signal_handlers(&all_signals, &handlers, &chain);
}

int main(int argc, char **argv)
{
    unsigned alarm_time = 5;

    if (argc != 1)
    {
        printf("Usage: %s takes no arguments\n", argv[0]);
        return 1;
    }

    printf("Program will exit after %d seconds of inactivity\n", alarm_time);
    do_signals();

    fool_options opts = {};
    fool_io *io = fool_io_open2(STDIN_FILENO, STDOUT_FILENO, &opts, sizeof(opts));
    if (!io)
    {
        printf("Failed to open terminal!\n");
        return 2;
    }
    io_for_cleanup = io;

    fool_event ev;
    while (alarm(alarm_time), fool_event_get(io, &ev) != FOOL_EVENT_EOF)
    {
        printf("(0x%08x) -> %s\r\n", ev.basic, fool_event_string(io, &ev, 0));
        fool_event_free(io, &ev);
    }

    fool_io_close(io);
}
