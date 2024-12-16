
#include "libccc.h"
#include "libccc/sys/io.h"

#ifndef __NOSTD__
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/types.h"
	#include "libccc/compatibility/msvc/unistd.h"
	#else
	#include <unistd.h>
	#endif
	#include <fcntl.h>
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



_INLINE()
t_fd	IO_Open(t_char const* filepath, t_io_open flags, t_io_mode mode)
{
	t_fd	result;

	result = open(filepath, flags | OPEN_BINARY, mode);
	if CCCERROR((result < 0), ERROR_SYSTEM, 
		"could not open file: %s", filepath)
		return (result);
	return (result);
}
