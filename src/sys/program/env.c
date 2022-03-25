
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
	HANDLE_ERROR_SF(SYSTEM,
		(result == NULL),
		return (NULL);,
		"call to getenv() failed, with name=\"%s\"", name)
	return (result);
}



e_cccerror	Program_SetEnv(t_char const* name, t_char const* value, t_bool overwrite)
{
#if __HASFUNC_SETENV
	HANDLE_ERROR_SF(SYSTEM,
		setenv(name, value, overwrite),
		return (ERROR_SYSTEM);,
		"call to setenv() failed, with name=\"%s\", value=\"%s\", overwrite="SF_BOOL,
		name, value, overwrite)
#else
	if (!overwrite)
	{
		if (Program_GetEnv(name) != NULL)
			return (ERROR_NONE);
	}
	t_char* command = String_Format("%s=%s", name, value);
	HANDLE_ERROR_SF(SYSTEM,
		putenv(command),
		return (ERROR_SYSTEM);,
		"cal to putenv() failed, with command: `%s`", command)
	String_Delete(&command);
#endif
	return (ERROR_NONE);
}
