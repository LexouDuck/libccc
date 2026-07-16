
#if defined(_WIN32)
	#if !defined(_WIN32_WINNT) || (_WIN32_WINNT < 0x0600)
	#undef  _WIN32_WINNT
	#define _WIN32_WINNT	0x0600	// require Windows Vista or later (for `GetTickCount64()`)
	#endif
#elif !defined(__NOSTD__)
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L	// needed to expose POSIX APIs, when compiling with a strict `-std=c**` option
	#endif
#endif
#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/sys/async.h"

#if defined(_WIN32)
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>	// TODO handle __NOSTD__ for the win32 backend ?
#elif !defined(__NOSTD__)
	#include <unistd.h>
	#include <fcntl.h>
	#include <poll.h>
	#include <time.h>
	#include <errno.h>
#else
	int	pipe(int pipefd[2]);
	int	close(int fd);
	long int	read(int fd, void* buffer, unsigned long int n);
	int	fcntl(int fd, int cmd, ...);
	struct pollfd { int fd; short events; short revents; };
	int	poll(struct pollfd* fds, unsigned long int nfds, int timeout);
	int	clock_gettime(int clockid, struct timespec* result);
	#define CLOCK_MONOTONIC	1 // TODO find platform-specific value
	#define F_GETFL	3 // TODO find platform-specific value
	#define F_SETFL	4 // TODO find platform-specific value
	#define O_NONBLOCK	04000 // TODO find platform-specific value
	#define POLLIN	0x01 // TODO find platform-specific value
	#define POLLOUT	0x04 // TODO find platform-specific value
	#define POLLERR	0x08 // TODO find platform-specific value
	#define POLLHUP	0x10 // TODO find platform-specific value
#endif

#include "async_private.h"

#include LIBCONFIG_ERROR_INCLUDE



#if !defined(_WIN32)
static e_cccerror	__AsyncLoop_SetNonBlocking(t_fd fd)
{
	int	flags;

	flags = fcntl(fd, F_GETFL, 0);
	if CCCERROR((flags < 0), ERROR_SYSTEM, 
		"could not get file descriptor flags")
		return (ERROR_SYSTEM);
	if CCCERROR((fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0), ERROR_SYSTEM, 
		"could not set file descriptor as non-blocking")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}
#endif



s_asyncloop*	AsyncLoop_New(void)
{
	s_asyncloop*	loop;

	loop = (s_asyncloop*)Memory_New(sizeof(s_asyncloop));
	if CCCERROR((loop == NULL), ERROR_ALLOCFAILURE, 
		"could not allocate new event loop")
		return (NULL);
#if defined(_WIN32)
	loop->wakeup_event = (void*)CreateEventW(NULL, FALSE, FALSE, NULL); // auto-reset, initially unsignaled
	if CCCERROR((loop->wakeup_event == NULL), ERROR_SYSTEM, 
		"could not create event loop wakeup event (GetLastError: %lu)", GetLastError())
	{
		Memory_Delete((void**)&loop);
		return (NULL);
	}
	if (Mutex_Init(&loop->mutex) != ERROR_NONE ||
		Cond_Init(&loop->pool_cond) != ERROR_NONE)
	{
		CloseHandle((HANDLE)loop->wakeup_event);
		Memory_Delete((void**)&loop);
		return (NULL);
	}
#else
	if CCCERROR((pipe(loop->wakeup) != 0), ERROR_SYSTEM, 
		"could not create event loop wakeup pipe")
	{
		Memory_Delete((void**)&loop);
		return (NULL);
	}
	if (__AsyncLoop_SetNonBlocking(loop->wakeup[0]) != ERROR_NONE ||
		__AsyncLoop_SetNonBlocking(loop->wakeup[1]) != ERROR_NONE ||
		Mutex_Init(&loop->mutex) != ERROR_NONE)
	{
		close(loop->wakeup[0]);
		close(loop->wakeup[1]);
		Memory_Delete((void**)&loop);
		return (NULL);
	}
	if (Cond_Init(&loop->pool_cond) != ERROR_NONE)
	{
		Mutex_Delete(&loop->mutex);
		close(loop->wakeup[0]);
		close(loop->wakeup[1]);
		Memory_Delete((void**)&loop);
		return (NULL);
	}
#endif
	AsyncLoop_UpdateTime(loop);
	return (loop);
}



