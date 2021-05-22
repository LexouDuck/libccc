
#ifndef __NOSTD__
	#include <unistd.h>
#else
	int	isatty(int fd);
#endif

#include "libccc/sys/io.h"

#include LIBCONFIG_HANDLE_INCLUDE



inline
t_bool	IO_IsTerminal(t_fd fd)
{
	return (fd == STDIN ||
		fd == STDOUT ||
		fd == STDERR ||
		isatty(fd));
}
