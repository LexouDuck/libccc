
#include "libccc.h"
#include "libccc/sys/io.h"

#ifndef __NOSTD__
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/unistd.h"
	#include "libccc/compatibility/msvc/fcntl.h"
	#else
	#include <unistd.h>
	#include <fcntl.h>
	#endif
#else
	typedef unsigned int	mode_t;
	int	open(char const* pathname, int flags, mode_t mode);
#endif

#include LIBCONFIG_ERROR_INCLUDE



// the following lines allow us to fix windows stupidities
#ifdef _WIN32
#define OPEN_BINARY		O_BINARY
#define OPEN_TEXT		O_TEXT
#else
#define OPEN_BINARY		0
#define OPEN_TEXT		0
#endif



inline
t_fd	IO_Open(t_char const* filepath, t_io_open flags, t_io_mode mode)
{
	t_fd	result;
#if (!defined(__GNUC__) && defined(__MSVC__))
	result = _open(filepath, flags | OPEN_BINARY, mode);
#else
	result = open(filepath, flags | OPEN_BINARY, mode);
#endif
	HANDLE_ERROR(SYSTEM, (result < 0),
		return (ERROR_SYSTEM);)
	return (result);
}