//! Shuts down the given loop's worker thread pool: waits for all pending work to complete
static void	__AsyncLoop_PoolShutdown(s_asyncloop* loop)
{
	if (!loop->pool_started)
		return;
	Mutex_Lock(&loop->mutex);
	loop->pool_shutdown = TRUE;
	Cond_NotifyAll(&loop->pool_cond);
	Mutex_Unlock(&loop->mutex);
	for (t_uint i = 0; i < ASYNC_THREADPOOL_SIZE; ++i)
	{
		Thread_Join(loop->pool_threads[i], NULL);
	}
	loop->pool_started = FALSE;
}

e_cccerror	AsyncLoop_Delete(s_asyncloop* *a_loop)
{
	s_asyncloop*	loop;

	if CCCERROR((a_loop == NULL || *a_loop == NULL), ERROR_NULLPOINTER, 
		"event loop given is NULL")
		return (ERROR_NULLPOINTER);
	loop = *a_loop;
	if CCCERROR((loop->running), ERROR_INVALIDARGS, 
		"cannot delete an event loop while it is running")
		return (ERROR_INVALIDARGS);
	// wait for any pending thread pool work to complete, and run the `done` callbacks
	__AsyncLoop_PoolShutdown(loop);
	__AsyncLoop_RunWorkDone(loop);
	// detach any remaining handles (handle structs are user-allocated: never freed here)
	while (loop->handles)
	{
		AsyncHandle_Detach(loop->handles);
	}
	Cond_Delete(&loop->pool_cond);
	Mutex_Delete(&loop->mutex);
#if defined(_WIN32)
	CloseHandle((HANDLE)loop->wakeup_event);
#else
	close(loop->wakeup[0]);
	close(loop->wakeup[1]);
#endif
	if (loop->pollfds)
		Memory_Delete(&loop->pollfds);
	if (loop->pollhandles)
		Memory_Delete((void**)&loop->pollhandles);
	Memory_Delete((void**)a_loop);
	return (ERROR_NONE);
}



_INLINE()
t_bool	AsyncLoop_IsAlive(s_asyncloop const* loop)
{
	if CCCERROR((loop == NULL), ERROR_NULLPOINTER, 
		"event loop given is NULL")
		return (FALSE);
	return (loop->active > 0);
}

_INLINE()
t_asynctime	AsyncLoop_Now(s_asyncloop const* loop)
{
	if CCCERROR((loop == NULL), ERROR_NULLPOINTER, 
		"event loop given is NULL")
		return (0);
	return (loop->now);
}

e_cccerror	AsyncLoop_UpdateTime(s_asyncloop* loop)
{
	if CCCERROR((loop == NULL), ERROR_NULLPOINTER, 
		"event loop given is NULL")
		return (ERROR_NULLPOINTER);
#if defined(_WIN32)
	{
		LARGE_INTEGER	counter;
		static t_u64	frequency = 0; // ticks per second: fixed at system boot (benign race: every thread computes the same value)

		if (frequency == 0)
		{
			LARGE_INTEGER	f;
			QueryPerformanceFrequency(&f); // (cannot fail on Windows XP or later)
			frequency = (t_u64)f.QuadPart;
		}
		// NOTE: `QueryPerformanceCounter()` is used rather than `GetTickCount64()`,
		// because the latter only has the granularity of the system timer tick
		// (usually ~15.6ms), which is too coarse for short timer deadlines
		if CCCERROR((QueryPerformanceCounter(&counter) == 0), ERROR_SYSTEM, 
			"could not get the current monotonic time (GetLastError: %lu)", GetLastError())
			return (ERROR_SYSTEM);
		loop->now = (t_asynctime)((t_u64)counter.QuadPart * 1000 / frequency);
		return (ERROR_NONE);
	}
#else
	{
		struct timespec	t;

		if CCCERROR((clock_gettime(CLOCK_MONOTONIC, &t) != 0), ERROR_SYSTEM, 
			"could not get the current monotonic time")
			return (ERROR_SYSTEM);
		loop->now = ((t_asynctime)t.tv_sec * 1000) + ((t_asynctime)t.tv_nsec / 1000000);
		return (ERROR_NONE);
	}
#endif
}

