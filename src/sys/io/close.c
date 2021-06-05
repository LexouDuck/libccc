
#ifndef __NOSTD__
	#include <unistd.h>
	#include <fcntl.h>
#else
	int	close(int fd);
#endif

#include "libccc/sys/io.h"

#include LIBCONFIG_ERROR_INCLUDE



inline
e_cccerror	IO_Close(t_fd fd)
{
	HANDLE_ERROR(SYSTEM,
		close(fd),
		return (ERROR_SYSTEM);)
	return (OK);
}
