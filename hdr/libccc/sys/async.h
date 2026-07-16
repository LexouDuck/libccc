/*============================================================================*\
||                                            ______________________________  ||
||  libccc/sys/async.h                       |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_SYS_ASYNC_H
#define __LIBCCC_SYS_ASYNC_H
/*!@group{libccc_sys_async,25,libccc/sys/async.h}
**
**	This header defines an asynchronous, event-loop-driven programming API.
**
**	The design of this API is heavily inspired by the famous libuv library
**	(https://libuv.org/), which powers Node.js among many other projects.
**	Like libuv, this API is built around two central concepts:
**	- the "event loop" (#s_asyncloop): the central object which drives all
**	  asynchronous operations, by running "iterations" in which it processes
**	  due timers, polls for I/O, and dispatches callbacks (see AsyncLoop_Run()).
**	- "handles" (#s_asynchandle): user-allocated objects, each of which
**	  represents one long-lived asynchronous operation, and which invoke
**	  user-provided callback functions when their event of interest occurs.
**
**	The following handle types are available:
**	- #s_async_timer:	invokes its callback after a delay (and/or at a repeating interval)
**	- #s_async_idle:	invokes its callback on every single loop iteration
**	- #s_async_event:	invokes its callback when signaled (from any thread, see AsyncEvent_Send())
**	- #s_async_poll:	invokes its callback when a file descriptor becomes readable/writable
**	- #s_async_work:	runs a function on a worker thread pool, then invokes a
**						completion callback back on the event loop thread
**
**	Just like in libuv, every handle has a `data` field: an opaque user pointer,
**	which the user is free to use to store any custom contextual data,
**	so that it may be easily retrieved from within a callback function.
**
**	The API is identical on every platform, and there are currently two
**	implementation backends:
**	- on POSIX platforms: a `poll()`-based event loop, woken up via a self-pipe
**	- on Windows: a native win32 event loop, woken up via an Event object
**	NOTE: the one exception is #s_async_poll handles, which are not yet
**	supported by the Windows backend (TODO: implement an IOCP-based backend).
**
**	Unless otherwise noted, the functions of this API are not thread-safe:
**	they must be called from the thread which runs the event loop
**	(the notable exception being AsyncEvent_Send(), whose entire purpose
**	is to allow other threads to safely wake up and signal an event loop).
**
**	Typical usage looks like this:
**	```c
**	static void	on_timeout(s_async_timer* timer)
**	{
**		IO_Output_Line("tick !");
**	}
**	
**	int	main(void)
**	{
**		s_asyncloop*	loop = AsyncLoop_New();
**		s_async_timer	timer;
**		AsyncTimer_Init(loop, &timer);
**		AsyncTimer_Start(&timer, on_timeout, 1000, 1000); // tick every second
**		AsyncLoop_Run(loop, ASYNCRUN_DEFAULT); // runs until no active handles remain
**		AsyncLoop_Delete(&loop);
**	}
**	```
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"

#include "libccc/sys/thread.h"

#ifndef __LIBCCC_SYS_IO_H
#define	__LIBCCC_SYS_IO_F
#include "libccc/sys/io.h"
#undef	__LIBCCC_SYS_IO_H
#undef	__LIBCCC_SYS_IO_F
#endif

HEADER_CPP

#ifndef __LIBCCC_SYS_ASYNC_T
#define __LIBCCC_SYS_ASYNC_T

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//! The amount of worker threads in an event loop's thread pool (see #s_async_work)
/*!
**	Like libuv's default thread pool, this is a fixed amount of threads.
**	The worker threads are only spawned lazily, upon the first call to
**	AsyncWork_Submit() for the given loop (so if you never submit any
**	thread pool work, no worker threads will ever be created).
**	You can configure this value at compile time (`-D ASYNC_THREADPOOL_SIZE=8`).
*/
#ifndef ASYNC_THREADPOOL_SIZE
#define ASYNC_THREADPOOL_SIZE	4
#endif



