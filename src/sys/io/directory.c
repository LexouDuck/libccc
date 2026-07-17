
#include "libccc.h"

#ifndef __NOSTD__
	#include <errno.h>
	#ifdef _WIN32
		#if (!defined(__GNUC__) && defined(__MSVC__))
		#include "libccc/compatibility/msvc/types.h"
		#include "libccc/compatibility/msvc/unistd.h"
		#endif
		#include <direct.h>
		// on Windows, the mkdir() function only takes one argument (permissions are handled differently)
		#define ccc_mkdir(PATH, MODE)	_mkdir(PATH)
		#define ccc_rmdir(PATH)			_rmdir(PATH)
	#else
		#include <unistd.h>
		#include <sys/stat.h>
		#define ccc_mkdir(PATH, MODE)	mkdir((PATH), (MODE))
		#define ccc_rmdir(PATH)			rmdir(PATH)
	#endif
#else
	typedef unsigned int	mode_t;
	int	mkdir(char const* path, mode_t mode);
	int	rmdir(char const* path);
	#define ccc_mkdir(PATH, MODE)	mkdir((PATH), (MODE))
	#define ccc_rmdir(PATH)			rmdir(PATH)
#endif

#include "libccc/string.h"
#include "libccc/memory.h"
#include "libccc/sys/io.h"

#include LIBCONFIG_ERROR_INCLUDE



//! Checks whether the given char `c` is a valid path separator char for the current platform
static
t_bool	IO_Path_IsSeparator(t_char c)
{
#ifdef _WIN32
	return (c == '/' || c == '\\');
#else
	return (c == '/');
#endif
}



e_cccerror	IO_CreateDirectory(t_char const* path, t_io_mode mode)
{
	if CCCERROR((path == NULL), ERROR_NULLPOINTER, "path given is NULL")
		return (ERROR_NULLPOINTER);
	if (ccc_mkdir(path, mode) != 0)
	{
		// like most modern languages: not an error, if the directory already exists
		if (errno == EEXIST && IO_DirectoryExists(path))
			return (ERROR_NONE);
		if CCCERROR(TRUE, ERROR_SYSTEM,
			"call to mkdir() failed, with path=\"%s\" and mode=%u", path, mode)
			return (ERROR_SYSTEM);
	}
	return (ERROR_NONE);
}



e_cccerror	IO_CreateDirectory_Recursive(t_char const* path, t_io_mode mode)
{
	e_cccerror	error;
	t_char*		tmp;
	t_size		i;

	if CCCERROR((path == NULL), ERROR_NULLPOINTER, "path given is NULL")
		return (ERROR_NULLPOINTER);
	tmp = String_Duplicate(path);
	if CCCERROR((tmp == NULL), ERROR_ALLOCFAILURE, NULL)
		return (ERROR_ALLOCFAILURE);
	for (i = 0; tmp[i] != '\0'; ++i)
	{
		if (!IO_Path_IsSeparator(tmp[i]))
			continue;
		if (i == 0)
			continue; // do not attempt to create the filesystem root
#ifdef _WIN32
		if (i > 0 && tmp[i - 1] == ':')
			continue; // do not attempt to create a drive root, ie: `C:\`
		if (i > 0 && IO_Path_IsSeparator(tmp[i - 1]))
			continue; // do not attempt to create a UNC path root, ie: `\\host`
#endif
		tmp[i] = '\0';
		error = IO_CreateDirectory(tmp, mode);
		tmp[i] = IO_PATH_SEPARATOR;
		if (error != ERROR_NONE)
		{
			Memory_Free(tmp);
			return (error);
		}
	}
	Memory_Free(tmp);
	// finally, create the full deepest-level directory (unless the path had a trailing separator)
	i = String_Length(path);
	if (i > 0 && IO_Path_IsSeparator(path[i - 1]))
		return (ERROR_NONE);
	return (IO_CreateDirectory(path, mode));
}



e_cccerror	IO_DeleteDirectory(t_char const* path)
{
	if CCCERROR((path == NULL), ERROR_NULLPOINTER, "path given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((ccc_rmdir(path) != 0), ERROR_SYSTEM,
		"call to rmdir() failed, with path=\"%s\"", path)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}
