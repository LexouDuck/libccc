
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
	int	pthread_mutex_init(pthread_mutex_t* mutex, void const* attr);
	int	pthread_mutex_destroy(pthread_mutex_t* mutex);
	int	pthread_mutex_lock(pthread_mutex_t* mutex);
	int	pthread_mutex_trylock(pthread_mutex_t* mutex);
	int	pthread_mutex_unlock(pthread_mutex_t* mutex);
#endif

#include LIBCONFIG_ERROR_INCLUDE

#if defined(_WIN32)
// compile-time check: the public `t_mutex` type must be binary-compatible with the win32 `SRWLOCK` type
typedef char __assert_mutex_srwlock_size [(sizeof (t_mutex) == sizeof (SRWLOCK)) ? 1 : -1];
//! Accesses the given `t_mutex*` as the win32 `SRWLOCK*` which it is, layout-wise
#define MUTEX_WIN32(MUTEX)	((SRWLOCK*)(void*)(MUTEX))
#endif



e_cccerror	Mutex_Init(t_mutex* mutex)
{
	if CCCERROR((mutex == NULL), ERROR_NULLPOINTER, 
		"mutex given is NULL")
		return (ERROR_NULLPOINTER);
#if defined(_WIN32)
	InitializeSRWLock(MUTEX_WIN32(mutex));
	return (ERROR_NONE);
#else
	{
		int	error;

		error = pthread_mutex_init(mutex, NULL);
		errno = error;
		if CCCERROR((error != 0), ERROR_SYSTEM, 
			"could not initialize mutex")
			return (ERROR_SYSTEM);
		return (ERROR_NONE);
	}
#endif
}



e_cccerror	Mutex_Delete(t_mutex* mutex)
{
	if CCCERROR((mutex == NULL), ERROR_NULLPOINTER, 
		"mutex given is NULL")
		return (ERROR_NULLPOINTER);
#if defined(_WIN32)
	// win32 `SRWLOCK` objects do not need to be destroyed
	return (ERROR_NONE);
#else
	{
		int	error;

		error = pthread_mutex_destroy(mutex);
		errno = error;
		if CCCERROR((error != 0), ERROR_SYSTEM, 
			"could not delete mutex")
			return (ERROR_SYSTEM);
		return (ERROR_NONE);
	}
#endif
}



e_cccerror	Mutex_Lock(t_mutex* mutex)
{
	if CCCERROR((mutex == NULL), ERROR_NULLPOINTER, 
		"mutex given is NULL")
		return (ERROR_NULLPOINTER);
#if defined(_WIN32)
	AcquireSRWLockExclusive(MUTEX_WIN32(mutex)); // (cannot fail)
	return (ERROR_NONE);
#else
	{
		int	error;

		error = pthread_mutex_lock(mutex);
		errno = error;
		if CCCERROR((error != 0), ERROR_SYSTEM, 
			"could not lock mutex")
			return (ERROR_SYSTEM);
		return (ERROR_NONE);
	}
#endif
}



t_bool	Mutex_TryLock(t_mutex* mutex)
{
	if CCCERROR((mutex == NULL), ERROR_NULLPOINTER, 
		"mutex given is NULL")
		return (FALSE);
#if defined(_WIN32)
	return (TryAcquireSRWLockExclusive(MUTEX_WIN32(mutex)) != 0);
#else
	{
		int	error;

		error = pthread_mutex_trylock(mutex);
		if (error == EBUSY)
			return (FALSE); // the mutex is currently locked by another thread: this is not an error
		errno = error;
		if CCCERROR((error != 0), ERROR_SYSTEM, 
			"could not try-lock mutex")
			return (FALSE);
		return (TRUE);
	}
#endif
}



e_cccerror	Mutex_Unlock(t_mutex* mutex)
{
	if CCCERROR((mutex == NULL), ERROR_NULLPOINTER, 
		"mutex given is NULL")
		return (ERROR_NULLPOINTER);
#if defined(_WIN32)
	ReleaseSRWLockExclusive(MUTEX_WIN32(mutex));
	return (ERROR_NONE);
#else
	{
		int	error;

		error = pthread_mutex_unlock(mutex);
		errno = error;
		if CCCERROR((error != 0), ERROR_SYSTEM, 
			"could not unlock mutex")
			return (ERROR_SYSTEM);
		return (ERROR_NONE);
	}
#endif
}
