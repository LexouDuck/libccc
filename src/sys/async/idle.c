
#ifndef __NOSTD__
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L	// needed to expose POSIX APIs, when compiling with a strict `-std=c**` option
	#endif
#endif
#include "libccc.h"
#include "libccc/sys/async.h"

#include "async_private.h"

#include LIBCONFIG_ERROR_INCLUDE



e_cccerror	AsyncIdle_Init(s_asyncloop* loop, s_async_idle* idle)
{
	if CCCERROR((loop == NULL), ERROR_NULLPOINTER, 
		"event loop given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((idle == NULL), ERROR_NULLPOINTER, 
		"idle handle given is NULL")
		return (ERROR_NULLPOINTER);
	idle->base.data = NULL;
	idle->callback = NULL;
	__AsyncLoop_Attach(loop, &idle->base, ASYNCHANDLE_IDLE);
	return (ERROR_NONE);
}



e_cccerror	AsyncIdle_Start(s_async_idle* idle, f_async_idle callback)
{
	if CCCERROR((idle == NULL), ERROR_NULLPOINTER, 
		"idle handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((idle->base.loop == NULL || idle->base.kind != ASYNCHANDLE_IDLE), ERROR_INVALIDARGS, 
		"idle handle given is not initialized (make sure to call AsyncIdle_Init() first)")
		return (ERROR_INVALIDARGS);
	if CCCERROR((callback == NULL), ERROR_NULLPOINTER, 
		"idle callback function given is NULL")
		return (ERROR_NULLPOINTER);
	idle->callback = callback;
	__AsyncHandle_SetActive(&idle->base, TRUE);
	return (ERROR_NONE);
}



e_cccerror	AsyncIdle_Stop(s_async_idle* idle)
{
	if CCCERROR((idle == NULL), ERROR_NULLPOINTER, 
		"idle handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((idle->base.loop == NULL || idle->base.kind != ASYNCHANDLE_IDLE), ERROR_INVALIDARGS, 
		"idle handle given is not initialized (make sure to call AsyncIdle_Init() first)")
		return (ERROR_INVALIDARGS);
	__AsyncHandle_SetActive(&idle->base, FALSE);
	return (ERROR_NONE);
}
