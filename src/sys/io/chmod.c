
#ifndef __NOSTD__
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/unistd.h"
	#endif
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



t_io_mode	IO_GetMode(t_char const* filepath)
{
	if CCCERROR((filepath == NULL), ERROR_NULLPOINTER, "filepath given is NULL")
		return (ERROR_NULLPOINTER);
#if (defined(__NOSTD__))
	filepath = NULL;
	return (ERROR_UNSPECIFIED); // TODO
#else
	t_io_mode	result = 0;
	struct stat	stat_buffer;

	Memory_Clear(&stat_buffer, sizeof(struct stat));
	if CCCERROR(stat(filepath, &stat_buffer), ERROR_SYSTEM,
		"call to stat() failed, with filepath=\"%s\"", filepath)
		return (ERROR_SYSTEM);
	result = stat_buffer.st_mode &
		(ACCESSMODE_USER_RWX |
		ACCESSMODE_GROUP_RWX |
		ACCESSMODE_OTHER_RWX);
	return (result);
#endif
}



e_cccerror	IO_ChangeMode(t_char const* filepath, t_io_mode mode)
{
	if CCCERROR((filepath == NULL), ERROR_NULLPOINTER, "filepath given is NULL")
		return (ERROR_NULLPOINTER);
#if (defined(__NOSTD__) || \
	(!defined(__GNUC__) && defined(__MSVC__) && defined(__clang__))) // TODO figure out why chmod() is not present on all windows envs
	if CCCERROR((TRUE | mode), ERROR_UNSPECIFIED, // use the 'mode' argument here to avoid unused arg warning
		"the 'chmod()' function is not available for this platform.")
		return (ERROR_UNSPECIFIED);
#else
	#if (!defined(__GNUC__) && defined(__MSVC__))
	mode = (
		((mode & ACCESSMODE_USER_R) ? _S_IREAD  : 0) |
		((mode & ACCESSMODE_USER_W) ? _S_IWRITE : 0));
	#endif
	if CCCERROR(chmod(filepath, mode), ERROR_SYSTEM,
		"call to chmod() failed, with filepath=\"%s\" and mode=%u", filepath, mode)
		return (ERROR_SYSTEM);
#endif
	return (ERROR_NONE);
}



#if 0
e_cccerror	IO_ChangeOwner(t_char const* filepath, t_char const* owner, t_char const* group)
{
	return (chown(filepath,
		getpwnam(owner),
		getgrnam(group)) ? errno : OK);
}
#endif
