
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
#ifndef __NOSTD__
	#include <errno.h>
#else
	#ifndef	errno
	#define errno	(*_errno())
	extern	int*	_errno(void);
	#endif
#endif

#include "libccc/sys/io.h"

#include LIBCONFIG_HANDLE_INCLUDE



inline
e_stderror	IO_ChangeMode(t_char const* filepath, t_io_mode mode)
{
	HANDLE_ERROR(NULLPOINTER, (filepath == NULL), return (ERROR_NULLPOINTER);)
	return (chmod(filepath, mode) ? errno : OK);
}



#if 0
inline
e_stderror	IO_ChangeOwner(t_char const* filepath, t_char const* owner, t_char const* group)
{
	return (chown(filepath,
		getpwnam(owner),
		getgrnam(group)) ? errno : OK);
}
#endif
