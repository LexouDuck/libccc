
#ifndef __NOSTD__
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L	// needed to expose POSIX APIs, when compiling with a strict `-std=c**` option
	#endif
#endif
#include "libccc.h"
#include "libccc/sys/async.h"

#include "async_private.h"

#include LIBCONFIG_ERROR_INCLUDE



e_cccerror	AsyncPoll_Init(s_asyncloop* loop, s_async_poll* poll, t_fd fd)
{
	if CCCERROR((loop == NULL), ERROR_NULLPOINTER, 
		"event loop given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((poll == NULL), ERROR_NULLPOINTER, 
		"poll handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((fd < 0), ERROR_INVALIDARGS, 
		"file descriptor given has a negative value: %i", fd)
		return (ERROR_INVALIDARGS);
	poll->base.data = NULL;
	poll->callback = NULL;
	poll->fd = fd;
	poll->events = 0;
	__AsyncLoop_Attach(loop, &poll->base, ASYNCHANDLE_POLL);
	return (ERROR_NONE);
}



e_cccerror	AsyncPoll_Start(s_async_poll* poll, t_asyncpoll_events events, f_async_poll callback)
{
	if CCCERROR((poll == NULL), ERROR_NULLPOINTER, 
		"poll handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((poll->base.loop == NULL || poll->base.kind != ASYNCHANDLE_POLL), ERROR_INVALIDARGS, 
		"poll handle given is not initialized (make sure to call AsyncPoll_Init() first)")
		return (ERROR_INVALIDARGS);
	if CCCERROR((callback == NULL), ERROR_NULLPOINTER, 
		"poll callback function given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR(((events & (ASYNCPOLL_READABLE | ASYNCPOLL_WRITABLE)) == 0), ERROR_INVALIDARGS, 
		"poll events bitflag given must contain at least one of ASYNCPOLL_READABLE or ASYNCPOLL_WRITABLE")
		return (ERROR_INVALIDARGS);
	poll->callback = callback;
	poll->events = events;
	__AsyncHandle_SetActive(&poll->base, TRUE);
	return (ERROR_NONE);
}



e_cccerror	AsyncPoll_Stop(s_async_poll* poll)
{
	t_uint	i;

	if CCCERROR((poll == NULL), ERROR_NULLPOINTER, 
		"poll handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((poll->base.loop == NULL || poll->base.kind != ASYNCHANDLE_POLL), ERROR_INVALIDARGS, 
		"poll handle given is not initialized (make sure to call AsyncPoll_Init() first)")
		return (ERROR_INVALIDARGS);
	// if this is called from within a poll callback, discard any not-yet-dispatched events for this handle
	for (i = poll->base.loop->poll_index; i < poll->base.loop->poll_amount; ++i)
	{
		if (poll->base.loop->pollhandles[i] == poll)
			poll->base.loop->pollhandles[i] = NULL;
	}
	__AsyncHandle_SetActive(&poll->base, FALSE);
	return (ERROR_NONE);
}
