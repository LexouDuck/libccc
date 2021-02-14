
/*
**	Functions used from <unistd.h>:
**	-	int close(int fd);
*/
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "libccc/sys/io.h"


inline t_io_error	IO_Close(t_fd fd)
{
	return (close(fd) ? errno : OK);
}
