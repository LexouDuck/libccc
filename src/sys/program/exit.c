
#ifndef __NOSTD__
	#include <stdlib.h>
#else
	void	abort(void);
	void	exit(int exit_code);
	int		atexit(void (*f)(void));
#endif

#include "libccc/sys/program.h"

#include LIBCONFIG_ERROR_INCLUDE



inline
void	Program_Abort(void)
{
	abort();
}



inline
void	Program_Exit(int exit_code)
{
	exit(exit_code);
}



inline
e_cccerror	Program_OnExit(void (*f)(void))
{
	HANDLE_ERROR(SYSTEM,
		atexit(f),
		return (ERROR_SYSTEM);)
	return (OK);
}
