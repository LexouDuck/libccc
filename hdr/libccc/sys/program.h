/*============================================================================*\
||                                            ______________________________  ||
||  libccc/sys/program.h                     |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_SYS_PROGRAM_H
#define __LIBCCC_SYS_PROGRAM_H
/*!@group{libccc_sys_program,24,libccc/sys/program.h}
**
**	This header defines all the functions for OS-level input/output, read/write.
**
**	@isostd{C,https://en.cppreference.com/w/c/program}
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#ifndef __NOSTD__
	#include <stdlib.h>
	#include <setjmp.h>
#else
	#define EXIT_SUCCESS	(OK)
	#define EXIT_FAILURE	(ERROR)
	typedef long	jmp_buf[64]; // opaque fallback definition (platform-dependent)
	int		setjmp(jmp_buf context);
	void	longjmp(jmp_buf context, int status);
#endif

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_SYS_PROGRAM_T
#define __LIBCCC_SYS_PROGRAM_T

/*============================================================================*\
||                                  Definitions                               ||
\*============================================================================*/

//!@doc The type used to store a program execution context, for non-local jumps
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/jmp_buf}
**
**	This type stores the calling environment/context of the program
**	(as saved by Program_SaveContext(), for Program_RestoreContext()
**	to jump back to at a later point in the program execution).
*/
//!@{
typedef jmp_buf	t_jmpbuf;
//!@}



#endif
#ifndef __LIBCCC_SYS_PROGRAM_F
#define __LIBCCC_SYS_PROGRAM_F

/*============================================================================*\
||                           Common Program Utilities                         ||
\*============================================================================*/

//!@doc Terminates the program abnormally, without any cleanup (wrapper for `abort()`)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/abort}
*/
//!@{
_NORETURN()
void				Program_Abort(void);
#define c_abort		Program_Abort
//!@}



//!@doc Terminates the program normally, performing the usual cleanup (calls `atexit()` handlers, flushes and closes streams)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/exit}
*/
//!@{
_NORETURN()
void				Program_Exit(int exit_code);
#define c_exit		Program_Exit
//!@}



//!@doc Registers the given function `f` to be called upon normal program termination
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/atexit}
*/
//!@{
e_cccerror			Program_OnExit(void (*f)(void));
#define c_atexit	Program_OnExit
#define c_onexit	Program_OnExit
//!@}



//!@doc Terminates the program immediately, without any cleanup (skips `atexit()` handlers, does not flush streams)
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/program/_Exit}
**
**	@nonstd equivalent to python `os._exit()`
**
**	@param	exit_code	The exit status code to return to the host environment
*/
//!@{
_NORETURN()
void					Program_ExitNow(int exit_code);
#define c_exitnow	Program_ExitNow
//!@}



//!@doc Terminates the program "quickly": calls the functions registered with Program_OnExitQuick(), but performs no other cleanup
/*!
**	@isostd{C11,https://en.cppreference.com/w/c/program/quick_exit}
**
**	NB: On platforms where the C11 `quick_exit()` function is not available,
**	this function behaves like Program_ExitNow() (ie: `_Exit()`).
**
**	@param	exit_code	The exit status code to return to the host environment
*/
//!@{
_NORETURN()
void						Program_ExitQuick(int exit_code);
#define c_quick_exit	Program_ExitQuick
//!@}



//!@doc Registers the given function `f` to be called upon Program_ExitQuick() invocation
/*!
**	@isostd{C11,https://en.cppreference.com/w/c/program/at_quick_exit}
**
**	NB: On platforms where the C11 `at_quick_exit()` function is not
**	available, this function does nothing, and returns an error.
**
**	@param	f	The function to call during "quick exit" program termination
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror					Program_OnExitQuick(void (*f)(void));
#define c_at_quick_exit	Program_OnExitQuick
//!@}



//!@doc Marks a point of the program's control flow as being unreachable (this is an optimization hint for the compiler)
/*!
**	@isostd{C23,https://en.cppreference.com/w/c/program/unreachable}
**
**	NB: If the point marked with this macro function is, in fact, reached
**	during program execution, then the behavior is undefined. As such, this
**	should only ever be used when the point is truly logically unreachable.
*/
//!@{
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L)
#define Program_Unreachable()	unreachable()
#elif defined(__GNUC__)
#define Program_Unreachable()	__builtin_unreachable()
#elif defined(_MSC_VER)
#define Program_Unreachable()	__assume(0)
#else
#define Program_Unreachable()	((void)0)
#endif
#define c_unreachable	Program_Unreachable
//!@}



/*============================================================================*\
||                               Non-local Jumps                              ||
\*============================================================================*/

