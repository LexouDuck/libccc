
#include "libccc.h"

#ifndef __NOSTD__
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/types.h"
	#include "libccc/compatibility/msvc/unistd.h"
	#endif
	#include <sys/stat.h>
#else
	struct stat;
	int	stat(char const* pathname, struct stat* statbuf);
#endif

#include "libccc/memory.h"
#include "libccc/sys/io.h"

#include LIBCONFIG_ERROR_INCLUDE



#ifndef S_IFMT
#define S_IFMT	0170000	//!< bitmask for the file type bitfields, within a `stat.st_mode` value
#endif
#ifndef S_IFREG
#define S_IFREG	0100000	//!< file type bitflag: regular file
#endif
#ifndef S_IFDIR
#define S_IFDIR	0040000	//!< file type bitflag: directory
#endif



t_bool	IO_FileExists(t_char const* filepath)
{
	if CCCERROR((filepath == NULL), ERROR_NULLPOINTER, "filepath given is NULL")
		return (FALSE);
#if (defined(__NOSTD__))
	return (FALSE); // TODO
#else
	struct stat	stat_buffer;

	Memory_Clear(&stat_buffer, sizeof(struct stat));
	if (stat(filepath, &stat_buffer) != 0)
		return (FALSE); // NB: no error raised here: a non-existing file is not an "error" per se
	return ((stat_buffer.st_mode & S_IFMT) == S_IFREG);
#endif
}



t_bool	IO_DirectoryExists(t_char const* path)
{
	if CCCERROR((path == NULL), ERROR_NULLPOINTER, "path given is NULL")
		return (FALSE);
#if (defined(__NOSTD__))
	return (FALSE); // TODO
#else
	struct stat	stat_buffer;

	Memory_Clear(&stat_buffer, sizeof(struct stat));
	if (stat(path, &stat_buffer) != 0)
		return (FALSE); // NB: no error raised here: a non-existing directory is not an "error" per se
	return ((stat_buffer.st_mode & S_IFMT) == S_IFDIR);
#endif
}



t_sintmax	IO_GetFileSize(t_char const* filepath)
{
	if CCCERROR((filepath == NULL), ERROR_NULLPOINTER, "filepath given is NULL")
		return (-1);
#if (defined(__NOSTD__))
	return (-1); // TODO
#else
	struct stat	stat_buffer;

	Memory_Clear(&stat_buffer, sizeof(struct stat));
	if CCCERROR((stat(filepath, &stat_buffer) != 0), ERROR_SYSTEM,
		"call to stat() failed, with filepath=\"%s\"", filepath)
		return (-1);
	return ((t_sintmax)stat_buffer.st_size);
#endif
}
