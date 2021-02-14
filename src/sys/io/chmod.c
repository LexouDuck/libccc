
/*
**	Functions used from <unistd.h>:
**	-	int chmod(const char *pathname, mode_t mode);
**	-	int chown(const char *pathname, uid_t owner, gid_t group);
*/
#include <unistd.h>
#include <sys/stat.h>

#include "libccc/sys/io.h"



inline t_bool	IO_IsTerminal(t_fd fd)
{
	return (fd == STDIN ||
		fd == STDOUT ||
		fd == STDERR ||
		isatty(fd));
}



inline int	IO_ChangeMode(char const* filepath, t_io_mode mode)
{
	return (chmod(filepath, mode));
}



#if 0
inline int	IO_ChangeOwner(char const* filepath, char const* owner, char const* group)
{
	return (chown(filepath,
		getpwnam(owner),
		getgrnam(group)));
}
#endif