//!@doc The type used to represent a point in time (or duration) for the event loop, in milliseconds
/*!
**	Like libuv, the event loop measures time in milliseconds, on a monotonic
**	clock (unaffected by system clock adjustments), with an arbitrary origin.
**	The "current time" is cached by the event loop at the start of each
**	iteration (see AsyncLoop_Now()), to reduce the amount of system calls.
*/
//!@{
typedef t_u64	t_asynctime;
TYPEDEF_ALIAS(	t_asynctime, ASYNCTIME, PRIMITIVE)
//!@}



struct asyncloop;
//!@doc The event loop: the central object which drives all asynchronous operations
/*!
**	This type is analogous to libuv's `uv_loop_t`.
**
**	This struct is opaque: it is created with AsyncLoop_New(), destroyed with
**	AsyncLoop_Delete(), and its fields should never be accessed directly.
*/
//!@{
typedef struct asyncloop	s_asyncloop;
TYPEDEF_ALIAS(				s_asyncloop, ASYNCLOOP, STRUCT)
//!@}

//!@doc The set of modes in which an event loop can be run, with AsyncLoop_Run()
/*!
**	This type is analogous to libuv's `uv_run_mode`.
*/
//!@{
typedef enum asyncrun
{
	ASYNCRUN_DEFAULT = 0,	//!< Run the event loop until there are no more active handles nor pending work
	ASYNCRUN_ONCE,			//!< Run a single loop iteration: poll for I/O once (blocking, if there are no due callbacks), and dispatch callbacks
	ASYNCRUN_NOWAIT,		//!< Run a single loop iteration, but without ever blocking: poll for already-pending I/O, and dispatch callbacks
}				e_asyncrun;
TYPEDEF_ALIAS(	e_asyncrun, ASYNCRUN, ENUM)
//!@}

//!@doc The set of possible types of event loop handles (see #s_asynchandle)
//!@{
typedef enum asynchandle_kind
{
	ASYNCHANDLE_NONE = 0,	//!< This handle is not yet initialized/attached to an event loop
	ASYNCHANDLE_TIMER,		//!< This handle is a #s_async_timer
	ASYNCHANDLE_IDLE,		//!< This handle is a #s_async_idle
	ASYNCHANDLE_EVENT,		//!< This handle is a #s_async_event
	ASYNCHANDLE_POLL,		//!< This handle is a #s_async_poll
	ASYNCHANDLE_WORK,		//!< This handle is a #s_async_work
}				e_asynchandle_kind;
TYPEDEF_ALIAS(	e_asynchandle_kind, ASYNCHANDLE_KIND, ENUM)
//!@}

//!@doc The common base for every kind of event loop handle
/*!
**	This type is analogous to libuv's `uv_handle_t`.
**
**	Every handle struct (#s_async_timer, #s_async_idle, #s_async_event,
**	#s_async_poll, #s_async_work) contains this struct as its first member
**	(named `base`), such that a pointer to any handle can be safely cast to
**	a `s_asynchandle*`, in order to use the generic AsyncHandle_*() functions.
**
**	NOTE: with the exception of the `data` field (which is yours to use freely),
**	the fields of this struct are internal, and should not be modified directly.
*/
//!@{
typedef struct asynchandle
{
	void*					data;	//!< [PUBLIC] an opaque user pointer: use it to store any custom contextual data
	struct asyncloop*		loop;	//!< [internal] the event loop to which this handle is attached
	e_asynchandle_kind		kind;	//!< [internal] which type of handle this is
	t_bool					active;	//!< [internal] whether this handle is currently active (keeping the loop alive)
	struct asynchandle*		prev;	//!< [internal] the previous handle attached to the same loop
	struct asynchandle*		next;	//!< [internal] the next handle attached to the same loop
}				s_asynchandle;
TYPEDEF_ALIAS(	s_asynchandle, ASYNCHANDLE, STRUCT)
//!@}



