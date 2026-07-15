
#ifndef __NOSTD__
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L	// needed to expose POSIX APIs, when compiling with a strict `-std=c**` option
	#endif
#endif
#include "libccc.h"
#include "libccc/sys/async.h"

#ifndef __NOSTD__
	#include <unistd.h>
#else
	long int	write(int fd, void const* buffer, unsigned long int n);
#endif

#include "async_private.h"

#include LIBCONFIG_ERROR_INCLUDE



void	__AsyncLoop_Attach(s_asyncloop* loop, s_asynchandle* handle, e_asynchandle_kind kind)
{
	handle->loop = loop;
	handle->kind = kind;
	handle->active = FALSE;
	handle->prev = NULL;
	handle->next = loop->handles;
	if (loop->handles)
		loop->handles->prev = handle;
	loop->handles = handle;
}



void	__AsyncLoop_Detach(s_asynchandle* handle)
{
	s_asyncloop*	loop = handle->loop;
	t_uint			i;

	// keep the loop's various iteration cursors valid, if they point to this handle
	if (loop->iter_next == handle)
		loop->iter_next = handle->next;
	for (i = loop->poll_index; i < loop->poll_amount; ++i)
	{
		if (loop->pollhandles[i] == (s_async_poll*)handle)
			loop->pollhandles[i] = NULL;
	}
	// unlink this handle from the loop's handle list
	if (handle->prev)
		handle->prev->next = handle->next;
	else
		loop->handles = handle->next;
	if (handle->next)
		handle->next->prev = handle->prev;
	handle->loop = NULL;
	handle->kind = ASYNCHANDLE_NONE;
	handle->prev = NULL;
	handle->next = NULL;
}



void	__AsyncHandle_SetActive(s_asynchandle* handle, t_bool active)
{
	if (handle->active == active)
		return;
	handle->active = active;
	if (active)
		handle->loop->active += 1;
	else
		handle->loop->active -= 1;
}



void	__AsyncLoop_Wakeup(s_asyncloop* loop)
{
	char	byte = 0;
	long	result;

	result = write(loop->wakeup[1], &byte, 1);
	(void)result; // a full pipe means a wakeup is already pending: nothing to do
}



_INLINE()
t_bool	AsyncHandle_IsActive(s_asynchandle const* handle)
{
	if CCCERROR((handle == NULL), ERROR_NULLPOINTER, 
		"handle given is NULL")
		return (FALSE);
	return (handle->active);
}



e_cccerror	AsyncHandle_Stop(s_asynchandle* handle)
{
	if CCCERROR((handle == NULL), ERROR_NULLPOINTER, 
		"handle given is NULL")
		return (ERROR_NULLPOINTER);
	switch (handle->kind)
	{
		case ASYNCHANDLE_TIMER:	return (AsyncTimer_Stop((s_async_timer*)handle));
		case ASYNCHANDLE_IDLE:	return (AsyncIdle_Stop ((s_async_idle *)handle));
		case ASYNCHANDLE_EVENT:	return (AsyncEvent_Stop((s_async_event*)handle));
		case ASYNCHANDLE_POLL:	return (AsyncPoll_Stop ((s_async_poll *)handle));
		case ASYNCHANDLE_WORK:
			if CCCERROR((handle->active), ERROR_INVALIDARGS, 
				"thread pool work cannot be stopped/cancelled once submitted")
				return (ERROR_INVALIDARGS);
			return (ERROR_NONE);
		default:
			if CCCERROR((TRUE), ERROR_INVALIDENUM, 
				"handle given has an invalid type (%i): is it initialized ?", (int)handle->kind)
				return (ERROR_INVALIDENUM);
	}
	return (ERROR_NONE);
}



e_cccerror	AsyncHandle_Detach(s_asynchandle* handle)
{
	e_cccerror	error;

	if CCCERROR((handle == NULL), ERROR_NULLPOINTER, 
		"handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((handle->loop == NULL), ERROR_INVALIDARGS, 
		"handle given is not attached to any event loop")
		return (ERROR_INVALIDARGS);
	if CCCERROR((handle->kind == ASYNCHANDLE_WORK && handle->active), ERROR_INVALIDARGS, 
		"thread pool work cannot be detached while it is pending")
		return (ERROR_INVALIDARGS);
	if (handle->active)
	{
		error = AsyncHandle_Stop(handle);
		if (error != ERROR_NONE)
			return (error);
	}
	__AsyncLoop_Detach(handle);
	return (ERROR_NONE);
}
