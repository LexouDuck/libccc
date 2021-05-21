
#ifndef __NOSTD__
	#include <unistd.h>
	#include <fcntl.h>
#else
	int	close(int fd);
#endif
#ifndef __NOSTD__
	#include <errno.h>
#else
	#undef	errno
	#define errno	(*_errno())
#endif

#include "libccc/sys/io.h"



inline t_io_error	IO_Close(t_fd fd)
{
	return (close(fd) ? errno : OK);
}
