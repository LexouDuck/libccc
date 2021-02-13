
/*
**	Functions used from <unistd.h>:
**	-	int close(int fd);
*/
#include <unistd.h>
#include <fcntl.h>

#include "libccc/sys/io.h"


inline int	IO_Close(t_fd fd)
{
	return (close(fd));
}
