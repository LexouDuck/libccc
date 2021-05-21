
#ifndef __NOSTD__
	#include <unistd.h>
#else
	int	isatty(int fd);
#endif

#include "libccc/sys/io.h"



inline t_bool	IO_IsTerminal(t_fd fd)
{
	return (fd == STDIN ||
		fd == STDOUT ||
		fd == STDERR ||
		isatty(fd));
}
