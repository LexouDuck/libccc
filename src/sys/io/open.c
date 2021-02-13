
/*
**	Functions used from <unistd.h>:
**	-	int	open(const char *pathname, int flags, mode_t mode);
*/
#include <unistd.h>
#include <fcntl.h>

#include "libccc/sys/io.h"


inline t_fd	IO_Open(char const* filepath, t_io_open flags, t_io_mode mode)
{
	return (open(filepath, flags, mode));
}
