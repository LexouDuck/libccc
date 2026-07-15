
#ifndef __NOSTD__
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L	// needed to expose `pthread_rwlock_t` and friends, when compiling with a strict `-std=c**` option
	#endif
#endif
#include "libccc.h"
#include "libccc/sys/thread.h"

#ifndef __NOSTD__
	#include <pthread.h>
	#include <time.h>
	#include <errno.h>
#else
	int	pthread_cond_init(pthread_cond_t* cond, void const* attr);
	int	pthread_cond_destroy(pthread_cond_t* cond);
	int	pthread_cond_signal(pthread_cond_t* cond);
	int	pthread_cond_broadcast(pthread_cond_t* cond);
	int	pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mutex);
	int	pthread_cond_timedwait(pthread_cond_t* cond, pthread_mutex_t* mutex, struct timespec const* abstime);
	int	clock_gettime(int clockid, struct timespec* result);
	#define CLOCK_REALTIME	0 // TODO find platform-specific value
#endif

#include LIBCONFIG_ERROR_INCLUDE



e_cccerror	Cond_Init(t_cond* cond)
{
	int	error;

	if CCCERROR((cond == NULL), ERROR_NULLPOINTER, 
		"condition variable given is NULL")
		return (ERROR_NULLPOINTER);
	error = pthread_cond_init(cond, NULL);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not initialize condition variable")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



e_cccerror	Cond_Delete(t_cond* cond)
{
	int	error;

	if CCCERROR((cond == NULL), ERROR_NULLPOINTER, 
		"condition variable given is NULL")
		return (ERROR_NULLPOINTER);
	error = pthread_cond_destroy(cond);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not delete condition variable")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



e_cccerror	Cond_NotifyOne(t_cond* cond)
{
	int	error;

	if CCCERROR((cond == NULL), ERROR_NULLPOINTER, 
		"condition variable given is NULL")
		return (ERROR_NULLPOINTER);
	error = pthread_cond_signal(cond);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not signal condition variable")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



e_cccerror	Cond_NotifyAll(t_cond* cond)
{
	int	error;

	if CCCERROR((cond == NULL), ERROR_NULLPOINTER, 
		"condition variable given is NULL")
		return (ERROR_NULLPOINTER);
	error = pthread_cond_broadcast(cond);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not broadcast condition variable")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



e_cccerror	Cond_Wait(t_cond* cond, t_mutex* mutex)
{
	int	error;

	if CCCERROR((cond == NULL), ERROR_NULLPOINTER, 
		"condition variable given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((mutex == NULL), ERROR_NULLPOINTER, 
		"mutex given is NULL")
		return (ERROR_NULLPOINTER);
	error = pthread_cond_wait(cond, mutex);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not wait on condition variable")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



t_bool	Cond_WaitTime(t_cond* cond, t_mutex* mutex, s_nanotime duration)
{
	struct timespec	abstime;
	int	error;

	if CCCERROR((cond == NULL), ERROR_NULLPOINTER, 
		"condition variable given is NULL")
		return (FALSE);
	if CCCERROR((mutex == NULL), ERROR_NULLPOINTER, 
		"mutex given is NULL")
		return (FALSE);
	if CCCERROR((duration.sec < 0 || duration.nanosec < 0 || duration.nanosec > 999999999),
		ERROR_INVALIDARGS, "invalid wait duration given: {.sec=%li, .nanosec=%li}",
		(long)duration.sec, (long)duration.nanosec)
		return (FALSE);
	// pthread_cond_timedwait() expects an absolute timestamp,
	// so convert the given relative `duration` to an absolute deadline
	error = clock_gettime(CLOCK_REALTIME, &abstime);
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not get the current time")
		return (FALSE);
	abstime.tv_sec  += (time_t)duration.sec;
	abstime.tv_nsec += (long)duration.nanosec;
	if (abstime.tv_nsec >= 1000000000L)
	{
		abstime.tv_sec  += 1;
		abstime.tv_nsec -= 1000000000L;
	}
	error = pthread_cond_timedwait(cond, mutex, &abstime);
	if (error == ETIMEDOUT)
		return (FALSE); // the timeout duration elapsed: this is not an error
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not timed-wait on condition variable")
		return (FALSE);
	return (TRUE);
}
