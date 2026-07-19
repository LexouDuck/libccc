
#include "libccc.h"

#ifndef __NOSTD__
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/types.h"
	#include "libccc/compatibility/msvc/unistd.h"
	#include <process.h>
	#define getpid	_getpid
	#else
	#include <unistd.h>
	#endif
#else
	int	getpid(void);
#endif

#include "libccc/sys/program.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
t_sint	Program_GetPID(void)
{
	return ((t_sint)getpid());
}
