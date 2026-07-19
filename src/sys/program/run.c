
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
	if CCCERROR((command == NULL), ERROR_NULLPOINTER, "terminal command given is NULL")
		return (ERROR_NULLPOINTER);
	// check if a command processor exists (calling system(NULL) returns non-zero if one is available)
	if CCCERROR((system(NULL) == 0), ERROR_SYSTEM,
		"no command processor is available on this system")
		return (ERROR_SYSTEM);
	// run terminal command
	if CCCERROR(system(command), ERROR_SYSTEM,
		"terminal command failed: \"%s\"", command)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}