//!@doc A timer handle: invokes its callback after a delay, and/or at a repeating interval
/*!
**	This type is analogous to libuv's `uv_timer_t`.
*/
//!@{
typedef struct async_timer	s_async_timer;
TYPEDEF_ALIAS(				s_async_timer, ASYNC_TIMER, STRUCT)
//! The type of callback function invoked when a #s_async_timer is due
typedef void	(*f_async_timer)(s_async_timer* timer);
TYPEDEF_ALIAS(	f_async_timer, ASYNC_TIMER_FUNCTION, FUNCTION)
struct async_timer
{
	s_asynchandle	base;		//!< the common handle base (contains the `data` user pointer)
	f_async_timer	callback;	//!< [internal] the function to invoke when this timer is due
	t_asynctime		deadline;	//!< [internal] the loop timestamp at which this timer is next due
	t_asynctime		repeat;		//!< [internal] the repeat interval (in ms): if non-zero, this timer re-arms itself after firing
	t_u64			sweep;		//!< [internal] used to ensure a timer fires at most once per loop iteration
};
//!@}



//!@doc An idle handle: invokes its callback on every single loop iteration
/*!
**	This type is analogous to libuv's `uv_idle_t`.
**
**	WARNING: like in libuv, an active idle handle prevents the event loop from
**	blocking (ie: the loop will spin, polling for I/O with a timeout of zero),
**	so idle handles will cause 100% CPU usage for as long as they are active.
*/
//!@{
typedef struct async_idle	s_async_idle;
TYPEDEF_ALIAS(				s_async_idle, ASYNC_IDLE, STRUCT)
//! The type of callback function invoked by a #s_async_idle on every loop iteration
typedef void	(*f_async_idle)(s_async_idle* idle);
TYPEDEF_ALIAS(	f_async_idle, ASYNC_IDLE_FUNCTION, FUNCTION)
struct async_idle
{
	s_asynchandle	base;		//!< the common handle base (contains the `data` user pointer)
	f_async_idle	callback;	//!< [internal] the function to invoke on every loop iteration
};
//!@}



//!@doc An event handle: invokes its callback when signaled (possibly from another thread)
/*!
**	This type is analogous to libuv's `uv_async_t`.
**
**	This is the one handle type whose "trigger" function (AsyncEvent_Send())
**	is thread-safe: its purpose is to allow any thread to wake up an event
**	loop (which is possibly blocked, polling for I/O), and have it execute
**	a callback on the event loop thread.
**
**	NOTE: like libuv's `uv_async_t`, the event is "coalescing": the callback
**	is invoked at most once per loop iteration, regardless of how many times
**	AsyncEvent_Send() was called since the previous invocation.
*/
//!@{
typedef struct async_event	s_async_event;
TYPEDEF_ALIAS(				s_async_event, ASYNC_EVENT, STRUCT)
//! The type of callback function invoked when a #s_async_event is signaled
typedef void	(*f_async_event)(s_async_event* event);
TYPEDEF_ALIAS(	f_async_event, ASYNC_EVENT_FUNCTION, FUNCTION)
struct async_event
{
	s_asynchandle	base;		//!< the common handle base (contains the `data` user pointer)
	f_async_event	callback;	//!< [internal] the function to invoke when this event is signaled
	t_bool			pending;	//!< [internal] whether this event has been signaled (protected by the loop's mutex)
};
//!@}



//!@doc The set of I/O event bitflags used by #s_async_poll handles
//!@{
typedef t_uint	t_asyncpoll_events;
TYPEDEF_ALIAS(	t_asyncpoll_events, ASYNCPOLL_EVENTS, PRIMITIVE)
#define ASYNCPOLL_READABLE		(1 << 0)	//!< The file descriptor has data available to read
#define ASYNCPOLL_WRITABLE		(1 << 1)	//!< The file descriptor is ready to be written to
#define ASYNCPOLL_DISCONNECT	(1 << 2)	//!< The peer of the file descriptor has disconnected (pipe/socket hangup)
#define ASYNCPOLL_ERROR			(1 << 3)	//!< An error condition occurred on the file descriptor
//!@}

