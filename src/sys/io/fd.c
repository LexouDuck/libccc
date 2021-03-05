
/*
**	Functions used from <unistd.h>:
**	-	int isatty(int fd);
*/
#include <unistd.h>

#include "libccc/sys/io.h"



inline t_bool	IO_IsTerminal(t_fd fd)
{
	return (fd == STDIN ||
		fd == STDOUT ||
		fd == STDERR ||
		isatty(fd));
}
