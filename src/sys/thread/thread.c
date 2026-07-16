
#if defined(_WIN32)
	#if !defined(_WIN32_WINNT) || (_WIN32_WINNT < 0x0600)
	#undef  _WIN32_WINNT
	#define _WIN32_WINNT	0x0600	// require Windows Vista or later (for `INIT_ONCE`, `SRWLOCK`, `CONDITION_VARIABLE`)
	#endif
#elif !defined(__NOSTD__)
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L	// needed to expose `pthread_rwlock_t` and friends, when compiling with a strict `-std=c**` option
	#endif
#endif
#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/sys/thread.h"

#if defined(_WIN32)
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>	// TODO handle __NOSTD__ for the win32 backend ?
	#include <process.h>
#elif !defined(__NOSTD__)
	#include <pthread.h>
	#include <sched.h>
	#include <time.h>
	#include <errno.h>
#else
	int		pthread_create(pthread_t* thread, void const* attr, void* (*function)(void*), void* arg);
	int		pthread_join(pthread_t thread, void** retval);
	int		pthread_detach(pthread_t thread);
	void	pthread_exit(void* retval);
	pthread_t	pthread_self(void);
	int		pthread_equal(pthread_t t1, pthread_t t2);
	int		sched_yield(void);
	int		nanosleep(struct timespec const* duration, struct timespec* remaining);
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if defined(_WIN32)

/*
**	The win32 threading backend needs some per-thread bookkeeping, because the
**	win32 API has no notion of a `void*` thread return value (thread exit codes
**	are 32-bit integers, which cannot hold a pointer on 64-bit platforms).
**	So, each thread created by Thread_New() gets a small reference-counted
**	"thread data" block, which holds its entry point/argument/return value.
**	The block is shared between the thread itself and the joinable #t_thread
**	value: whichever of the two "finishes" last frees the block, which makes
**	both Thread_Join() and Thread_Detach() behave just like their POSIX
**	counterparts, with no memory leaks in either scenario.
*/
typedef struct thread_data
{
	f_thread		func;	//!< the thread's entry point function
	void*			arg;	//!< the argument to pass to `func`
	void*			retval;	//!< the thread's return value (retrieved by Thread_Join())
	volatile LONG	refs;	//!< reference count: the thread itself + the joinable handle
}	s_thread_data;

//! Decrements the given thread data block's reference count, freeing it if it reaches zero
static void	__Thread_DataDeref(s_thread_data* data)
{
	if (InterlockedDecrement(&data->refs) == 0)
		Memory_Delete((void**)&data);
}

/*
**	A TLS (thread-local storage) slot maps each running thread to its own
**	thread data block, so that Thread_Exit() can store the return value.
*/
static INIT_ONCE	thread_tls_once = INIT_ONCE_STATIC_INIT;
static DWORD		thread_tls_index = TLS_OUT_OF_INDEXES;

static BOOL CALLBACK	__Thread_TLSAlloc(PINIT_ONCE once, PVOID param, PVOID* context)
{
	(void)once;
	(void)param;
	(void)context;
	thread_tls_index = TlsAlloc();
	return (thread_tls_index != TLS_OUT_OF_INDEXES);
}

//! Ensures the TLS slot has been allocated (thread-safe, runs only once)
static t_bool	__Thread_TLSInit(void)
{
	return (InitOnceExecuteOnce(&thread_tls_once, __Thread_TLSAlloc, NULL, NULL) != 0);
}

//! The win32 entry point trampoline: calls the user's `void*(*)(void*)` function
static unsigned __stdcall	__Thread_Run(void* arg)
{
	s_thread_data*	data = (s_thread_data*)arg;

	TlsSetValue(thread_tls_index, data);
	data->retval = data->func(data->arg);
	__Thread_DataDeref(data);
	return (0);
}

#endif



e_cccerror	Thread_New(t_thread* dest, f_thread function, void* arg)
{
	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, 
		"destination thread handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((function == NULL), ERROR_NULLPOINTER, 
		"thread entry point function given is NULL")
		return (ERROR_NULLPOINTER);
#if defined(_WIN32)
	{
		s_thread_data*	data;
		t_uintmax		handle;
		unsigned		id = 0;

		if CCCERROR((!__Thread_TLSInit()), ERROR_SYSTEM, 
			"could not allocate thread-local storage slot (GetLastError: %lu)", GetLastError())
			return (ERROR_SYSTEM);
		data = (s_thread_data*)Memory_New(sizeof(s_thread_data));
		if CCCERROR((data == NULL), ERROR_ALLOCFAILURE, 
			"could not allocate thread bookkeeping data")
			return (ERROR_ALLOCFAILURE);
		data->func = function;
		data->arg = arg;
		data->refs = 2; // one reference for the thread itself, one for the joinable `t_thread` value
		handle = _beginthreadex(NULL, 0, __Thread_Run, data, 0, &id);
		if CCCERROR((handle == 0), ERROR_SYSTEM, 
			"could not create new thread")
		{
			Memory_Delete((void**)&data);
			return (ERROR_SYSTEM);
		}
		dest->handle = (void*)handle;
		dest->id = (t_u32)id;
		dest->data = data;
		return (ERROR_NONE);
	}
