
#ifndef __NOSTD__
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L	// needed to expose POSIX APIs, when compiling with a strict `-std=c**` option
	#endif
#endif
#include "libccc.h"
#include "libccc/sys/async.h"

#include "async_private.h"

#include LIBCONFIG_ERROR_INCLUDE



e_cccerror	AsyncTimer_Init(s_asyncloop* loop, s_async_timer* timer)
{
	if CCCERROR((loop == NULL), ERROR_NULLPOINTER, 
		"event loop given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((timer == NULL), ERROR_NULLPOINTER, 
		"timer handle given is NULL")
		return (ERROR_NULLPOINTER);
	timer->base.data = NULL;
	timer->callback = NULL;
	timer->deadline = 0;
	timer->repeat = 0;
	timer->sweep = 0;
	__AsyncLoop_Attach(loop, &timer->base, ASYNCHANDLE_TIMER);
	return (ERROR_NONE);
}



e_cccerror	AsyncTimer_Start(s_async_timer* timer, f_async_timer callback, t_asynctime delay, t_asynctime repeat)
{
	if CCCERROR((timer == NULL), ERROR_NULLPOINTER, 
		"timer handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((timer->base.loop == NULL || timer->base.kind != ASYNCHANDLE_TIMER), ERROR_INVALIDARGS, 
		"timer handle given is not initialized (make sure to call AsyncTimer_Init() first)")
		return (ERROR_INVALIDARGS);
	if CCCERROR((callback == NULL), ERROR_NULLPOINTER, 
		"timer callback function given is NULL")
		return (ERROR_NULLPOINTER);
	timer->callback = callback;
	timer->deadline = timer->base.loop->now + delay;
	timer->repeat = repeat;
	timer->sweep = timer->base.loop->timer_sweep; // a timer started from within a callback only fires from the next iteration onwards
	__AsyncHandle_SetActive(&timer->base, TRUE);
	return (ERROR_NONE);
}



e_cccerror	AsyncTimer_Stop(s_async_timer* timer)
{
	if CCCERROR((timer == NULL), ERROR_NULLPOINTER, 
		"timer handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((timer->base.loop == NULL || timer->base.kind != ASYNCHANDLE_TIMER), ERROR_INVALIDARGS, 
		"timer handle given is not initialized (make sure to call AsyncTimer_Init() first)")
		return (ERROR_INVALIDARGS);
	__AsyncHandle_SetActive(&timer->base, FALSE);
	return (ERROR_NONE);
}



e_cccerror	AsyncTimer_Restart(s_async_timer* timer)
{
	if CCCERROR((timer == NULL), ERROR_NULLPOINTER, 
		"timer handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((timer->base.loop == NULL || timer->base.kind != ASYNCHANDLE_TIMER), ERROR_INVALIDARGS, 
		"timer handle given is not initialized (make sure to call AsyncTimer_Init() first)")
		return (ERROR_INVALIDARGS);
	if CCCERROR((timer->callback == NULL), ERROR_INVALIDARGS, 
		"timer handle given was never started (make sure to call AsyncTimer_Start() first)")
		return (ERROR_INVALIDARGS);
	__AsyncHandle_SetActive(&timer->base, FALSE);
	if (timer->repeat > 0)
	{
		timer->deadline = timer->base.loop->now + timer->repeat;
		timer->sweep = timer->base.loop->timer_sweep;
		__AsyncHandle_SetActive(&timer->base, TRUE);
	}
	return (ERROR_NONE);
}