//!@doc A poll handle: invokes its callback when a file descriptor becomes readable/writable
/*!
**	This type is analogous to libuv's `uv_poll_t`.
**
**	NOTE: poll handles are not yet supported by the Windows backend
**	(AsyncPoll_Init() will return an error): all of the other handle types
**	work on every platform (TODO: implement an IOCP-based backend).
*/
//!@{
typedef struct async_poll	s_async_poll;
TYPEDEF_ALIAS(				s_async_poll, ASYNC_POLL, STRUCT)
//! The type of callback function invoked when a #s_async_poll handle's file descriptor is ready
/*!
**	@param	poll	The poll handle whose file descriptor is ready
**	@param	events	The set of I/O events which occurred (bitflag of `ASYNCPOLL_*` values)
*/
typedef void	(*f_async_poll)(s_async_poll* poll, t_asyncpoll_events events);
TYPEDEF_ALIAS(	f_async_poll, ASYNC_POLL_FUNCTION, FUNCTION)
struct async_poll
{
	s_asynchandle		base;		//!< the common handle base (contains the `data` user pointer)
	f_async_poll		callback;	//!< [internal] the function to invoke when the file descriptor is ready
	t_fd				fd;			//!< [internal] the file descriptor being watched
	t_asyncpoll_events	events;		//!< [internal] the set of I/O events being watched for (bitflag of `ASYNCPOLL_*` values)
};
//!@}



//!@doc A work handle: runs a function on a worker thread pool, with a completion callback on the loop thread
/*!
**	This type is analogous to libuv's `uv_work_t` (see libuv's `uv_queue_work()`).
**
**	This is the mechanism to use for long, blocking, CPU-heavy (or otherwise
**	non-async-able) operations, so as to not block the event loop thread:
**	the `work` callback runs on one of the loop's worker pool threads, and,
**	once it completes, the `done` callback is invoked back on the event loop
**	thread (during a subsequent loop iteration).
*/
//!@{
typedef struct async_work	s_async_work;
TYPEDEF_ALIAS(				s_async_work, ASYNC_WORK, STRUCT)
//! The type of callback function used by a #s_async_work handle (for both its `work` and `done` callbacks)
typedef void	(*f_async_work)(s_async_work* work);
TYPEDEF_ALIAS(	f_async_work, ASYNC_WORK_FUNCTION, FUNCTION)
struct async_work
{
	s_asynchandle		base;		//!< the common handle base (contains the `data` user pointer)
	f_async_work		work;		//!< [internal] the function to run on a worker pool thread
	f_async_work		done;		//!< [internal] the function to invoke on the loop thread, once `work` has completed
	struct async_work*	queue_next;	//!< [internal] the next work item in the queue (protected by the loop's mutex)
};
//!@}



#endif
#ifndef __LIBCCC_SYS_ASYNC_F
#define __LIBCCC_SYS_ASYNC_F

/*============================================================================*\
||                             Event Loop Functions                           ||
\*============================================================================*/

//!@doc Allocates and initializes a new event loop
/*!
**	@nonstd, analogous to libuv's `uv_loop_init()`
**
**	The returned event loop should eventually be freed
**	with a matching call to AsyncLoop_Delete().
**
**	@returns
**	A newly allocated event loop,
**	or `NULL` if an error occurred.
*/
//!@{
_MALLOC()
s_asyncloop*				AsyncLoop_New(void);
#define c_asyncnew			AsyncLoop_New
//!@}

