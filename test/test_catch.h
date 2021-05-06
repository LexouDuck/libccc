
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



typedef enum signal
{
	SIGNAL_NULL = 0,//!< No signal emitted by function tested
	SIGNAL_SIGTERM	= (1 << 0),	//!< Signal emitted: termination request, sent to the program
	SIGNAL_SIGSEGV	= (1 << 1),	//!< Signal emitted: invalid memory access (segmentation fault)
	SIGNAL_SIGINT	= (1 << 2),	//!< Signal emitted: external interrupt, usually initiated by the user
	SIGNAL_SIGILL	= (1 << 3),	//!< Signal emitted: invalid program image, such as invalid instruction
	SIGNAL_SIGABRT	= (1 << 4),	//!< Signal emitted: abnormal termination condition, as is e.g. initiated by abort()
	SIGNAL_SIGFPE	= (1 << 5),	//!< Signal emitted: erroneous arithmetic operation such as divide by zero
ENUMLENGTH_SIGNAL
}			e_signal;



//! global array which holds the string equivalents for the SIGNAL_ enum
extern char const*	signals[ENUMLENGTH_SIGNAL + 1];

//! global variable which stores the latest signal emitted
extern e_signal		sig;
//! global variable which stores the execution context, to restore execution after a signal
extern jmp_buf	restore;



/*
** ************************************************************************** *|
**                           Signal catching/handling                         *|
** ************************************************************************** *|
*/

void	init_segfault_handler(void);

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
	sig = setjmp(restore);				\
	if (!sig)							\

#define _CATCH \
	else								\

#ifdef __MINGW32__
#define _END \
	if (sig)							\
		signal(SIGSEGV,	signal_handler);\

#else
#define _END	;

#endif



#endif
