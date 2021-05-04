
#ifndef LIBCCC_TEST_CATCH_H
#define LIBCCC_TEST_CATCH_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include <setjmp.h>
#include <signal.h>

#include "libccc.h"



/*
** ************************************************************************** *|
**                                   Defines                                  *|
** ************************************************************************** *|
*/

/*!
**	This define is used as the 'can_segfault' arg for certain 'int' tests,
**	so as to have those tests expect a "(segfault)" result.
*/
#define SEGV	(TRUE | (1 << 2))



extern char*	nullstr;
extern char*	segstr;
extern int		segfault;
extern jmp_buf	restore;



typedef enum signal
{
	SIGNAL_NULL = 0,//!< No signal emitted by function tested
	SIGNAL_SIGTERM,	//!< Signal emitted: termination request, sent to the program
	SIGNAL_SIGSEGV,	//!< Signal emitted: invalid memory access (segmentation fault)
	SIGNAL_SIGINT,	//!< Signal emitted: external interrupt, usually initiated by the user
	SIGNAL_SIGILL,	//!< Signal emitted: invalid program image, such as invalid instruction
	SIGNAL_SIGABRT,	//!< Signal emitted: abnormal termination condition, as is e.g. initiated by abort()
	SIGNAL_SIGFPE,	//!< Signal emitted: erroneous arithmetic operation such as divide by zero
ENUMLENGTH_SIGNAL
}			e_signal;

char const*	signals[ENUMLENGTH_SIGNAL];



/*
** ************************************************************************** *|
**                           Signal catching/handling                         *|
** ************************************************************************** *|
*/

#ifdef __MINGW32__
void	signal_handler(int signaltype);
#else
struct sigaction sig;
void	signal_handler(int signaltype, siginfo_t *info, void *ptr);
#endif



/*
**	These macros are used to have signal handling/checking during tests which can crash the program
*/

#define _TRY \
	segfault = setjmp(restore);			\
	if (!segfault)						\

#define _CATCH \
	else								\

#ifdef __MINGW32__
#define _END \
	if (segfault)						\
		signal(SIGSEGV,	signal_handler);\

#else
#define _END	;

#endif



#endif
