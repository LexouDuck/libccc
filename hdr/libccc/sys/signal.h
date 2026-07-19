/*============================================================================*\
||                                            ______________________________  ||
||  libccc/sys/signal.h                      |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_SYS_SIGNAL_H
#define __LIBCCC_SYS_SIGNAL_H
/*!@group{libccc_sys_signal,24,libccc/sys/signal.h}
**
**	This header defines all the functions for OS signal handling.
**
**	@isostd{C,https://en.cppreference.com/w/c/program}
**
**	The signal values which can be given to the functions of this header
**	are the standard `SIG*` macro constants, defined in `<signal.h>`.
**	The ISO C standard only defines the following 6 signals (any other
**	`SIG*` constants used should be within platform-specific `#ifdef`s):
**	- `SIGABRT`: Abnormal termination (such as is initiated by the `abort()` function)
**	- `SIGFPE`:  Erroneous arithmetic operation (such as zero divide, or operation resulting in overflow)
**	- `SIGILL`:  Detection of an invalid function image (such as an invalid instruction)
**	- `SIGINT`:  Receipt of an interactive attention signal (typically, the user pressing Ctrl+C)
**	- `SIGSEGV`: An invalid access to storage (ie: a memory access violation)
**	- `SIGTERM`: A termination request sent to the program
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#ifndef __NOSTD__
	#include <signal.h>
#else
	typedef int	sig_atomic_t;
	void	(*signal(int signal, void (*handler)(int)))(int);
	int		raise(int signal);
	#define SIG_DFL	((void (*)(int)) 0)
	#define SIG_IGN	((void (*)(int)) 1)
	#define SIG_ERR	((void (*)(int))-1)
#endif

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_SYS_SIGNAL_T
#define __LIBCCC_SYS_SIGNAL_T

/*============================================================================*\
||                                  Definitions                               ||
\*============================================================================*/

//!@doc The type used to store an OS signal identifier value
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/signal}
**
**	The values stored within this type are the platform's `SIG*` macro
**	constants, defined in `<signal.h>` (see the header comment above).
*/
//!@{
typedef int	t_signal;
//!@}

//!@doc The integer type which can be accessed atomically from an asynchronous signal handler
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/sig_atomic_t}
**
**	Any global variable which is written to from within a signal handler
**	function should be declared with the type `volatile t_sigatomic`,
**	to avoid any possibility of memory-tearing during read/write.
*/
//!@{
typedef sig_atomic_t	t_sigatomic;
//!@}

//!@doc The type of a signal handler function, which can be set to handle a certain signal
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/signal}
**
**	NB: The code within a signal handler function is very restricted by the C standard:
**	it should do nothing more than write to a `volatile t_sigatomic` global variable
**	(and/or call a program termination function, such as `Program_ExitNow()`).
**
**	@param	signal	The signal value which triggered this handler (one of the `SIG*` macro constants)
*/
//!@{
typedef void	(*f_signalhandler)(int signal);
//!@}



#endif
#ifndef __LIBCCC_SYS_SIGNAL_F
#define __LIBCCC_SYS_SIGNAL_F

/*============================================================================*\
||                           Signal Handling Functions                        ||
\*============================================================================*/

//!@doc Sets the given `handler` function to be called whenever the given `signal` is raised
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/signal}
**
**	@param	signal	The signal to handle (one of the `SIG*` macro constants)
**	@param	handler	The handler function to call whenever this signal is raised
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror						Signal_SetHandler(t_signal signal, f_signalhandler handler);
#define c_signal				Signal_SetHandler
//!@}

//!@doc Resets the handling of the given `signal` back to its default behavior (ie: `SIG_DFL`)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/SIG_strategies}
**
**	@param	signal	The signal whose handling should be reset to the default (one of the `SIG*` macro constants)
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror						Signal_Reset(t_signal signal);
#define c_sigreset				Signal_Reset
#define Signal_SetHandler_Default	Signal_Reset
//!@}

//!@doc Sets the given `signal` to be ignored entirely by the program (ie: `SIG_IGN`)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/SIG_strategies}
**
**	NB: The `SIGKILL` and `SIGSTOP` signals cannot be ignored (nor handled).
**
**	@param	signal	The signal which should be ignored (one of the `SIG*` macro constants)
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror						Signal_Ignore(t_signal signal);
#define c_sigignore				Signal_Ignore
#define Signal_SetHandler_Ignore	Signal_Ignore
//!@}

//!@doc Raises the given `signal`, running its associated signal handler
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/raise}
**
**	@param	signal	The signal to raise (one of the `SIG*` macro constants)
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror						Signal_Raise(t_signal signal);
#define c_raise					Signal_Raise
//!@}

//!@doc Gets the standard name of the given `signal` (for example: `"SIGINT"`)
/*!
**	@nonstd equivalent to python `signal.Signals(x).name`, or the POSIX function `sigabbrev_np()`
**
**	@param	signal	The signal whose name should be returned (one of the `SIG*` macro constants)
**	@returns
**	A string literal containing the standard name of the given `signal`
**	(This string is a constant literal, so it should NOT be freed).
**	Returns `NULL` if the given `signal` value is unknown/invalid.
*/
//!@{
t_char const*					Signal_GetName(t_signal signal);
#define c_signame				Signal_GetName
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
