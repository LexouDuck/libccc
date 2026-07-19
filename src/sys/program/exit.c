
#ifndef __NOSTD__
	#include <stdlib.h>
#else
	void	abort(void);
	void	exit(int exit_code);
	void	_Exit(int exit_code);
	int		atexit(void (*f)(void));
#endif

// feature test: whether the C11 quick_exit()/at_quick_exit() functions are available
#ifndef __HASFUNC_QUICK_EXIT
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L && !defined(__NOSTD__) && \
	(defined(__GLIBC__) || defined(__MSVC__) || defined(_MSC_VER) || defined(__APPLE__) || defined(__MINGW32__)))
#define __HASFUNC_QUICK_EXIT	1
#else
#define __HASFUNC_QUICK_EXIT	0
#endif
#endif

#if (!defined(__GNUC__) && defined(__MSVC__))
	#include <process.h> // for _exit()
	#define _Exit	_exit
#endif

#include "libccc/sys/program.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
void	Program_Abort(void)
{
	abort();
}



_INLINE()
void	Program_Exit(int exit_code)
{
	exit(exit_code);
}



_INLINE()
e_cccerror	Program_OnExit(void (*f)(void))
{
	if CCCERROR(atexit(f), ERROR_SYSTEM,
		"call to atexit() failed%s", (f == NULL) ? ", function given is NULL" : "")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



_INLINE()
void	Program_ExitNow(int exit_code)
{
	_Exit(exit_code);
}



_INLINE()
void	Program_ExitQuick(int exit_code)
{
#if __HASFUNC_QUICK_EXIT
	quick_exit(exit_code);
#else
	_Exit(exit_code); // quick_exit() is unavailable: fall back to immediate termination
#endif
}



_INLINE()
e_cccerror	Program_OnExitQuick(void (*f)(void))
{
#if __HASFUNC_QUICK_EXIT
	if CCCERROR(at_quick_exit(f), ERROR_SYSTEM,
		"call to at_quick_exit() failed%s", (f == NULL) ? ", function given is NULL" : "")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
#else
	(void)f;
	if CCCERROR(TRUE, ERROR_SYSTEM,
		"the C11 at_quick_exit() function is not available on this platform")
		return (ERROR_SYSTEM);
	return (ERROR_SYSTEM);
#endif
}