//!@doc Deletes the given event loop, freeing any resources associated with it
/*!
**	@nonstd, analogous to libuv's `uv_loop_close()`
**
**	The given loop must not be currently running.
**	If any thread pool work has been submitted (via AsyncWork_Submit()) and
**	has not yet completed, this function waits for all of it to complete
**	(invoking the `done` callbacks of any still-pending completed work),
**	and then joins all of the loop's worker pool threads.
**	Any handles still attached to the loop are simply detached
**	(handle structs are user-allocated: they are never freed by the loop).
**
**	@param	a_loop	The address of the event loop to delete (will be set to `NULL`)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncLoop_Delete(s_asyncloop* *a_loop);
#define c_asyncdel			AsyncLoop_Delete
//!@}

//!@doc Runs the given event loop, dispatching callbacks as their events occur
/*!
**	@nonstd, analogous to libuv's `uv_run()`
**
**	This function is the heart of the async API. Each loop "iteration"
**	performs the following steps (closely mirroring libuv's loop iteration):
**	1. the loop's cached "current time" is updated (see AsyncLoop_Now())
**	2. any due timer callbacks are invoked (in order of their deadlines)
**	3. any active idle handle callbacks are invoked
**	4. the loop polls for I/O, blocking for an appropriate amount of time
**	   (until the next timer deadline; or not blocking at all, if there are
**	   active idle handles, or pending callbacks, or in #ASYNCRUN_NOWAIT mode)
**	5. any due I/O callbacks are invoked (poll handles, signaled event
**	   handles, and the `done` callbacks of completed thread pool work)
**
**	In #ASYNCRUN_DEFAULT mode, iterations keep running until either there are
**	no more active handles nor pending work, or AsyncLoop_Stop() is called.
**	In #ASYNCRUN_ONCE and #ASYNCRUN_NOWAIT modes, a single iteration is run.
**
**	@param	loop	The event loop to run (cannot be `NULL`, must not already be running)
**	@param	mode	The mode in which to run the loop (see #e_asyncrun)
**	@returns
**	`TRUE` if the loop still has any active handles or pending work
**	(which means it should be run again at some point, typically relevant
**	for the #ASYNCRUN_ONCE/#ASYNCRUN_NOWAIT modes), otherwise `FALSE`.
*/
//!@{
t_bool						AsyncLoop_Run(s_asyncloop* loop, e_asyncrun mode);
#define c_asyncrun			AsyncLoop_Run
//!@}

//!@doc Stops the given event loop, making its AsyncLoop_Run() call return as soon as possible
/*!
**	@nonstd, analogous to libuv's `uv_stop()`
**
**	This function is safe to call from within a handle callback:
**	the current loop iteration will finish dispatching its due callbacks,
**	and then AsyncLoop_Run() will return, without polling for I/O again.
**
**	@param	loop	The event loop to stop (cannot be `NULL`)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncLoop_Stop(s_asyncloop* loop);
#define c_asyncstop			AsyncLoop_Stop
//!@}

//!@doc Checks whether the given event loop has any active handles or pending work
/*!
**	@nonstd, analogous to libuv's `uv_loop_alive()`
**
**	@param	loop	The event loop to check (cannot be `NULL`)
**	@returns
**	`TRUE` if the given loop has any active handles or pending work,
**	otherwise `FALSE`.
*/
//!@{
t_bool						AsyncLoop_IsAlive(s_asyncloop const* loop);
#define c_asyncalive		AsyncLoop_IsAlive
//!@}

//!@doc Returns the given event loop's cached "current time", in milliseconds
/*!
**	@nonstd, analogous to libuv's `uv_now()`
**
**	The returned timestamp comes from a monotonic clock, with an arbitrary
**	origin point. It is cached: it only updates once per loop iteration
**	(or when AsyncLoop_UpdateTime() is explicitly called).
**
**	@param	loop	The event loop whose cached current time to get (cannot be `NULL`)
**	@returns
**	The given event loop's cached "current time", in milliseconds.
*/
//!@{
t_asynctime					AsyncLoop_Now(s_asyncloop const* loop);
#define c_asyncnow			AsyncLoop_Now
//!@}

//!@doc Updates the given event loop's cached "current time" (see AsyncLoop_Now())
/*!
**	@nonstd, analogous to libuv's `uv_update_time()`
**
**	There is normally no need to call this function manually (the loop calls
**	it itself at the start of every iteration), unless you have long-running
**	callbacks and want subsequent timers to be scheduled more accurately.
**
**	@param	loop	The event loop whose cached current time to update (cannot be `NULL`)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncLoop_UpdateTime(s_asyncloop* loop);
#define c_asyncupdatetime	AsyncLoop_UpdateTime
//!@}



/*============================================================================*\
||                          Generic Handle Functions                          ||
\*============================================================================*/

