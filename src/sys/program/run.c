
#include "libccc.h"

#ifndef __NOSTD__
	#include <stdlib.h>
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/types.h"
	#include "libccc/compatibility/msvc/unistd.h"
	#else
	#include <unistd.h>
	#endif
#else
	int	system(char const* command);
#endif

#include "libccc/sys/program.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
e_cccerror	Program_Run(t_char const* command)
{
	// check if command processor exists
	if CCCERROR(system(NULL), ERROR_SYSTEM,
		"call to system() failed")
		return (ERROR_SYSTEM);
	// run terminal command
	if CCCERROR(system(command), ERROR_SYSTEM,
		"terminal command failed: \"%s\"", command)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}
