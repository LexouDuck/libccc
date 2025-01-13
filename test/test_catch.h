
#ifndef LIBCCC_TEST_CATCH_H
#define LIBCCC_TEST_CATCH_H

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include <setjmp.h>
#include <signal.h>



/*============================================================================*\
||                                   Defines                                  ||
\*============================================================================*/

//! This integer type is used as a bitflag, to indicate whether a test expects a certain kind of failure
/*!
**	When a function is tested, it might do a segfault (#SIGSEGV), or a floating-point error (#SIGFPE).
**	Sometimes, this is expected behavior, and the test suite should reflect this.
**	Additionally, a failing test can be "benign", in the sense that we would prefer that test to
**	merely give a warning, rather than count it as a failing test.
**	This integer type is used to set all of these "testing options" when running a test.
**	@see
**	- #FLAG_SIGNAL_SIGTERM
**	- #FLAG_SIGNAL_SIGINT
**	- #FLAG_SIGNAL_SIGABRT
**	- #FLAG_SIGNAL_SIGSEGV
**	- #FLAG_SIGNAL_SIGILL
**	- #FLAG_SIGNAL_SIGFPE
**	as well as #FLAG_SIGNALMASK and #FLAG_SIGNALS
*/
typedef int	t_testflags;

//! If set, then the test in question will only issue a warning when it fails
#define FLAG_WARNING	(1 << 0)

#define FLAG_SIGTERM    (1 << 1) //!< Signal bitflag: termination request sent to the program
#define FLAG_SIGINT     (1 << 2) //!< Signal bitflag: interrupt request - usually from the user (Ctrl+C)
#define FLAG_SIGABRT    (1 << 3) //!< Signal bitflag: aborted execution - abnormal termination condition
#define FLAG_SIGSEGV    (1 << 4) //!< Signal bitflag: segmentation fault - invalid memory access/write
#define FLAG_SIGILL     (1 << 5) //!< Signal bitflag: illegal assembly instruction, or invalid program image
#define FLAG_SIGFPE     (1 << 6) //!< Signal bitflag: floating point exception - e.g. `2.0 / 0` or `sqrt(NAN)`
//! Signal bitmask: to isolate the "signal flags" part of a `t_testflags` integer
#define FLAG_SIGNALMASK \
	( FLAG_SIGTERM \
	| FLAG_SIGINT \
	| FLAG_SIGABRT \
	| FLAG_SIGSEGV \
	| FLAG_SIGILL \
	| FLAG_SIGFPE \
	)

#define ALLOW_SIGTERM    (FLAG_WARNING | FLAG_SIGTERM)
#define ALLOW_SIGINT     (FLAG_WARNING | FLAG_SIGINT)
#define ALLOW_SIGABRT    (FLAG_WARNING | FLAG_SIGABRT)
#define ALLOW_SIGSEGV    (FLAG_WARNING | FLAG_SIGSEGV)
#define ALLOW_SIGILL     (FLAG_WARNING | FLAG_SIGILL)
#define ALLOW_SIGFPE     (FLAG_WARNING | FLAG_SIGFPE)

typedef enum signal
{
	SIGNAL_NULL = 0, //!< No signal emitted by function tested
	SIGNAL_SIGTERM,	//!< Signal emitted: termination request sent to the program
	SIGNAL_SIGINT,	//!< Signal emitted: interrupt request - usually from the user (Ctrl+C)
	SIGNAL_SIGABRT,	//!< Signal emitted: aborted execution - abnormal termination condition
	SIGNAL_SIGSEGV,	//!< Signal emitted: segmentation fault - invalid memory access/write
	SIGNAL_SIGILL,	//!< Signal emitted: illegal assembly instruction, or invalid program image
	SIGNAL_SIGFPE,	//!< Signal emitted: floating point exception - e.g. `2.0 / 0` or `sqrt(NAN)`
ENUMLENGTH_SIGNAL	//!< Signal region size: amount of different signal flags, i.e. the amount of bits in #FLAG_SIGNALMASK
}	e_signal;

//! global array which holds the string equivalents for the SIGNAL_ enum
extern char const* const	signals[ENUMLENGTH_SIGNAL + 1];

//! global variable which stores the latest signal emitted
extern e_signal	sig;
//! global variable which stores the execution context, to restore execution after a signal occurred
extern jmp_buf	restore;



/*============================================================================*\
||                           Signal catching/handling                         ||
\*============================================================================*/

void	init_signal_handler(void);

#if (defined(_WIN32) || defined(__MINGW32__))
void	signal_handler(int signaltype);
#else
extern struct sigaction signal_action;
void	signal_handler(int signaltype, siginfo_t *info, void *ptr);
#endif



/*!
**	These macros are used to have signal handling/checking during tests which can crash the program
*/
//!@{
#define _TRY \
	sig = (e_signal)setjmp(restore); \
	if (sig == SIGNAL_NULL) \

#define _CATCH \
	else

#if (defined(_WIN32) || defined(__MINGW32__))
#define _END \
	if ((sig & FLAG_SIGNALMASK) != 0) \
		signal(SIGSEGV, signal_handler); \

#else
#define _END	;

#endif
//!@}



#endif