//!@doc Checks whether the given `handle` is currently active
/*!
**	@nonstd, analogous to libuv's `uv_is_active()`
**
**	A handle is "active" when it has been started (eg: AsyncTimer_Start()),
**	and has not yet been stopped (eg: AsyncTimer_Stop()) - active handles
**	are what keeps an event loop running (see AsyncLoop_IsAlive()).
**	Any handle pointer can be passed to this function,
**	by casting it: `AsyncHandle_IsActive((s_asynchandle*)&my_timer)`
**
**	@param	handle	The handle to check (cannot be `NULL`)
**	@returns
**	`TRUE` if the given handle is currently active, otherwise `FALSE`.
*/
//!@{
t_bool						AsyncHandle_IsActive(s_asynchandle const* handle);
#define c_asyncactive		AsyncHandle_IsActive
//!@}

//!@doc Stops the given `handle` (whatever its type), making it inactive
/*!
**	@nonstd, analogous to libuv's generic handle API
**
**	This generic function dispatches to the appropriate `*_Stop()` function,
**	according to the given handle's type. Any handle pointer can be passed
**	to this function, by casting it: `AsyncHandle_Stop((s_asynchandle*)&my_timer)`
**	NOTE: thread pool work (#s_async_work) cannot be stopped/cancelled.
**
**	@param	handle	The handle to stop (cannot be `NULL`)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncHandle_Stop(s_asynchandle* handle);
#define c_asyncstophandle	AsyncHandle_Stop
//!@}

//!@doc Detaches the given `handle` from its event loop (stopping it first, if needed)
/*!
**	@nonstd, analogous to libuv's `uv_close()`
**
**	After this call, the handle is no longer attached to any event loop,
**	and its memory can be safely freed or reused (remember: handle structs
**	are always user-allocated, the loop never frees them).
**	It is safe to call this function from within any handle callback.
**	NOTE: thread pool work (#s_async_work) cannot be detached while pending.
**
**	@param	handle	The handle to detach (cannot be `NULL`)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncHandle_Detach(s_asynchandle* handle);
#define c_asyncdetach		AsyncHandle_Detach
//!@}



/*============================================================================*\
||                               Timer Functions                              ||
\*============================================================================*/

//!@doc Initializes the given `timer` handle, attaching it to the given `loop`
/*!
**	@nonstd, analogous to libuv's `uv_timer_init()`
**
**	@param	loop	The event loop to attach the timer to (cannot be `NULL`)
**	@param	timer	The timer handle to initialize (cannot be `NULL`)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncTimer_Init(s_asyncloop* loop, s_async_timer* timer);
#define c_asynctimerinit	AsyncTimer_Init
//!@}

//!@doc Starts the given `timer`: its `callback` will be invoked after `delay` milliseconds
/*!
**	@nonstd, analogous to libuv's `uv_timer_start()`
**
**	If `repeat` is non-zero, the callback is invoked first after `delay` ms,
**	and then again every `repeat` ms, until the timer is stopped.
**	If the timer was already active, it is simply re-scheduled.
**	NOTE: like in libuv, a `delay` of `0` means the callback will be
**	invoked during the *next* event loop iteration (not the current one).
**
**	@param	timer		The timer to start (cannot be `NULL`, must be initialized)
**	@param	callback	The function to invoke when the timer is due (cannot be `NULL`)
**	@param	delay		The amount of milliseconds to wait before the first callback invocation
**	@param	repeat		If non-zero, the timer re-arms itself: the callback is re-invoked every `repeat` milliseconds
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncTimer_Start(s_async_timer* timer, f_async_timer callback, t_asynctime delay, t_asynctime repeat);
#define c_asynctimerstart	AsyncTimer_Start
//!@}

//!@doc Stops the given `timer`: its callback will no longer be invoked
/*!
**	@nonstd, analogous to libuv's `uv_timer_stop()`
**
**	@param	timer	The timer to stop (cannot be `NULL`, must be initialized)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncTimer_Stop(s_async_timer* timer);
#define c_asynctimerstop	AsyncTimer_Stop
//!@}

//!@doc Restarts the given `timer`, using its `repeat` interval as the delay
/*!
**	@nonstd, analogous to libuv's `uv_timer_again()`
**
**	This is a convenience function for "de-bouncing"-style timers:
**	it stops the timer, and, if its `repeat` interval is non-zero,
**	re-starts it, scheduled for `repeat` milliseconds from now.
**
**	@param	timer	The timer to restart (cannot be `NULL`, must have been started with a non-zero `repeat` at some point)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncTimer_Restart(s_async_timer* timer);
#define c_asynctimeragain	AsyncTimer_Restart
//!@}



/*============================================================================*\
||                               Idle Functions                               ||
\*============================================================================*/

