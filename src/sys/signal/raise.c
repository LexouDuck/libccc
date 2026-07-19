
#include "libccc.h"

#ifndef __NOSTD__
	#include <signal.h>
#endif

#include "libccc/sys/signal.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
e_cccerror	Signal_Raise(t_signal sig)
{
	if CCCERROR((raise(sig) != 0), ERROR_SYSTEM,
		"call to raise() failed, with signal=%i", sig)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}
