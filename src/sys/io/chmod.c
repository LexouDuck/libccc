
#ifndef __NOSTD__
	#include <sys/stat.h>
#else
	typedef unsigned int	mode_t;
	typedef unsigned long	uid_t;
	typedef unsigned long	pid_t;
	typedef unsigned long	gid_t;
	int chmod(char const* pathname, mode_t mode);
	int chown(char const* pathname, uid_t owner, gid_t group);
	int stat (char const* pathname, struct stat* statbuf);
#endif

#include "libccc/string.h"
#include "libccc/sys/io.h"

#include LIBCONFIG_ERROR_INCLUDE



inline
e_cccerror	IO_ChangeMode	(t_char const* filepath, t_io_mode mode)
{
	HANDLE_ERROR(NULLPOINTER, (filepath == NULL), return (ERROR_NULLPOINTER);)
	HANDLE_ERROR(SYSTEM,
		chmod(filepath, mode),
		return (ERROR_SYSTEM);)
	return (OK);
}

inline
t_io_mode	IO_GetMode		(t_char const* filepath)
{
	HANDLE_ERROR(NULLPOINTER, (filepath == NULL), return (ERROR_NULLPOINTER);)

	t_io_mode	result = 0;
	struct stat	stat_buffer = {0};

	HANDLE_ERROR(SYSTEM,
		stat(filepath, &stat_buffer),
		return (ERROR_SYSTEM);)
	result = stat_buffer.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
	return (result);
}

#if 0
inline
e_cccerror	IO_ChangeOwner(t_char const* filepath, t_char const* owner, t_char const* group)
{
	return (chown(filepath,
		getpwnam(owner),
		getgrnam(group)) ? errno : OK);
}
#endif