//!@doc Initializes the given `idle` handle, attaching it to the given `loop`
/*!
**	@nonstd, analogous to libuv's `uv_idle_init()`
**
**	@param	loop	The event loop to attach the idle handle to (cannot be `NULL`)
**	@param	idle	The idle handle to initialize (cannot be `NULL`)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncIdle_Init(s_asyncloop* loop, s_async_idle* idle);
#define c_asyncidleinit		AsyncIdle_Init
//!@}

//!@doc Starts the given `idle` handle: its `callback` will be invoked on every loop iteration
/*!
**	@nonstd, analogous to libuv's `uv_idle_start()`
**
**	WARNING: an active idle handle prevents the event loop from ever blocking,
**	causing 100% CPU usage for as long as it is active (see #s_async_idle).
**
**	@param	idle		The idle handle to start (cannot be `NULL`, must be initialized)
**	@param	callback	The function to invoke on every loop iteration (cannot be `NULL`)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncIdle_Start(s_async_idle* idle, f_async_idle callback);
#define c_asyncidlestart	AsyncIdle_Start
//!@}

//!@doc Stops the given `idle` handle: its callback will no longer be invoked
/*!
**	@nonstd, analogous to libuv's `uv_idle_stop()`
**
**	@param	idle	The idle handle to stop (cannot be `NULL`, must be initialized)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncIdle_Stop(s_async_idle* idle);
#define c_asyncidlestop		AsyncIdle_Stop
//!@}



/*============================================================================*\
||                               Event Functions                              ||
\*============================================================================*/

//!@doc Initializes the given `event` handle, attaching it to the given `loop`
/*!
**	@nonstd, analogous to libuv's `uv_async_init()`
**
**	NOTE: like libuv's `uv_async_init()`, this function immediately makes the
**	handle active (there is no separate "start" function for event handles):
**	an initialized event handle keeps its event loop alive, until it is
**	stopped (AsyncEvent_Stop()) or detached (AsyncHandle_Detach()).
**
**	@param	loop		The event loop to attach the event handle to (cannot be `NULL`)
**	@param	event		The event handle to initialize (cannot be `NULL`)
**	@param	callback	The function to invoke (on the loop thread) when this event is signaled (cannot be `NULL`)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncEvent_Init(s_asyncloop* loop, s_async_event* event, f_async_event callback);
#define c_asynceventinit	AsyncEvent_Init
//!@}

//!@doc Signals the given `event` handle, waking up its event loop - safe to call from any thread
/*!
**	@nonstd, analogous to libuv's `uv_async_send()`
**
**	This is the only function of this API which is safe to call from any
**	thread. It wakes up the event handle's loop (even if it is currently
**	blocked, polling for I/O), which will invoke the event's callback
**	(on the loop thread) during its current/next iteration.
**	NOTE: like libuv's `uv_async_send()`, this event is "coalescing":
**	the callback is invoked at most once per loop iteration, regardless of
**	how many times this function was called since the previous invocation.
**
**	@param	event	The event handle to signal (cannot be `NULL`, must be initialized)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncEvent_Send(s_async_event* event);
#define c_asynceventsend	AsyncEvent_Send
//!@}

//!@doc Stops the given `event` handle: it can no longer be signaled, and no longer keeps the loop alive
/*!
**	@nonstd
**
**	@param	event	The event handle to stop (cannot be `NULL`, must be initialized)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncEvent_Stop(s_async_event* event);
#define c_asynceventstop	AsyncEvent_Stop
//!@}



/*============================================================================*\
||                               Poll Functions                               ||
\*============================================================================*/