e_cccerror	AsyncLoop_Stop(s_asyncloop* loop)
{
	if CCCERROR((loop == NULL), ERROR_NULLPOINTER, 
		"event loop given is NULL")
		return (ERROR_NULLPOINTER);
	loop->stop = TRUE;
	return (ERROR_NONE);
}



//! Runs the callbacks of every timer which is due, in order of their deadlines (like libuv's `uv__run_timers()`)
static void	__AsyncLoop_RunTimers(s_asyncloop* loop)
{
	s_asynchandle*	handle;
	s_async_timer*	timer;
	s_async_timer*	due;

	loop->timer_sweep += 1;
	while (TRUE)
	{
		// find the not-yet-fired due timer with the smallest deadline
		// TODO use a min-heap (like libuv does), rather than this O(n^2) scan
		due = NULL;
		for (handle = loop->handles; handle; handle = handle->next)
		{
			if (handle->kind != ASYNCHANDLE_TIMER || !handle->active)
				continue;
			timer = (s_async_timer*)handle;
			if (timer->sweep == loop->timer_sweep) // already fired during this iteration
				continue;
			if (timer->deadline > loop->now) // not due yet
				continue;
			if (due == NULL || timer->deadline < due->deadline)
				due = timer;
		}
		if (due == NULL)
			return;
		due->sweep = loop->timer_sweep; // ensure this timer fires at most once per iteration
		if (due->repeat > 0)
			due->deadline = loop->now + due->repeat; // re-arm the repeating timer
		else
			__AsyncHandle_SetActive(&due->base, FALSE); // one-shot timer: becomes inactive
		due->callback(due);
	}
}



//! Runs the callbacks of every active idle handle (like libuv's `uv__run_idle()`)
static void	__AsyncLoop_RunIdle(s_asyncloop* loop)
{
	s_asynchandle*	handle;
	s_async_idle*	idle;

	handle = loop->handles;
	while (handle)
	{
		loop->iter_next = handle->next; // (callbacks can safely detach any handle)
		if (handle->kind == ASYNCHANDLE_IDLE && handle->active)
		{
			idle = (s_async_idle*)handle;
			idle->callback(idle);
		}
		handle = loop->iter_next;
	}
	loop->iter_next = NULL;
}



//! Runs the callbacks of every signaled event handle
static void	__AsyncLoop_RunEvents(s_asyncloop* loop)
{
	s_asynchandle*	handle;
	s_async_event*	event;
	t_bool			pending;

	handle = loop->handles;
	while (handle)
	{
		loop->iter_next = handle->next; // (callbacks can safely detach any handle)
		if (handle->kind == ASYNCHANDLE_EVENT && handle->active)
		{
			event = (s_async_event*)handle;
			Mutex_Lock(&loop->mutex);
			pending = event->pending;
			event->pending = FALSE;
			Mutex_Unlock(&loop->mutex);
			if (pending)
				event->callback(event);
		}
		handle = loop->iter_next;
	}
	loop->iter_next = NULL;
}



//! Checks whether the given loop has any completed work items awaiting their `done` callback
static t_bool	__AsyncLoop_HasWorkDone(s_asyncloop* loop)
{
	t_bool	result;

	Mutex_Lock(&loop->mutex);
	result = (loop->queue_done != NULL);
	Mutex_Unlock(&loop->mutex);
	return (result);
}

