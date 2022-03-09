
#include "libccc.h"

#define __HASFUNC_SETENV	(_POSIX_C_SOURCE >= 200112L || _BSD_SOURCE) // TODO more accurate feature tests like this everywhere

#ifndef __NOSTD__
	#include <stdlib.h>
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/unistd.h"
	#else
	#include <unistd.h>
	#endif
#else
	typedef int	errno_t;
	typedef unsigned long	size_t;
	typedef unsigned long	rsize_t;
	char*	getenv(char const* name);
	errno_t getenv_s(size_t* len, char* value, rsize_t valuesz, char const* name);
	#if __HASFUNC_SETENV
		int	setenv(char const* name, char const* value, int overwrite);
	#else
		int	putenv(char const* command);
	#endif
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
#if __HASFUNC_SETENV
	HANDLE_ERROR(SYSTEM,
		setenv(name, value, overwrite),
		return (ERROR_SYSTEM);)
#else
	if (!overwrite)
	{
		if (Program_GetEnv(name) != NULL)
			return (OK);
	}
	t_char* command = String_Format("%s=%s", name, value);
	HANDLE_ERROR(SYSTEM,
		putenv(command),
		return (ERROR_SYSTEM);)
	String_Delete(&command);
#endif
	return (OK);
}