//!@doc Initializes the given `poll` handle for the given file descriptor `fd`, attaching it to the given `loop`
/*!
**	@nonstd, analogous to libuv's `uv_poll_init()`
**
**	@param	loop	The event loop to attach the poll handle to (cannot be `NULL`)
**	@param	poll	The poll handle to initialize (cannot be `NULL`)
**	@param	fd		The file descriptor to watch (must be a valid open file descriptor)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncPoll_Init(s_asyncloop* loop, s_async_poll* poll, t_fd fd);
#define c_asyncpollinit		AsyncPoll_Init
//!@}

//!@doc Starts the given `poll` handle: its `callback` is invoked whenever its fd has any of the given `events`
/*!
**	@nonstd, analogous to libuv's `uv_poll_start()`
**
**	If the poll handle was already active, it is simply updated
**	to watch for the newly given set of `events`.
**	NOTE: the #ASYNCPOLL_DISCONNECT and #ASYNCPOLL_ERROR events are always
**	watched for implicitly (they may always appear in the callback's `events`
**	argument), like the POSIX `poll()` function's `POLLHUP`/`POLLERR` events.
**
**	@param	poll		The poll handle to start (cannot be `NULL`, must be initialized)
**	@param	events		The set of I/O events to watch for (bitflag: `ASYNCPOLL_READABLE` and/or `ASYNCPOLL_WRITABLE`)
**	@param	callback	The function to invoke whenever the file descriptor is ready (cannot be `NULL`)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncPoll_Start(s_async_poll* poll, t_asyncpoll_events events, f_async_poll callback);
#define c_asyncpollstart	AsyncPoll_Start
//!@}

//!@doc Stops the given `poll` handle: its file descriptor is no longer watched
/*!
**	@nonstd, analogous to libuv's `uv_poll_stop()`
**
**	@param	poll	The poll handle to stop (cannot be `NULL`, must be initialized)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncPoll_Stop(s_async_poll* poll);
#define c_asyncpollstop		AsyncPoll_Stop
//!@}



/*============================================================================*\
||                            Thread Pool Functions                           ||
\*============================================================================*/

//!@doc Submits the given `work` to the event loop's worker thread pool
/*!
**	@nonstd, analogous to libuv's `uv_queue_work()`
**
**	The given `work` callback will be run on one of the loop's worker pool
**	threads (the pool's threads are created lazily, upon the first call to
**	this function). Once the `work` callback completes, the `done` callback
**	is invoked back on the event loop thread, during a subsequent iteration.
**	Pending work counts as "active" for the loop (see AsyncLoop_IsAlive()):
**	the loop will not stop running until all submitted work has completed
**	(and all `done` callbacks have been invoked).
**
**	WARNING: the `work` callback runs on another thread: it must not call any
**	function of this API on the loop (except AsyncEvent_Send()), and any data
**	it shares with other threads must be synchronized (eg: with a #t_mutex).
**	The `done` callback, however, runs on the loop thread, as usual.
**
**	NOTE: the work handle cannot be stopped/cancelled once submitted, and
**	it must not be freed/reused until its `done` callback has been invoked.
**
**	@param	loop	The event loop whose thread pool should run the work (cannot be `NULL`)
**	@param	work	The work handle to submit (cannot be `NULL`, must not be already-submitted pending work)
**	@param	work_callback	The function to run on a worker pool thread (cannot be `NULL`)
**	@param	done_callback	The function to invoke on the loop thread once the work completes (if `NULL`, no completion callback is invoked)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					AsyncWork_Submit(s_asyncloop* loop, s_async_work* work, f_async_work work_callback, f_async_work done_callback);
#define c_asyncworksubmit	AsyncWork_Submit
#define AsyncWork_Queue		AsyncWork_Submit
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