//! Computes how long the polling phase may block for, in ms (like libuv's `uv__backend_timeout()`): `-1` means "indefinitely"
static int	__AsyncLoop_PollTimeout(s_asyncloop* loop, e_asyncrun mode)
{
	s_asynchandle*	handle;
	t_bool			has_timer = FALSE;
	t_asynctime		deadline = 0;

	if (mode == ASYNCRUN_NOWAIT || loop->stop)
		return (0);
	if (loop->active == 0)
		return (0); // no more active handles nor pending work: do not block (the loop is about to terminate), like libuv's `uv_backend_timeout()`
	if (__AsyncLoop_HasWorkDone(loop))
		return (0); // completed work is awaiting dispatch: do not block
	for (handle = loop->handles; handle; handle = handle->next)
	{
		if (!handle->active)
			continue;
		if (handle->kind == ASYNCHANDLE_IDLE)
			return (0); // active idle handles prevent the loop from ever blocking
		if (handle->kind == ASYNCHANDLE_TIMER)
		{
			s_async_timer* timer = (s_async_timer*)handle;
			if (!has_timer || timer->deadline < deadline)
			{
				has_timer = TRUE;
				deadline = timer->deadline;
			}
		}
	}
	if (!has_timer)
		return (-1); // no timers: block indefinitely (the wakeup pipe can always interrupt the poll)
	if (deadline <= loop->now)
		return (0);
	if (deadline - loop->now > 0x7FFFFFFF)
		return (0x7FFFFFFF);
	return ((int)(deadline - loop->now));
}



#if defined(_WIN32)

//! The polling phase of a loop iteration, win32 version: waits on the loop's wakeup Event
static void	__AsyncLoop_Poll(s_asyncloop* loop, int timeout)
{
	DWORD	result;

	// NOTE: there can be no active poll handles on Windows (AsyncPoll_Init() is
	// not supported by this backend), so the polling phase only has to wait for
	// the loop's wakeup Event object (which is auto-reset: waiting consumes it)
	result = WaitForSingleObject((HANDLE)loop->wakeup_event, (timeout < 0 ? INFINITE : (DWORD)timeout));
	if CCCERROR((result == WAIT_FAILED), ERROR_SYSTEM, 
		"error while polling for I/O (GetLastError: %lu)", GetLastError())
		return;
}

#else

//! Grows the loop's `pollfds`/`pollhandles` buffers to hold at least `amount` items
static e_cccerror	__AsyncLoop_PollReserve(s_asyncloop* loop, t_uint amount)
{
	t_uint	capacity;
	void*	pollfds;
	void*	pollhandles;

	if (amount <= loop->poll_capacity)
		return (ERROR_NONE);
	capacity = (loop->poll_capacity == 0 ? 8 : loop->poll_capacity);
	while (capacity < amount)
		capacity *= 2;
	pollfds     = Memory_New(capacity * sizeof(struct pollfd));
	pollhandles = Memory_New(capacity * sizeof(s_async_poll*));
	if CCCERROR((pollfds == NULL || pollhandles == NULL), ERROR_ALLOCFAILURE, 
		"could not grow event loop polling buffers")
	{
		if (pollfds)		Memory_Delete(&pollfds);
		if (pollhandles)	Memory_Delete(&pollhandles);
		return (ERROR_ALLOCFAILURE);
	}
	if (loop->pollfds)		Memory_Delete(&loop->pollfds);
	if (loop->pollhandles)	Memory_Delete((void**)&loop->pollhandles);
	loop->pollfds = pollfds;
	loop->pollhandles = (s_async_poll**)pollhandles;
	loop->poll_capacity = capacity;
	return (ERROR_NONE);
}

