
#ifndef __NOSTD__
	#include <stdlib.h>
	#include <unistd.h>
#else
	int	system(char const* command);
#endif

#include "libccc/sys/program.h"

#include LIBCONFIG_ERROR_INCLUDE



inline
e_cccerror	Program_Run(t_char const* command)
{
	// check if command processor exists
	HANDLE_ERROR(SYSTEM,
		system(NULL),
		return (ERROR_SYSTEM);)
	// run terminal command
	HANDLE_ERROR(SYSTEM,
		system(command),
		return (ERROR_SYSTEM);)
	return (OK);
}