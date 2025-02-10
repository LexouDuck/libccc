
#include "libccc.h"

#ifndef __NOSTD__
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/types.h"
	#include "libccc/compatibility/msvc/unistd.h"
	#else
	#include <unistd.h>
	#endif
#else
	int	isatty(int fd);
#endif

#include "libccc/sys/io.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
t_bool	IO_IsTerminal(t_fd fd)
{
	return (fd == STDIN ||
			fd == STDOUT ||
			fd == STDERR ||
			isatty(fd));
}
