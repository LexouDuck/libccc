
#ifndef __NOSTD__
	#include <sys/stat.h>
#else
	typedef unsigned int	mode_t;
	typedef unsigned long	uid_t;
	typedef unsigned long	pid_t;
	typedef unsigned long	gid_t;
	int chmod(char const* pathname, mode_t mode);
	int chown(char const* pathname, uid_t owner, gid_t group);
	typedef struct stat	chmod_stat;
	int stat (char const* pathname, struct stat* statbuf);
#endif

#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"

#include LIBCONFIG_ERROR_INCLUDE



e_cccerror	IO_ChangeMode(t_char const* filepath, t_io_mode mode)
{
	HANDLE_ERROR(NULLPOINTER, (filepath == NULL), return (ERROR_NULLPOINTER);)
#if (!defined(__NOSTD__) && !defined(__GNUC__) && defined(__MSVC__))
	mode = (
		((mode & ACCESSMODE_USER_R) ? _S_IREAD  : 0) |
		((mode & ACCESSMODE_USER_W) ? _S_IWRITE : 0));
	HANDLE_ERROR(SYSTEM,
		_chmod(filepath, mode),
		return (ERROR_SYSTEM);)
#else
	HANDLE_ERROR(SYSTEM,
		chmod(filepath, mode),
		return (ERROR_SYSTEM);)
#endif
	return (OK);
}



t_io_mode	IO_GetMode(t_char const* filepath)
{
#ifdef __NOSTD__
	filepath = NULL;
	return (ERROR_UNSPECIFIED); // TODO
#else
	HANDLE_ERROR(NULLPOINTER, (filepath == NULL), return (ERROR_NULLPOINTER);)

	t_io_mode	result = 0;
	struct stat	stat_buffer;

	Memory_Clear(&stat_buffer, sizeof(struct stat));
	HANDLE_ERROR(SYSTEM,
		stat(filepath, &stat_buffer),
		return (ERROR_SYSTEM);)
	result = stat_buffer.st_mode &
		(ACCESSMODE_USER_RWX |
		ACCESSMODE_GROUP_RWX |
		ACCESSMODE_OTHER_RWX);
	return (result);
#endif
}



#if 0
e_cccerror	IO_ChangeOwner(t_char const* filepath, t_char const* owner, t_char const* group)
{
	return (chown(filepath,
		getpwnam(owner),
		getgrnam(group)) ? errno : OK);
}
#endif
