
/*
**	Functions used from <string.h>:
**	-	char const* strerror(int errnum);
**	-	char const* strerror_r(int errnum);
*/
#include <string.h>

#include "libccc/sys/io.h"



inline char const*	IO_GetError(t_io_error error)
{
#ifdef _WIN32
	return (strerror(error));
#else
	return (strerror_r(error));
#endif
}
