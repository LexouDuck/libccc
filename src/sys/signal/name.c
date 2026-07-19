
#include "libccc.h"

#ifndef __NOSTD__
	#include <signal.h>
#endif

#include "libccc/sys/signal.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char const*	Signal_GetName(t_signal sig)
{
	// NB: an if/else chain is used here (rather than a switch), because some
	// platforms define several of these SIG* macros with identical values
	// (for example: `SIGPOLL`/`SIGIO`, or `SIGABRT`/`SIGIOT`, or `SIGCHLD`/`SIGCLD`)

	// the 6 standard ISO C signals:
	if (sig == SIGABRT)	return ("SIGABRT");
	if (sig == SIGFPE)	return ("SIGFPE");
	if (sig == SIGILL)	return ("SIGILL");
	if (sig == SIGINT)	return ("SIGINT");
	if (sig == SIGSEGV)	return ("SIGSEGV");
	if (sig == SIGTERM)	return ("SIGTERM");
	// other common signals (typically POSIX), only if defined on the current platform:
#ifdef SIGALRM
	if (sig == SIGALRM)	return ("SIGALRM");
#endif
#ifdef SIGBUS
	if (sig == SIGBUS)	return ("SIGBUS");
#endif
#ifdef SIGCHLD
	if (sig == SIGCHLD)	return ("SIGCHLD");
#endif
#ifdef SIGCONT
	if (sig == SIGCONT)	return ("SIGCONT");
#endif
#ifdef SIGHUP
	if (sig == SIGHUP)	return ("SIGHUP");
#endif
#ifdef SIGKILL
	if (sig == SIGKILL)	return ("SIGKILL");
#endif
#ifdef SIGPIPE
	if (sig == SIGPIPE)	return ("SIGPIPE");
#endif
#ifdef SIGPOLL
	if (sig == SIGPOLL)	return ("SIGPOLL");
#endif
#ifdef SIGPROF
	if (sig == SIGPROF)	return ("SIGPROF");
#endif
#ifdef SIGQUIT
	if (sig == SIGQUIT)	return ("SIGQUIT");
#endif
#ifdef SIGSTOP
	if (sig == SIGSTOP)	return ("SIGSTOP");
#endif
#ifdef SIGSYS
	if (sig == SIGSYS)	return ("SIGSYS");
#endif
#ifdef SIGTRAP
	if (sig == SIGTRAP)	return ("SIGTRAP");
#endif
#ifdef SIGTSTP
	if (sig == SIGTSTP)	return ("SIGTSTP");
#endif
#ifdef SIGTTIN
	if (sig == SIGTTIN)	return ("SIGTTIN");
#endif
#ifdef SIGTTOU
	if (sig == SIGTTOU)	return ("SIGTTOU");
#endif
#ifdef SIGURG
	if (sig == SIGURG)	return ("SIGURG");
#endif
#ifdef SIGUSR1
	if (sig == SIGUSR1)	return ("SIGUSR1");
#endif
#ifdef SIGUSR2
	if (sig == SIGUSR2)	return ("SIGUSR2");
#endif
#ifdef SIGVTALRM
	if (sig == SIGVTALRM)	return ("SIGVTALRM");
#endif
#ifdef SIGWINCH
	if (sig == SIGWINCH)	return ("SIGWINCH");
#endif
#ifdef SIGXCPU
	if (sig == SIGXCPU)	return ("SIGXCPU");
#endif
#ifdef SIGXFSZ
	if (sig == SIGXFSZ)	return ("SIGXFSZ");
#endif
#ifdef SIGBREAK // (win32 only) Ctrl+Break
	if (sig == SIGBREAK)	return ("SIGBREAK");
#endif
	if CCCERROR(TRUE, ERROR_INVALIDARGS,
		"unknown signal value given: %i", sig)
		return (NULL);
	return (NULL);
}
