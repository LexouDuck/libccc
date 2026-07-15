
#ifndef __NOSTD__
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L	// needed to expose `pthread_rwlock_t` and friends, when compiling with a strict `-std=c**` option
	#endif
#endif
#include "libccc.h"
#include "libccc/sys/thread.h"

#ifndef __NOSTD__
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



e_cccerror	Thread_New(t_thread* dest, f_thread function, void* arg)
{
	int	error;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, 
		"destination thread handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((function == NULL), ERROR_NULLPOINTER, 
		"thread entry point function given is NULL")
		return (ERROR_NULLPOINTER);
	error = pthread_create(dest, NULL, function, arg);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not create new thread")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



e_cccerror	Thread_Join(t_thread thread, void* *dest_result)
{
	int	error;

	error = pthread_join(thread, dest_result);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not join thread")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



e_cccerror	Thread_Detach(t_thread thread)
{
	int	error;

	error = pthread_detach(thread);
	errno = error;
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not detach thread")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



_NORETURN()
void	Thread_Exit(void* result)
{
	pthread_exit(result);
}



_INLINE()
t_thread	Thread_Self(void)
{
	return (pthread_self());
}



_INLINE()
t_bool	Thread_Equals(t_thread thread1, t_thread thread2)
{
	return (pthread_equal(thread1, thread2) != 0);
}



e_cccerror	Thread_Sleep(s_nanotime duration)
{
	struct timespec	remaining;
	struct timespec	t;
	int	error;

	if CCCERROR((duration.sec < 0 || duration.nanosec < 0 || duration.nanosec > 999999999),
		ERROR_INVALIDARGS, "invalid sleep duration given: {.sec=%li, .nanosec=%li}",
		(long)duration.sec, (long)duration.nanosec)
		return (ERROR_INVALIDARGS);
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



e_cccerror	Thread_Yield(void)
{
	int	error;

	error = sched_yield();
	if CCCERROR((error != 0), ERROR_SYSTEM, 
		"could not make thread yield")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}
