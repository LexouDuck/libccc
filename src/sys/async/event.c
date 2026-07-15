
#ifndef __NOSTD__
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L	// needed to expose POSIX APIs, when compiling with a strict `-std=c**` option
	#endif
#endif
#include "libccc.h"
#include "libccc/sys/async.h"

#include "async_private.h"

#include LIBCONFIG_ERROR_INCLUDE



e_cccerror	AsyncEvent_Init(s_asyncloop* loop, s_async_event* event, f_async_event callback)
{
	if CCCERROR((loop == NULL), ERROR_NULLPOINTER, 
		"event loop given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((event == NULL), ERROR_NULLPOINTER, 
		"event handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((callback == NULL), ERROR_NULLPOINTER, 
		"event callback function given is NULL")
		return (ERROR_NULLPOINTER);
	event->base.data = NULL;
	event->callback = callback;
	event->pending = FALSE;
	__AsyncLoop_Attach(loop, &event->base, ASYNCHANDLE_EVENT);
	__AsyncHandle_SetActive(&event->base, TRUE); // like libuv's `uv_async_t`, event handles are active from init onwards
	return (ERROR_NONE);
}



e_cccerror	AsyncEvent_Send(s_async_event* event)
{
	s_asyncloop*	loop;

	if CCCERROR((event == NULL), ERROR_NULLPOINTER, 
		"event handle given is NULL")
		return (ERROR_NULLPOINTER);
	loop = event->base.loop;
	if CCCERROR((loop == NULL || event->base.kind != ASYNCHANDLE_EVENT), ERROR_INVALIDARGS, 
		"event handle given is not initialized (make sure to call AsyncEvent_Init() first)")
		return (ERROR_INVALIDARGS);
	Mutex_Lock(&loop->mutex);
	event->pending = TRUE;
	Mutex_Unlock(&loop->mutex);
	__AsyncLoop_Wakeup(loop);
	return (ERROR_NONE);
}



e_cccerror	AsyncEvent_Stop(s_async_event* event)
{
	if CCCERROR((event == NULL), ERROR_NULLPOINTER, 
		"event handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((event->base.loop == NULL || event->base.kind != ASYNCHANDLE_EVENT), ERROR_INVALIDARGS, 
		"event handle given is not initialized (make sure to call AsyncEvent_Init() first)")
		return (ERROR_INVALIDARGS);
	Mutex_Lock(&event->base.loop->mutex);
	event->pending = FALSE;
	Mutex_Unlock(&event->base.loop->mutex);
	__AsyncHandle_SetActive(&event->base, FALSE);
	return (ERROR_NONE);
}
