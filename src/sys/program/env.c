
#include "libccc.h"

#define __HASFUNC_SETENV	(_POSIX_C_SOURCE >= 200112L || _BSD_SOURCE) // TODO more accurate feature tests like this everywhere

#ifndef __NOSTD__
	#include <stdlib.h>
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/types.h"
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
		int	unsetenv(char const* name);
	#else
		int	putenv(char const* command);
	#endif
#endif

#include "libccc/sys/program.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
t_char*	Program_GetEnv(t_char const* name)
{
	if CCCERROR((name == NULL), ERROR_NULLPOINTER, "environment variable name given is NULL")
		return (NULL);
	t_char* result = getenv(name);
	if CCCERROR((result == NULL), ERROR_SYSTEM, 
		"call to getenv() failed, with name=\"%s\"", name)
		return (NULL);
	// NB: a duplicate is returned here, so that the result is safe to use
	// regardless of any future calls to setenv()/putenv()/getenv()
	return (String_Duplicate(result));
}



e_cccerror	Program_SetEnv(t_char const* name, t_char const* value, t_bool overwrite)
{
	if CCCERROR((name == NULL), ERROR_NULLPOINTER, "environment variable name given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((value == NULL), ERROR_NULLPOINTER, "environment variable value given is NULL")
		return (ERROR_NULLPOINTER);
#if __HASFUNC_SETENV
	if CCCERROR(setenv(name, value, overwrite), ERROR_SYSTEM,
		"call to setenv() failed, with name=\"%s\", value=\"%s\", overwrite=" SF_BOOL,
		name, value, overwrite)
		return (ERROR_SYSTEM);
#elif _POSIX_C_SOURCE > 0
	if (!overwrite)
	{
		if (Program_GetEnv(name) != NULL)
			return (ERROR_NONE);
	}
	t_char* command = String_Format("%s=%s", name, value);
	if CCCERROR(putenv(command), ERROR_SYSTEM,
		"call to putenv() failed, with command: `%s`", command)
		return (ERROR_SYSTEM);
	String_Delete(&command);
#else
	return (ERROR_SYSTEM);
#endif
	return (overwrite ? ERROR_NONE : ERROR_NONE);
}



e_cccerror	Program_UnsetEnv(t_char const* name)
{
	if CCCERROR((name == NULL), ERROR_NULLPOINTER, "environment variable name given is NULL")
		return (ERROR_NULLPOINTER);
#if __HASFUNC_SETENV
	if CCCERROR(unsetenv(name), ERROR_SYSTEM,
		"call to unsetenv() failed, with name=\"%s\"", name)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
#elif (defined(__MSVC__) || defined(_WIN32))
	// on Windows, setting an environment variable to an empty string deletes it
	t_char* command = String_Format("%s=", name);
	if CCCERROR((command == NULL), ERROR_ALLOCFAILURE, NULL)
		return (ERROR_ALLOCFAILURE);
	if CCCERROR(putenv(command), ERROR_SYSTEM,
		"call to putenv() failed, with command: `%s`", command)
	{
		String_Delete(&command);
		return (ERROR_SYSTEM);
	}
	String_Delete(&command);
	return (ERROR_NONE);
#else
	if CCCERROR(TRUE, ERROR_SYSTEM,
		"deleting an environment variable is not supported on this platform")
		return (ERROR_SYSTEM);
	return (ERROR_SYSTEM);
#endif
}
