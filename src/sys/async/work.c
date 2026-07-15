
#ifndef __NOSTD__
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L	// needed to expose POSIX APIs, when compiling with a strict `-std=c**` option
	#endif
#endif
#include "libccc.h"
#include "libccc/sys/async.h"

#include "async_private.h"

#include LIBCONFIG_ERROR_INCLUDE



//! The entry point function for each of the loop's worker pool threads (like libuv's `worker()`)
static void*	__AsyncWork_Worker(void* arg)
{
	s_asyncloop*	loop = (s_asyncloop*)arg;
	s_async_work*	work;

	while (TRUE)
	{
		Mutex_Lock(&loop->mutex);
		while (loop->queue_todo == NULL && !loop->pool_shutdown)
		{
			Cond_Wait(&loop->pool_cond, &loop->mutex);
		}
		if (loop->queue_todo == NULL) // (implies `pool_shutdown`: the queue has been fully drained)
		{
			Mutex_Unlock(&loop->mutex);
			return (NULL);
		}
		// pop the next work item from the "todo" queue
		work = loop->queue_todo;
		loop->queue_todo = work->queue_next;
		if (loop->queue_todo == NULL)
			loop->queue_todo_last = NULL;
		work->queue_next = NULL;
		Mutex_Unlock(&loop->mutex);
		// run the work callback (on this worker thread)
		work->work(work);
		// push the completed work item onto the "done" queue
		Mutex_Lock(&loop->mutex);
		if (loop->queue_done_last)
			loop->queue_done_last->queue_next = work;
		else
			loop->queue_done = work;
		loop->queue_done_last = work;
		Mutex_Unlock(&loop->mutex);
		// wake up the event loop, so that it dispatches the `done` callback
		__AsyncLoop_Wakeup(loop);
	}
}



e_cccerror	__AsyncLoop_PoolEnsure(s_asyncloop* loop)
{
	e_cccerror	error;
	t_uint		i;

	if (loop->pool_started)
		return (ERROR_NONE);
	loop->pool_shutdown = FALSE;
	for (i = 0; i < ASYNC_THREADPOOL_SIZE; ++i)
	{
		error = Thread_New(&loop->pool_threads[i], __AsyncWork_Worker, loop);
		if CCCERROR((error != ERROR_NONE), ERROR_SYSTEM, 
			"could not spawn event loop worker pool thread %u of %u", i + 1, (t_uint)ASYNC_THREADPOOL_SIZE)
		{
			// join any threads which were successfully spawned, to not leak them
			Mutex_Lock(&loop->mutex);
			loop->pool_shutdown = TRUE;
			Cond_NotifyAll(&loop->pool_cond);
			Mutex_Unlock(&loop->mutex);
			while (i > 0)
			{
				i -= 1;
				Thread_Join(loop->pool_threads[i], NULL);
			}
			return (ERROR_SYSTEM);
		}
	}
	loop->pool_started = TRUE;
	return (ERROR_NONE);
}



void	__AsyncLoop_RunWorkDone(s_asyncloop* loop)
{
	s_async_work*	done;
	s_async_work*	work;

	// steal the entire "done" queue at once (so callbacks run without holding the mutex)
	Mutex_Lock(&loop->mutex);
	done = loop->queue_done;
	loop->queue_done = NULL;
	loop->queue_done_last = NULL;
	Mutex_Unlock(&loop->mutex);
	while (done)
	{
		work = done;
		done = done->queue_next;
		work->queue_next = NULL;
		__AsyncHandle_SetActive(&work->base, FALSE);
		__AsyncLoop_Detach(&work->base); // the work handle can now be freed/reused/resubmitted
		if (work->done)
			work->done(work);
	}
}



e_cccerror	AsyncWork_Submit(s_asyncloop* loop, s_async_work* work, f_async_work work_callback, f_async_work done_callback)
{
	e_cccerror	error;

	if CCCERROR((loop == NULL), ERROR_NULLPOINTER, 
		"event loop given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((work == NULL), ERROR_NULLPOINTER, 
		"work handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((work_callback == NULL), ERROR_NULLPOINTER, 
		"work callback function given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((work->base.kind == ASYNCHANDLE_WORK && work->base.active), ERROR_INVALIDARGS, 
		"work handle given is already-submitted pending work")
		return (ERROR_INVALIDARGS);
	error = __AsyncLoop_PoolEnsure(loop);
	if (error != ERROR_NONE)
		return (error);
	work->work = work_callback;
	work->done = done_callback;
	work->queue_next = NULL;
	__AsyncLoop_Attach(loop, &work->base, ASYNCHANDLE_WORK);
	__AsyncHandle_SetActive(&work->base, TRUE); // pending work keeps the loop alive
	// push the work item onto the "todo" queue, and wake up one worker pool thread
	Mutex_Lock(&loop->mutex);
	if (loop->queue_todo_last)
		loop->queue_todo_last->queue_next = work;
	else
		loop->queue_todo = work;
	loop->queue_todo_last = work;
	Cond_NotifyOne(&loop->pool_cond);
	Mutex_Unlock(&loop->mutex);
	return (ERROR_NONE);
}
