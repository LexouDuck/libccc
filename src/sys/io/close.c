
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



inline
e_cccerror	IO_Close(t_fd fd)
{
	HANDLE_ERROR(SYSTEM,
		(close(fd) != 0),
		return (ERROR_SYSTEM);)
	return (OK);
}
