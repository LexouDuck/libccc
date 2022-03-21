
#include "libccc.h"

#ifndef __NOSTD__
	#include <stdlib.h>
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/unistd.h"
	#else
	#include <unistd.h>
	#endif
#else
	int	system(char const* command);
#endif

#include "libccc/sys/program.h"

#include LIBCONFIG_ERROR_INCLUDE



inline
e_cccerror	Program_Run(t_char const* command)
{
	// check if command processor exists
	HANDLE_ERROR_SF(SYSTEM,
		system(NULL),
		return (ERROR_SYSTEM);,
		"call to system() failed")
	// run terminal command
	HANDLE_ERROR_SF(SYSTEM,
		system(command),
		return (ERROR_SYSTEM);,
		"terminal command failed: \"%s\"", command)
	return (OK);
}
