
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
	int	pthread_rwlock_init(pthread_rwlock_t* rwlock, void const* attr);
	int	pthread_rwlock_destroy(pthread_rwlock_t* rwlock);
	int	pthread_rwlock_rdlock(pthread_rwlock_t* rwlock);
	int	pthread_rwlock_wrlock(pthread_rwlock_t* rwlock);
	int	pthread_rwlock_tryrdlock(pthread_rwlock_t* rwlock);
	int	pthread_rwlock_trywrlock(pthread_rwlock_t* rwlock);
	int	pthread_rwlock_unlock(pthread_rwlock_t* rwlock);
#endif

#include LIBCONFIG_ERROR_INCLUDE



e_cccerror	RWLock_Init(t_rwlock* rwlock)
{
	int	error;

	if CCCERROR((rwlock == NULL), ERROR_NULLPOINTER, 
		"read/write lock given is NULL")
		return (ERROR_NULLPOINTER);
	error = pthread_rwlock_init(rwlock, NULL);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not initialize read/write lock")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



e_cccerror	RWLock_Delete(t_rwlock* rwlock)
{
	int	error;

	if CCCERROR((rwlock == NULL), ERROR_NULLPOINTER, 
		"read/write lock given is NULL")
		return (ERROR_NULLPOINTER);
	error = pthread_rwlock_destroy(rwlock);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not delete read/write lock")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



e_cccerror	RWLock_LockRead(t_rwlock* rwlock)
{
	int	error;

	if CCCERROR((rwlock == NULL), ERROR_NULLPOINTER, 
		"read/write lock given is NULL")
		return (ERROR_NULLPOINTER);
	error = pthread_rwlock_rdlock(rwlock);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not lock read/write lock for reading")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



e_cccerror	RWLock_LockWrite(t_rwlock* rwlock)
{
	int	error;

	if CCCERROR((rwlock == NULL), ERROR_NULLPOINTER, 
		"read/write lock given is NULL")
		return (ERROR_NULLPOINTER);
	error = pthread_rwlock_wrlock(rwlock);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not lock read/write lock for writing")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



t_bool	RWLock_TryLockRead(t_rwlock* rwlock)
{
	int	error;

	if CCCERROR((rwlock == NULL), ERROR_NULLPOINTER, 
		"read/write lock given is NULL")
		return (FALSE);
	error = pthread_rwlock_tryrdlock(rwlock);
	if (error == EBUSY)
		return (FALSE); // the lock is currently held for writing by another thread: this is not an error
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not try-lock read/write lock for reading")
		return (FALSE);
	return (TRUE);
}



t_bool	RWLock_TryLockWrite(t_rwlock* rwlock)
{
	int	error;

	if CCCERROR((rwlock == NULL), ERROR_NULLPOINTER, 
		"read/write lock given is NULL")
		return (FALSE);
	error = pthread_rwlock_trywrlock(rwlock);
	if (error == EBUSY)
		return (FALSE); // the lock is currently held by another thread: this is not an error
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not try-lock read/write lock for writing")
		return (FALSE);
	return (TRUE);
}



e_cccerror	RWLock_Unlock(t_rwlock* rwlock)
{
	int	error;

	if CCCERROR((rwlock == NULL), ERROR_NULLPOINTER, 
		"read/write lock given is NULL")
		return (ERROR_NULLPOINTER);
	error = pthread_rwlock_unlock(rwlock);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not unlock read/write lock")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}
