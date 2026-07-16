
#if defined(_WIN32)
	#if !defined(_WIN32_WINNT) || (_WIN32_WINNT < 0x0600)
	#undef  _WIN32_WINNT
	#define _WIN32_WINNT	0x0600	// require Windows Vista or later (for `SRWLOCK`)
	#endif
#elif !defined(__NOSTD__)
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L	// needed to expose `pthread_rwlock_t` and friends, when compiling with a strict `-std=c**` option
	#endif
#endif
#include "libccc.h"
#include "libccc/sys/thread.h"

#if defined(_WIN32)
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>	// TODO handle __NOSTD__ for the win32 backend ?
#elif !defined(__NOSTD__)
	#include <pthread.h>
	#include <errno.h>
#else
	int	pthread_rwlock_init(pthread_rwlock_t* rwlock, void const* attr);
	int	pthread_rwlock_destroy(pthread_rwlock_t* rwlock);
	int	pthread_rwlock_rdlock(pthread_rwlock_t* rwlock);
	int	pthread_rwlock_wrlock(pthread_rwlock_t* rwlock);
	int	pthread_rwlock_tryrdlock(pthread_rwlock_t* rwlock);
	int	pthread_rwlock_trywrlock(pthread_rwlock_t* rwlock);
	int	pthread_rwlock_unlock(pthread_rwlock_t* rwlock);
#endif

#include LIBCONFIG_ERROR_INCLUDE

#if defined(_WIN32)
/*
**	The win32 backend for `t_rwlock` uses a `SRWLOCK`, together with one extra
**	field: the id of the thread currently holding the lock in "write" mode
**	(if any). This is needed because the win32 API has two distinct unlock
**	functions (`ReleaseSRWLockShared()`/`ReleaseSRWLockExclusive()`), whereas
**	this API (like pthread) has a single RWLock_Unlock() function: the extra
**	field lets RWLock_Unlock() know which kind of lock the calling thread holds.
**	Note that reading the `writer` field without synchronization is safe here:
**	- if the calling thread holds the lock for writing, it wrote its own id
**	- if the calling thread holds the lock for reading, no thread can possibly
**	  hold it for writing at the same time, so the field is necessarily `0`
**	  (the field is always cleared by the writer *before* it releases the lock)
*/
// compile-time check: the `ptr` field of the public `t_rwlock` type must be binary-compatible with the win32 `SRWLOCK` type
typedef char __assert_rwlock_srwlock_size [(sizeof (((t_rwlock*)0)->ptr) == sizeof (SRWLOCK)) ? 1 : -1];
//! Accesses the given `t_rwlock*`'s lock field as the win32 `SRWLOCK*` which it is, layout-wise
#define RWLOCK_WIN32(RWLOCK)	((SRWLOCK*)(void*)&(RWLOCK)->ptr)
#endif



e_cccerror	RWLock_Init(t_rwlock* rwlock)
{
	if CCCERROR((rwlock == NULL), ERROR_NULLPOINTER, 
		"read/write lock given is NULL")
		return (ERROR_NULLPOINTER);
#if defined(_WIN32)
	InitializeSRWLock(RWLOCK_WIN32(rwlock));
	rwlock->writer = 0;
	return (ERROR_NONE);
#else
	{
		int	error;

		error = pthread_rwlock_init(rwlock, NULL);
		errno = error;
		if CCCERROR((error != 0), ERROR_SYSTEM, 
			"could not initialize read/write lock")
			return (ERROR_SYSTEM);
		return (ERROR_NONE);
	}
#endif
}



e_cccerror	RWLock_Delete(t_rwlock* rwlock)
{
	if CCCERROR((rwlock == NULL), ERROR_NULLPOINTER, 
		"read/write lock given is NULL")
		return (ERROR_NULLPOINTER);
#if defined(_WIN32)
	// win32 `SRWLOCK` objects do not need to be destroyed
	return (ERROR_NONE);
#else
	{
		int	error;

		error = pthread_rwlock_destroy(rwlock);
		errno = error;
		if CCCERROR((error != 0), ERROR_SYSTEM, 
			"could not delete read/write lock")
			return (ERROR_SYSTEM);
		return (ERROR_NONE);
	}
#endif
}



