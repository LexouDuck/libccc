
#include "libccc.h"

#ifndef __NOSTD__
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/unistd.h"
	#else
	#include <unistd.h>
	#endif
	#include <fcntl.h>
#else
	int	close(int fd);
#endif

#include "libccc/sys/io.h"

#include LIBCONFIG_ERROR_INCLUDE



extern inline
e_cccerror	IO_Close(t_fd fd)
{
	if CCCERROR((close(fd) != 0), ERROR_SYSTEM,
		"call to close() failed, for fd=%i", fd)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}
