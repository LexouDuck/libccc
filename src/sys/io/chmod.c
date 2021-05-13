
/*
**	Functions used from <sys/stat.h>:
**	-	int chmod(const t_char* pathname, mode_t mode);
**	-	int chown(const t_char* pathname, uid_t owner, gid_t group);
*/
#include <errno.h>
#include <sys/stat.h>

#include "libccc/sys/io.h"



inline t_io_error	IO_ChangeMode(t_char const* filepath, t_io_mode mode)
{
	return (chmod(filepath, mode) ? errno : OK);
}



#if 0
inline t_io_error	IO_ChangeOwner(t_char const* filepath, t_char const* owner, t_char const* group)
{
	return (chown(filepath,
		getpwnam(owner),
		getgrnam(group)) ? errno : OK);
}
#endif
