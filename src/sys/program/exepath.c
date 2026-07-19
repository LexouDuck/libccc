
#include "libccc.h"

#ifndef __NOSTD__
	#if defined(_WIN32)
		#include <windows.h>
	#elif defined(__APPLE__)
		#include <mach-o/dyld.h>
	#else
		#include <unistd.h>
	#endif
#endif

#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/sys/program.h"

#include LIBCONFIG_ERROR_INCLUDE



#define MAX_BUFFER_SIZE		((t_size)8192)



t_char*	Program_GetExecutablePath(void)
{
#if defined(__NOSTD__)
	if CCCERROR(TRUE, ERROR_SYSTEM,
		"cannot get the executable path in a `__NOSTD__` build")
		return (NULL);
	return (NULL);
#elif defined(_WIN32)
	t_char	buffer[MAX_BUFFER_SIZE];
	DWORD	length;

	length = GetModuleFileNameA(NULL, buffer, (DWORD)MAX_BUFFER_SIZE);
	if CCCERROR((length == 0 || length >= MAX_BUFFER_SIZE), ERROR_SYSTEM,
		"call to GetModuleFileName() failed")
		return (NULL);
	return (String_Duplicate(buffer));
#elif defined(__APPLE__)
	t_char		buffer[MAX_BUFFER_SIZE];
	t_u32	size = (t_u32)MAX_BUFFER_SIZE;

	if CCCERROR((_NSGetExecutablePath(buffer, &size) != 0), ERROR_SYSTEM,
		"call to _NSGetExecutablePath() failed (path is longer than " SF_SIZE " chars)", MAX_BUFFER_SIZE)
		return (NULL);
	return (String_Duplicate(buffer)); // NB: the path returned may contain symlinks: this is deliberate (it matches `argv[0]` behavior)
#elif defined(__linux__)
	t_char	buffer[MAX_BUFFER_SIZE];
	t_sintmax	length;

	length = (t_sintmax)readlink("/proc/self/exe", buffer, MAX_BUFFER_SIZE - 1);
	if CCCERROR((length < 0 || (t_size)length >= MAX_BUFFER_SIZE), ERROR_SYSTEM,
		"call to readlink(\"/proc/self/exe\") failed")
		return (NULL);
	buffer[length] = '\0';
	return (String_Duplicate(buffer));
#else
	if CCCERROR(TRUE, ERROR_SYSTEM,
		"getting the executable path is not supported on this platform")
		return (NULL);
	return (NULL);
#endif
}
