#pragma once

#include <signal.h>


typedef struct fool_sigs fool_sigs;
typedef struct fool_sigs_simple fool_sigs_simple;

struct fool_sigs
{
    struct sigaction sigs[NSIG];
};

struct fool_sigs_simple
{
    struct sigaction crash;
    struct sigaction stop;
    struct sigaction cont;
    struct sigaction winch;
    struct sigaction child;
    struct sigaction urg;
};


void fool_expand_signal_handlers(const sigset_t *signals, const fool_sigs_simple *simple, fool_sigs *handlers);

// Install requested signal handlers, and save the old ones in the chain.
// Note that there is no "uninstall" function, to avoid having to think
// about the case where they are uninstalled in a different order than
// they were installed. Instead, make sure your handler implementations
// are no-ops when appropriate, and also make sure you never double-install.
//
// This function cannot be used to set SIG_DFL or SIG_IGN, as chaining
// does not make sense in that case. Also, chaining probably doesn't make
// sense for SIGCHLD.
void fool_install_signal_handlers(const sigset_t *signals, const fool_sigs *handlers, fool_sigs *chain);

// Call the next signal handler in the chain.
// Note that chaining does NOT preserve special handling, so
// you probably shouldn't use this for SIGCHLD.
void fool_do_chain(siginfo_t *info, const fool_sigs *chain);

// Implementation of psiginfo that is safe to call within a signal handler.
void fool_psiginfo(const siginfo_t *info, const char *s);
//void fool_psiginfo_signalfd(const signalfd_siginfo *info, const char *s);