e_cccerror	RWLock_LockRead(t_rwlock* rwlock)
{
	if CCCERROR((rwlock == NULL), ERROR_NULLPOINTER, 
		"read/write lock given is NULL")
		return (ERROR_NULLPOINTER);
#if defined(_WIN32)
	AcquireSRWLockShared(RWLOCK_WIN32(rwlock)); // (cannot fail)
	return (ERROR_NONE);
#else
	{
		int	error;

		error = pthread_rwlock_rdlock(rwlock);
		errno = error;
		if CCCERROR((error != 0), ERROR_SYSTEM, 
			"could not lock read/write lock for reading")
			return (ERROR_SYSTEM);
		return (ERROR_NONE);
	}
#endif
}



e_cccerror	RWLock_LockWrite(t_rwlock* rwlock)
{
	if CCCERROR((rwlock == NULL), ERROR_NULLPOINTER, 
		"read/write lock given is NULL")
		return (ERROR_NULLPOINTER);
#if defined(_WIN32)
	AcquireSRWLockExclusive(RWLOCK_WIN32(rwlock)); // (cannot fail)
	rwlock->writer = (t_u32)GetCurrentThreadId();
	return (ERROR_NONE);
#else
	{
		int	error;

		error = pthread_rwlock_wrlock(rwlock);
		errno = error;
		if CCCERROR((error != 0), ERROR_SYSTEM, 
			"could not lock read/write lock for writing")
			return (ERROR_SYSTEM);
		return (ERROR_NONE);
	}
#endif
}



t_bool	RWLock_TryLockRead(t_rwlock* rwlock)
{
	if CCCERROR((rwlock == NULL), ERROR_NULLPOINTER, 
		"read/write lock given is NULL")
		return (FALSE);
#if defined(_WIN32)
	return (TryAcquireSRWLockShared(RWLOCK_WIN32(rwlock)) != 0);
#else
	{
		int	error;

		error = pthread_rwlock_tryrdlock(rwlock);
		if (error == EBUSY)
			return (FALSE); // the lock is currently held for writing by another thread: this is not an error
		errno = error;
		if CCCERROR((error != 0), ERROR_SYSTEM, 
			"could not try-lock read/write lock for reading")
			return (FALSE);
		return (TRUE);
	}
#endif
}



t_bool	RWLock_TryLockWrite(t_rwlock* rwlock)
{
	if CCCERROR((rwlock == NULL), ERROR_NULLPOINTER, 
		"read/write lock given is NULL")
		return (FALSE);
#if defined(_WIN32)
	if (TryAcquireSRWLockExclusive(RWLOCK_WIN32(rwlock)) == 0)
		return (FALSE); // the lock is currently held by another thread: this is not an error
	rwlock->writer = (t_u32)GetCurrentThreadId();
	return (TRUE);
#else
	{
		int	error;

		error = pthread_rwlock_trywrlock(rwlock);
		if (error == EBUSY)
			return (FALSE); // the lock is currently held by another thread: this is not an error
		errno = error;
		if CCCERROR((error != 0), ERROR_SYSTEM, 
			"could not try-lock read/write lock for writing")
			return (FALSE);
		return (TRUE);
	}
#endif
}



e_cccerror	RWLock_Unlock(t_rwlock* rwlock)
{
	if CCCERROR((rwlock == NULL), ERROR_NULLPOINTER, 
		"read/write lock given is NULL")
		return (ERROR_NULLPOINTER);
#if defined(_WIN32)
	if (rwlock->writer == (t_u32)GetCurrentThreadId())
	{	// the calling thread holds the lock for writing (see the `writer` field explanation above)
		rwlock->writer = 0; // (cleared *before* releasing: no reader can observe a stale value)
		ReleaseSRWLockExclusive(RWLOCK_WIN32(rwlock));
	}
	else
	{	// the calling thread holds the lock for reading
		ReleaseSRWLockShared(RWLOCK_WIN32(rwlock));
	}
	return (ERROR_NONE);
#else
	{
		int	error;

		error = pthread_rwlock_unlock(rwlock);
		errno = error;
		if CCCERROR((error != 0), ERROR_SYSTEM, 
			"could not unlock read/write lock")
			return (ERROR_SYSTEM);
		return (ERROR_NONE);
	}
#endif
}
