
#ifndef __NOSTD__
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L	// needed to expose `pthread_rwlock_t` and friends, when compiling with a strict `-std=c**` option
	#endif
#endif
#include "libccc.h"
#include "libccc/sys/thread.h"

#ifndef __NOSTD__
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



e_cccerror	Mutex_Init(t_mutex* mutex)
{
	int	error;

	if CCCERROR((mutex == NULL), ERROR_NULLPOINTER, 
		"mutex given is NULL")
		return (ERROR_NULLPOINTER);
	error = pthread_mutex_init(mutex, NULL);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not initialize mutex")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



e_cccerror	Mutex_Delete(t_mutex* mutex)
{
	int	error;

	if CCCERROR((mutex == NULL), ERROR_NULLPOINTER, 
		"mutex given is NULL")
		return (ERROR_NULLPOINTER);
	error = pthread_mutex_destroy(mutex);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not delete mutex")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



e_cccerror	Mutex_Lock(t_mutex* mutex)
{
	int	error;

	if CCCERROR((mutex == NULL), ERROR_NULLPOINTER, 
		"mutex given is NULL")
		return (ERROR_NULLPOINTER);
	error = pthread_mutex_lock(mutex);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not lock mutex")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



t_bool	Mutex_TryLock(t_mutex* mutex)
{
	int	error;

	if CCCERROR((mutex == NULL), ERROR_NULLPOINTER, 
		"mutex given is NULL")
		return (FALSE);
	error = pthread_mutex_trylock(mutex);
	if (error == EBUSY)
		return (FALSE); // the mutex is currently locked by another thread: this is not an error
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not try-lock mutex")
		return (FALSE);
	return (TRUE);
}



e_cccerror	Mutex_Unlock(t_mutex* mutex)
{
	int	error;

	if CCCERROR((mutex == NULL), ERROR_NULLPOINTER, 
		"mutex given is NULL")
		return (ERROR_NULLPOINTER);
	error = pthread_mutex_unlock(mutex);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not unlock mutex")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}