//! The polling phase of a loop iteration: waits for I/O, then dispatches poll handle callbacks (like libuv's `uv__io_poll()`)
static void	__AsyncLoop_Poll(s_asyncloop* loop, int timeout)
{
	s_asynchandle*	handle;
	s_async_poll*	pollhandle;
	struct pollfd*	fds;
	t_uint			amount;
	int				result;
	char			buffer[256];

	// build the pollfd array: the wakeup pipe read-end, followed by every active poll handle
	amount = 1;
	for (handle = loop->handles; handle; handle = handle->next)
	{
		if (handle->kind == ASYNCHANDLE_POLL && handle->active)
			amount += 1;
	}
	if (__AsyncLoop_PollReserve(loop, amount) != ERROR_NONE)
		return;
	fds = (struct pollfd*)loop->pollfds;
	fds[0].fd = loop->wakeup[0];
	fds[0].events = POLLIN;
	fds[0].revents = 0;
	loop->pollhandles[0] = NULL;
	amount = 1;
	for (handle = loop->handles; handle; handle = handle->next)
	{
		if (handle->kind != ASYNCHANDLE_POLL || !handle->active)
			continue;
		pollhandle = (s_async_poll*)handle;
		fds[amount].fd = pollhandle->fd;
		fds[amount].events = 0;
		if (pollhandle->events & ASYNCPOLL_READABLE)	fds[amount].events |= POLLIN;
		if (pollhandle->events & ASYNCPOLL_WRITABLE)	fds[amount].events |= POLLOUT;
		fds[amount].revents = 0;
		loop->pollhandles[amount] = pollhandle;
		amount += 1;
	}
	loop->poll_amount = amount;
	// wait for I/O
	result = poll(fds, amount, timeout);
	if (result < 0)
	{
		if CCCERROR((errno != EINTR), ERROR_SYSTEM, 
			"error while polling for I/O")
			return;
		return; // the poll was interrupted by a signal: simply proceed with the loop iteration
	}
	// drain the wakeup pipe (its only purpose is to interrupt the `poll()` call)
	if (fds[0].revents & POLLIN)
	{
		while (read(loop->wakeup[0], buffer, sizeof(buffer)) > 0)
			;
	}
	// dispatch the poll handle callbacks
	loop->poll_index = 1;
	while (loop->poll_index < loop->poll_amount)
	{
		t_uint	i = loop->poll_index;
		t_asyncpoll_events	events = 0;

		pollhandle = loop->pollhandles[i]; // (can be NULL, if the handle was stopped by a previous callback)
		if (fds[i].revents & POLLIN)	events |= ASYNCPOLL_READABLE;
		if (fds[i].revents & POLLOUT)	events |= ASYNCPOLL_WRITABLE;
		if (fds[i].revents & POLLHUP)	events |= ASYNCPOLL_DISCONNECT;
		if (fds[i].revents & POLLERR)	events |= ASYNCPOLL_ERROR;
		loop->poll_index += 1;
		if (pollhandle && events)
			pollhandle->callback(pollhandle, events);
	}
	loop->poll_amount = 0;
	loop->poll_index = 0;
}

#endif



t_bool	AsyncLoop_Run(s_asyncloop* loop, e_asyncrun mode)
{
	int	timeout;

	if CCCERROR((loop == NULL), ERROR_NULLPOINTER, 
		"event loop given is NULL")
		return (FALSE);
	if CCCERROR((loop->running), ERROR_INVALIDARGS, 
		"event loop given is already running (AsyncLoop_Run() cannot be called recursively)")
		return (FALSE);
	loop->stop = FALSE;
	loop->running = TRUE;
	while (AsyncLoop_IsAlive(loop) && !loop->stop)
	{
		AsyncLoop_UpdateTime(loop);
		__AsyncLoop_RunTimers(loop);
		__AsyncLoop_RunIdle(loop);
		timeout = __AsyncLoop_PollTimeout(loop, mode);
		__AsyncLoop_Poll(loop, timeout);
		__AsyncLoop_RunEvents(loop);
		__AsyncLoop_RunWorkDone(loop);
		if (mode == ASYNCRUN_ONCE)
		{
			// in "once" mode, due timers are run one final time after the polling
			// phase (just like libuv does), since the poll may have blocked until
			// the very moment where the next timer was due
			AsyncLoop_UpdateTime(loop);
			__AsyncLoop_RunTimers(loop);
		}
		if (mode == ASYNCRUN_ONCE || mode == ASYNCRUN_NOWAIT)
			break;
	}
	loop->running = FALSE;
	return (AsyncLoop_IsAlive(loop));
}
