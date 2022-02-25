
#include "libccc.h"

#ifndef __NOSTD__
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/unistd.h"
	#include "libccc/compatibility/msvc/fcntl.h"
	#else
	#include <unistd.h>
	#include <fcntl.h>
	#endif
#else
	int	close(int fd);
#endif

#include "libccc/sys/io.h"

#include LIBCONFIG_ERROR_INCLUDE



inline
e_cccerror	IO_Close(t_fd fd)
{
	int result;
#if (!defined(__GNUC__) && defined(__MSVC__))
	result = _close(fd);
#else
	result = close(fd);
#endif
	HANDLE_ERROR(SYSTEM, (result != 0),
		return (ERROR_SYSTEM);)
	return (OK);
}