#else
	{
		int	error;

		error = pthread_create(dest, NULL, function, arg);
		errno = error;
		if CCCERROR((error != 0), ERROR_SYSTEM, 
			"could not create new thread")
			return (ERROR_SYSTEM);
		return (ERROR_NONE);
	}
#endif
}



e_cccerror	Thread_Join(t_thread thread, void* *dest_result)
{
#if defined(_WIN32)
	if CCCERROR((thread.handle == NULL), ERROR_INVALIDARGS, 
		"thread handle given is not joinable (on Windows, only threads created with Thread_New() can be joined)")
		return (ERROR_INVALIDARGS);
	if CCCERROR((WaitForSingleObject((HANDLE)thread.handle, INFINITE) != WAIT_OBJECT_0), ERROR_SYSTEM, 
		"could not join thread (GetLastError: %lu)", GetLastError())
		return (ERROR_SYSTEM);
	if (dest_result)
		*dest_result = (thread.data ? ((s_thread_data*)thread.data)->retval : NULL);
	CloseHandle((HANDLE)thread.handle);
	if (thread.data)
		__Thread_DataDeref((s_thread_data*)thread.data);
	return (ERROR_NONE);
#else
	int	error;

	error = pthread_join(thread, dest_result);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not join thread")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
#endif
}



e_cccerror	Thread_Detach(t_thread thread)
{
#if defined(_WIN32)
	if CCCERROR((thread.handle == NULL), ERROR_INVALIDARGS, 
		"thread handle given is not detachable (on Windows, only threads created with Thread_New() can be detached)")
		return (ERROR_INVALIDARGS);
	if CCCERROR((CloseHandle((HANDLE)thread.handle) == 0), ERROR_SYSTEM, 
		"could not detach thread (GetLastError: %lu)", GetLastError())
		return (ERROR_SYSTEM);
	if (thread.data)
		__Thread_DataDeref((s_thread_data*)thread.data);
	return (ERROR_NONE);
#else
	int	error;

	error = pthread_detach(thread);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not detach thread")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
#endif
}



_NORETURN()
void	Thread_Exit(void* result)
{
#if defined(_WIN32)
	s_thread_data*	data;

	if (thread_tls_index != TLS_OUT_OF_INDEXES)
	{
		data = (s_thread_data*)TlsGetValue(thread_tls_index);
		if (data) // this thread was created by Thread_New(): store its return value
		{
			data->retval = result;
			__Thread_DataDeref(data);
		}
	}
	_endthreadex(0);
	for (;;) {} // (never reached: `_endthreadex()` does not return)
#else
	pthread_exit(result);
#endif
}



_INLINE()
t_thread	Thread_Self(void)
{
#if defined(_WIN32)
	t_thread	result;

	result.handle = NULL; // (a `t_thread` from Thread_Self() is comparable, but not joinable)
	result.id = (t_u32)GetCurrentThreadId();
	result.data = (thread_tls_index != TLS_OUT_OF_INDEXES ? TlsGetValue(thread_tls_index) : NULL);
	return (result);
#else
	return (pthread_self());
#endif
}



_INLINE()
t_bool	Thread_Equals(t_thread thread1, t_thread thread2)
{
#if defined(_WIN32)
	return (thread1.id == thread2.id);
#else
	return (pthread_equal(thread1, thread2) != 0);
#endif
}



e_cccerror	Thread_Sleep(s_nanotime duration)
{
	if CCCERROR((duration.sec < 0 || duration.nanosec < 0 || duration.nanosec > 999999999),
		ERROR_INVALIDARGS, "invalid sleep duration given: {.sec=%li, .nanosec=%li}",
		(long)duration.sec, (long)duration.nanosec)
		return (ERROR_INVALIDARGS);
#if defined(_WIN32)
	{
		t_u64	ms;

		ms = ((t_u64)duration.sec * 1000) + (((t_u64)duration.nanosec + 999999) / 1000000); // round up to the next millisecond
		while (ms > 0xFFFFFFFE) // (`Sleep()` takes a 32-bit duration, and `0xFFFFFFFF` means "infinite")
		{
			Sleep(0xFFFFFFFE);
			ms -= 0xFFFFFFFE;
		}
		Sleep((DWORD)ms);
		return (ERROR_NONE);
	}
#else
	{
		struct timespec	remaining;
		struct timespec	t;
		int	error;

		t.tv_sec  = (time_t)duration.sec;
		t.tv_nsec = (long)duration.nanosec;
		while ((error = nanosleep(&t, &remaining)) != 0 && errno == EINTR)
		{
			t = remaining; // the sleep was interrupted by a signal: resume it
		}
		if CCCERROR((error != 0), ERROR_SYSTEM, 
			"could not make thread sleep")
			return (ERROR_SYSTEM);
		return (ERROR_NONE);
	}
#endif
}



e_cccerror	Thread_Yield(void)
{
#if defined(_WIN32)
	SwitchToThread(); // (a `FALSE` return simply means no other thread was ready to run: not an error)
	return (ERROR_NONE);
#else
	int	error;

	error = sched_yield();
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not make thread yield")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
#endif
}
