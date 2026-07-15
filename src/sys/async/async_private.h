/*
**	libccc/sys/async: private internal header (not installed, not part of the public API)
**
**	This header defines the internals of the `s_asyncloop` struct, as well as
**	the internal helper functions which are shared between the several source
**	files of the async module (loop.c, handle.c, timer.c, idle.c, event.c,
**	poll.c, work.c).
*/

#ifndef __LIBCCC_SYS_ASYNC_PRIVATE_H
#define __LIBCCC_SYS_ASYNC_PRIVATE_H

#include "libccc.h"
#include "libccc/sys/thread.h"
#include "libccc/sys/async.h"

#include LIBCONFIG_ERROR_INCLUDE



//! The internals of the event loop struct (see the public, opaque `s_asyncloop` type)
struct asyncloop
{
	// handle bookkeeping
	s_asynchandle*	handles;		//!< the head of the intrusive doubly-linked list of all attached handles
	s_asynchandle*	iter_next;		//!< iteration cursor: allows handles to be safely detached from within callbacks
	t_uint			active;			//!< the amount of currently active handles + pending thread pool work items
	t_asynctime		now;			//!< the cached "current time", in ms (see AsyncLoop_Now())
	t_u64			timer_sweep;	//!< incremented at each timer-dispatching phase (ensures each timer fires at most once per iteration)
	t_bool			running;		//!< whether this loop is currently inside a AsyncLoop_Run() call
	t_bool			stop;			//!< whether AsyncLoop_Stop() has been called (makes AsyncLoop_Run() return)
	// polling
	void*			pollfds;		//!< grown-on-demand buffer of `struct pollfd`, used during the polling phase
	s_async_poll**	pollhandles;	//!< grown-on-demand buffer of poll handle pointers (parallel to `pollfds`)
	t_uint			poll_capacity;	//!< the current capacity (in items) of the `pollfds`/`pollhandles` buffers
	t_uint			poll_amount;	//!< the amount of items currently in the `pollfds`/`pollhandles` buffers
	t_uint			poll_index;		//!< poll-dispatching cursor: allows poll handles to be safely stopped from within callbacks
	t_fd			wakeup[2];		//!< the self-pipe used to wake up the loop from other threads (`[0]`: read end, `[1]`: write end)
	// cross-thread state (protected by `mutex`)
	t_mutex			mutex;			//!< protects: event handles' `pending` flags, and the thread pool work queues
	t_cond			pool_cond;		//!< signaled when work is added to `queue_todo` (or when `pool_shutdown` is set)
	t_bool			pool_started;	//!< whether the worker pool threads have been spawned yet (they are spawned lazily)
	t_bool			pool_shutdown;	//!< tells the worker pool threads to exit (once `queue_todo` is empty)
	t_thread		pool_threads[ASYNC_THREADPOOL_SIZE];	//!< the worker pool threads
	s_async_work*	queue_todo;		//!< the head of the queue of submitted, not-yet-executed work items
	s_async_work*	queue_todo_last;//!< the tail of the `queue_todo` queue
	s_async_work*	queue_done;		//!< the head of the queue of completed work items, awaiting their `done` callback
	s_async_work*	queue_done_last;//!< the tail of the `queue_done` queue
};



//! Attaches the given `handle` to the given `loop` (linking it into the loop's handle list)
void		__AsyncLoop_Attach(s_asyncloop* loop, s_asynchandle* handle, e_asynchandle_kind kind);

//! Detaches the given `handle` from its loop (unlinking it, in an iteration-safe manner)
void		__AsyncLoop_Detach(s_asynchandle* handle);

//! Sets the given `handle`'s `active` flag, updating its loop's active handle count accordingly
void		__AsyncHandle_SetActive(s_asynchandle* handle, t_bool active);

//! Wakes up the given `loop` (writing a byte to its self-pipe) - safe to call from any thread
void		__AsyncLoop_Wakeup(s_asyncloop* loop);

//! Ensures the given `loop`'s worker pool threads have been spawned (spawning them if needed)
e_cccerror	__AsyncLoop_PoolEnsure(s_asyncloop* loop);

//! Runs the `done` callbacks of all completed thread pool work items (must be called on the loop thread)
void		__AsyncLoop_RunWorkDone(s_asyncloop* loop);



#endif
