
#ifndef __NOSTD__
	#include <sys/stat.h>
#else
	typedef unsigned int	mode_t;
	typedef unsigned long	uid_t;
	typedef unsigned long	pid_t;
	typedef unsigned long	gid_t;
	int chmod(char const* pathname, mode_t mode);
	int chown(char const* pathname, uid_t owner, gid_t group);
#endif

#include "libccc/string.h"
#include "libccc/sys/io.h"

#include LIBCONFIG_ERROR_INCLUDE



inline
e_cccerror	IO_ChangeMode(t_char const* filepath, t_io_mode mode)
{
	HANDLE_ERROR(NULLPOINTER, (filepath == NULL), return (ERROR_NULLPOINTER);)
	HANDLE_ERROR(SYSTEM,
		chmod(filepath, mode),
		return (ERROR_SYSTEM);)
	return (OK);
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
