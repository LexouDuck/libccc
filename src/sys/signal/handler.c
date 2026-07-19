
#include "libccc.h"

#ifndef __NOSTD__
	#include <signal.h>
#endif

#include "libccc/sys/signal.h"

#include LIBCONFIG_ERROR_INCLUDE



e_cccerror	Signal_SetHandler(t_signal sig, f_signalhandler handler)
{
	if CCCERROR((handler == NULL), ERROR_NULLPOINTER, "signal handler function given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((signal(sig, handler) == SIG_ERR), ERROR_SYSTEM,
		"call to signal() failed, with signal=%i", sig)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



e_cccerror	Signal_Reset(t_signal sig)
{
	if CCCERROR((signal(sig, SIG_DFL) == SIG_ERR), ERROR_SYSTEM,
		"call to signal(SIG_DFL) failed, with signal=%i", sig)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



e_cccerror	Signal_Ignore(t_signal sig)
{
	if CCCERROR((signal(sig, SIG_IGN) == SIG_ERR), ERROR_SYSTEM,
		"call to signal(SIG_IGN) failed, with signal=%i", sig)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}
