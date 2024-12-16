
#ifndef __NOSTD__
	#include <stdlib.h>
#else
	void	abort(void);
	void	exit(int exit_code);
	int		atexit(void (*f)(void));
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
