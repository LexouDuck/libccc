
#include "libccc.h"

#ifndef __NOSTD__
	#include <stdio.h>
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/types.h"
	#include "libccc/compatibility/msvc/unistd.h"
	#else
	#include <unistd.h>
	#endif
	#include <fcntl.h>
#else
	int	remove(char const* pathname);
	int	rename(char const* oldpath, char const* newpath);
	int	read(int fd, char* buffer, size_t n);
	int	write(int fd, char const* buffer, size_t n);
#endif

#include "libccc/memory.h"
#include "libccc/sys/io.h"

#include LIBCONFIG_ERROR_INCLUDE



e_cccerror	IO_DeleteFile(t_char const* filepath)
{
	if CCCERROR((filepath == NULL), ERROR_NULLPOINTER, "filepath given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((remove(filepath) != 0), ERROR_SYSTEM,
		"call to remove() failed, with filepath=\"%s\"", filepath)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



e_cccerror	IO_CopyFile(t_char const* srcpath, t_char const* dstpath)
{
	e_cccerror	error = ERROR_NONE;
	t_io_mode	mode;
	t_char*		buffer;
	t_fd		src = -1;
	t_fd		dst = -1;
	t_sintmax	size_read;
	t_sintmax	size_written;

	if CCCERROR((srcpath == NULL), ERROR_NULLPOINTER, "source filepath given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((dstpath == NULL), ERROR_NULLPOINTER, "destination filepath given is NULL")
		return (ERROR_NULLPOINTER);
	mode = IO_GetMode(srcpath); // preserve the file access permissions of the source file
	buffer = (t_char*)Memory_Allocate(IO_BUFFER_SIZE);
	if CCCERROR((buffer == NULL), ERROR_ALLOCFAILURE, NULL)
		return (ERROR_ALLOCFAILURE);
	src = IO_Open(srcpath, OPEN_READONLY, 0);
	if (src < 0)
	{
		error = ERROR_SYSTEM;
		goto cleanup;
	}
	dst = IO_Open(dstpath, (OPEN_WRITEONLY | OPEN_CREATE | OPEN_CLEARFILE), mode);
	if (dst < 0)
	{
		error = ERROR_SYSTEM;
		goto cleanup;
	}
	while ((size_read = read(src, buffer, IO_BUFFER_SIZE)) > 0)
	{
		size_written = write(dst, buffer, (t_size)size_read);
		if CCCERROR((size_written != size_read), ERROR_SYSTEM,
			"could not write to destination file: %s", dstpath)
		{
			error = ERROR_SYSTEM;
			goto cleanup;
		}
	}
	if CCCERROR((size_read < 0), ERROR_SYSTEM,
		"could not read from source file: %s", srcpath)
		error = ERROR_SYSTEM;

cleanup:
	Memory_Free(buffer);
	if (src >= 0)	IO_Close(src);
	if (dst >= 0)	IO_Close(dst);
	return (error);
}



e_cccerror	IO_MoveFile(t_char const* oldpath, t_char const* newpath)
{
	e_cccerror	error;

	if CCCERROR((oldpath == NULL), ERROR_NULLPOINTER, "old filepath given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((newpath == NULL), ERROR_NULLPOINTER, "new filepath given is NULL")
		return (ERROR_NULLPOINTER);
	if (rename(oldpath, newpath) == 0)
		return (ERROR_NONE);
	// a simple rename() was not possible (perhaps moving across devices/filesystems ?)
	// so, attempt to copy the file over to its new location, then delete the original
	error = IO_CopyFile(oldpath, newpath);
	if (error != ERROR_NONE)
		return (error);
	return (IO_DeleteFile(oldpath));
}
