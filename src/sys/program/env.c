
#ifndef __NOSTD__
	#include <stdlib.h>
	#include <unistd.h>
#else
	char*	getenv(char const* name);
	errno_t getenv_s(size_t* len, char* value, rsize_t valuesz, char const* name);
	int		setenv(char const* name, char const* value, int overwrite);
#endif

#include "libccc/sys/program.h"

#include LIBCONFIG_ERROR_INCLUDE



inline
t_char*	Program_GetEnv(t_char const* name)
{
	t_char* result = getenv(name);
	HANDLE_ERROR(SYSTEM,
		(result == NULL),
		return (NULL);)
	return (result);
}



e_cccerror	Program_SetEnv(t_char const* name, t_char const* value, t_bool overwrite)
{
	HANDLE_ERROR(SYSTEM,
		setenv(name, value, overwrite),
		return (ERROR_SYSTEM);)
	return (OK);
}
