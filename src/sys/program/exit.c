
#ifndef __NOSTD__
	#include <stdlib.h>
#else
	void	abort(void);
	void	exit(int exit_code);
	int		atexit(void (*f)(void));
#endif

#include "libccc/sys/program.h"

#include LIBCONFIG_ERROR_INCLUDE



extern inline
void	Program_Abort(void)
{
	abort();
}



extern inline
void	Program_Exit(int exit_code)
{
	exit(exit_code);
}



extern inline
e_cccerror	Program_OnExit(void (*f)(void))
{
	if CCCERROR(atexit(f), ERROR_SYSTEM,
		"call to atexit() failed%s", (f == NULL) ? ", function given is NULL" : "")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}