//!@doc Saves the current program execution context into the given `context` buffer (for a later non-local jump)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/setjmp}
**
**	NB: This must be implemented as a macro (rather than a wrapper function),
**	because the C standard requires `setjmp()` to be called directly within
**	the stack frame which will later be jumped back to.
**
**	@param	context	The #t_jmpbuf buffer in which to save the current execution context
**	@returns
**	`0` when returning directly (ie: after having just saved the context),
**	or the (necessarily non-zero) `status` value given to Program_RestoreContext(),
**	when returning as the result of a non-local jump back to this point.
*/
//!@{
#define Program_SaveContext(context)	setjmp(context)
#define c_setjmp	Program_SaveContext
//!@}

//!@doc Performs a non-local jump: restores the program execution context saved in the given `context` buffer
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/longjmp}
**
**	NB: The function which called Program_SaveContext() on this `context`
**	must not have finished executing (ie: its stack frame must still be
**	active), otherwise the behavior is undefined.
**
**	@param	context	The #t_jmpbuf execution context to jump back to (as saved by Program_SaveContext())
**	@param	status	The status value which the corresponding Program_SaveContext() call will return
**					(NB: if `0` is given here, the value returned there will be `1` instead)
*/
//!@{
_NORETURN()
void					Program_RestoreContext(t_jmpbuf context, int status);
#define c_longjmp	Program_RestoreContext
//!@}



//!@doc Runs the given terminal `command`, using the host environment's command processor
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/system}
*/
//!@{
e_cccerror			Program_Run(t_char const* command);
#define c_system	Program_Run
//!@}



//!@doc Gets the value of the environment variable with the given `name`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/getenv}
**
**	NB: Unlike a raw `getenv()` call, the string returned by this function is
**	a newly allocated duplicate (so, it must be freed), which makes it safe to
**	use regardless of any future calls to `setenv()`/`putenv()`/`getenv()`.
**
**	@param	name	The name of the environment variable to get
**	@returns
**	A newly allocated string containing the value of the environment variable
**	with the given `name`, or `NULL` if no such environment variable exists.
*/
//!@{
t_char*				Program_GetEnv(t_char const* name);
#define c_getenv	Program_GetEnv
//!@}

//!@doc Sets the value of the environment variable with the given `name`
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/setenv}
*/
//!@{
e_cccerror			Program_SetEnv(t_char const* name, t_char const* value, t_bool overwrite);
#define c_setenv	Program_SetEnv
//!@}

//!@doc Deletes the environment variable with the given `name`
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/unsetenv}
**
**	@nonstd equivalent to python `os.environ.pop()`, C# `Environment.SetEnvironmentVariable(name, null)`
**
**	NB: If no environment variable with the given `name` exists, this
**	function does nothing, and returns #ERROR_NONE.
**
**	@param	name	The name of the environment variable to delete
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror			Program_UnsetEnv(t_char const* name);
#define c_unsetenv	Program_UnsetEnv
//!@}



//!@doc Gets the current working directory of the program
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/getcwd}
*/
//!@{
t_char*				Program_GetCWD(void);
#define c_getcwd	Program_GetCWD
//!@}

//!@doc Changes the current working directory of the program, to the given `path`
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/chdir}
**
**	@nonstd equivalent to python `os.chdir()`, C# `Directory.SetCurrentDirectory()`, node.js `process.chdir()`
**
**	@param	path	The path of the directory to set as the new current working directory
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror			Program_SetCWD(t_char const* path);
#define c_chdir		Program_SetCWD
#define c_setcwd	Program_SetCWD
//!@}



//!@doc Gets the process identifier (PID) of the currently running program
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/getpid}
**
**	@nonstd equivalent to python `os.getpid()`, C# `Environment.ProcessId`, node.js `process.pid`
**
**	@returns
**	The unique process identifier (PID) of the currently running program.
*/
//!@{
t_sint				Program_GetPID(void);
#define c_getpid	Program_GetPID
//!@}



//!@doc Gets the absolute filesystem path of the currently running program's executable file
/*!
**	@nonstd equivalent to python `sys.executable`, C# `Environment.ProcessPath`, node.js `process.execPath`
**
**	NB: There is no standard way to do this in C, so this function uses the
**	appropriate platform-specific mechanism (`/proc/self/exe` on Linux,
**	`_NSGetExecutablePath()` on macOS, `GetModuleFileName()` on Windows).
**	On any other platform, this function returns `NULL`, with an error.
**
**	@returns
**	A newly allocated string containing the absolute path of the currently
**	running executable file, or `NULL` if an error occurred.
*/
//!@{
t_char*					Program_GetExecutablePath(void);
#define c_getexepath	Program_GetExecutablePath
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
