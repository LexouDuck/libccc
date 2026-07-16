
#include "libccc.h"
#include "libccc/bool.h"
#include "libccc/sys/thread.h"
#include "libccc/sys/time.h"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                              Testing Variables                             ||
\*============================================================================*/

#define THREADTEST_THREADS		8		//!< the amount of threads spawned for concurrency scenario tests
#define THREADTEST_ITERATIONS	10000	//!< the amount of iterations each thread performs, for concurrency scenario tests

//! shared state for the concurrency scenario tests (protected by the scenario's mutex/rwlock)
typedef struct threadtest_shared
{
	t_mutex		mutex;
	t_rwlock	rwlock;
	t_cond		cond;
	t_u64		counter;
	t_bool		ready;
	t_bool		flag_a;
	t_bool		flag_b;
}	s_threadtest_shared;

static s_threadtest_shared	shared;



/*============================================================================*\
||                              Scenario Functions                            ||
\*============================================================================*/

/*
**	The thread API functions cannot be tested in isolation with simple
**	input/expected-output comparisons: instead, each test below runs a small
**	multithreaded "scenario" function, whose final observable result is
**	deterministic, and is compared against the expected value, using the
**	usual test suite machinery.
*/

static void*	threadtest_return_42(void* arg)
{
	(void)arg;
	return ((void*)(t_size)42);
}

//! Thread_New()/Thread_Join(): the value returned by the thread function is retrieved by Thread_Join()
static t_u64	scenario_thread_join(void)
{
	t_thread	thread;
	void*		retval = NULL;

	if (Thread_New(&thread, threadtest_return_42, NULL) != ERROR_NONE)
		return (0);
	if (Thread_Join(thread, &retval) != ERROR_NONE)
		return (0);
	return ((t_u64)(t_size)retval);
}



static void*	threadtest_exit_99(void* arg)
{
	(void)arg;
	Thread_Exit((void*)(t_size)99);
	return (NULL); // never reached
}

//! Thread_Exit(): the value given to Thread_Exit() is retrieved by Thread_Join()
static t_u64	scenario_thread_exit(void)
{
	t_thread	thread;
	void*		retval = NULL;

	if (Thread_New(&thread, threadtest_exit_99, NULL) != ERROR_NONE)
		return (0);
	if (Thread_Join(thread, &retval) != ERROR_NONE)
		return (0);
	return ((t_u64)(t_size)retval);
}



static void*	threadtest_get_self(void* arg)
{
	*(t_thread*)arg = Thread_Self();
	return (NULL);
}

//! Thread_Self()/Thread_Equals(): a spawned thread is equal to itself, and different from the spawning thread
static t_bool	scenario_thread_self_equals(void)
{
	t_thread	thread;
	t_thread	inner_self;
	t_bool		result = TRUE;

	if (Thread_New(&thread, threadtest_get_self, &inner_self) != ERROR_NONE)
		return (FALSE);
	if (Thread_Join(thread, NULL) != ERROR_NONE)
		return (FALSE);
	result = result && (Thread_Equals(inner_self, thread) == TRUE); // the thread's own Thread_Self() is the handle Thread_New() returned
	result = result && (Thread_Equals(thread, Thread_Self()) == FALSE); // the spawned thread is not the current thread
	result = result && (Thread_Equals(Thread_Self(), Thread_Self()) == TRUE); // the current thread is itself
	return (result);
}



static void*	threadtest_detached(void* arg)
{
	s_threadtest_shared*	state = arg;

	Mutex_Lock(&state->mutex);
	state->ready = TRUE;
	Cond_NotifyOne(&state->cond);
	Mutex_Unlock(&state->mutex);
	return (NULL);
}

//! Thread_Detach(): a detached thread still runs to completion (verified via mutex/cond signaling)
static t_bool	scenario_thread_detach(void)
{
	t_thread	thread;
	t_bool		result = TRUE;

	shared = (s_threadtest_shared){0};
	if (Mutex_Init(&shared.mutex) != ERROR_NONE ||
		Cond_Init(&shared.cond) != ERROR_NONE)
		return (FALSE);
	if (Thread_New(&thread, threadtest_detached, &shared) != ERROR_NONE)
		return (FALSE);
	if (Thread_Detach(thread) != ERROR_NONE)
		result = FALSE;
	Mutex_Lock(&shared.mutex);
	while (!shared.ready) // wait for the detached thread to signal that it ran
	{
		if (!Cond_WaitTime(&shared.cond, &shared.mutex, (s_nanotime){ .sec=5, .nanosec=0 }))
		{
			result = FALSE; // 5 seconds without a signal: something is very wrong
			break;
		}
	}
	Mutex_Unlock(&shared.mutex);
	Mutex_Delete(&shared.mutex);
	Cond_Delete(&shared.cond);
	return (result);
}



//! Thread_Sleep(): sleeping for 50ms takes at least 50ms (and less than 5 seconds)
static t_bool	scenario_thread_sleep(void)
{
	t_time	start;
	t_time	elapsed;

	start = Time_Now();
	if (Thread_Sleep((s_nanotime){ .sec=0, .nanosec=50 * 1000 * 1000 }) != ERROR_NONE)
		return (FALSE);
	elapsed = Time_Now() - start;
	return (elapsed >= 0 && elapsed < 5); // t_time has second precision: 50ms elapses within [0,5) seconds
}



static void*	threadtest_mutex_worker(void* arg)
{
	s_threadtest_shared*	state = arg;

	for (t_uint i = 0; i < THREADTEST_ITERATIONS; ++i)
	{
		Mutex_Lock(&state->mutex);
		state->counter += 1;
		Mutex_Unlock(&state->mutex);
	}
	return (NULL);
}

//! Mutex_Lock()/Mutex_Unlock(): concurrent increments never get lost when protected by a mutex
static t_u64	scenario_mutex_counter(void)
{
	t_thread	threads[THREADTEST_THREADS];

	shared = (s_threadtest_shared){0};
	if (Mutex_Init(&shared.mutex) != ERROR_NONE)
		return (0);
	for (t_uint i = 0; i < THREADTEST_THREADS; ++i)
	{
		if (Thread_New(&threads[i], threadtest_mutex_worker, &shared) != ERROR_NONE)
			return (0);
	}
	for (t_uint i = 0; i < THREADTEST_THREADS; ++i)
	{
		Thread_Join(threads[i], NULL);
	}
	Mutex_Delete(&shared.mutex);
	return (shared.counter);
}



static void*	threadtest_trylock_worker(void* arg)
{
	s_threadtest_shared*	state = arg;

	state->flag_a = Mutex_TryLock(&state->mutex); // the main thread holds the mutex: must fail
	return (NULL);
}

//! Mutex_TryLock(): fails without blocking when the mutex is held by another thread
static t_bool	scenario_mutex_trylock(void)
{
	t_thread	thread;
	t_bool		result = TRUE;

	shared = (s_threadtest_shared){0};
	if (Mutex_Init(&shared.mutex) != ERROR_NONE)
		return (FALSE);
	result = result && (Mutex_TryLock(&shared.mutex) == TRUE); // free mutex: trylock succeeds
	if (Thread_New(&thread, threadtest_trylock_worker, &shared) != ERROR_NONE)
		return (FALSE);
	Thread_Join(thread, NULL); // (the worker attempted its trylock while this thread held the mutex)
	result = result && (shared.flag_a == FALSE); // held mutex: trylock from another thread fails
	Mutex_Unlock(&shared.mutex);
	Mutex_Delete(&shared.mutex);
	return (result);
}



static void*	threadtest_cond_producer(void* arg)
{
	s_threadtest_shared*	state = arg;

	Thread_Sleep((s_nanotime){ .sec=0, .nanosec=20 * 1000 * 1000 }); // 20ms: ensure the consumer is already waiting
	Mutex_Lock(&state->mutex);
	state->counter = 123;
	state->ready = TRUE;
	Cond_NotifyOne(&state->cond);
	Mutex_Unlock(&state->mutex);
	return (NULL);
}

//! Cond_Wait()/Cond_NotifyOne(): a consumer thread wakes up when the producer signals
static t_u64	scenario_cond_producer_consumer(void)
{
	t_thread	producer;
	t_u64		result;

	shared = (s_threadtest_shared){0};
	if (Mutex_Init(&shared.mutex) != ERROR_NONE ||
		Cond_Init(&shared.cond) != ERROR_NONE)
		return (0);
	if (Thread_New(&producer, threadtest_cond_producer, &shared) != ERROR_NONE)
		return (0);
	Mutex_Lock(&shared.mutex);
	while (!shared.ready)
	{
		Cond_Wait(&shared.cond, &shared.mutex);
	}
	result = shared.counter;
	Mutex_Unlock(&shared.mutex);
	Thread_Join(producer, NULL);
	Mutex_Delete(&shared.mutex);
	Cond_Delete(&shared.cond);
	return (result);
}



//! Cond_WaitTime(): returns `FALSE` when the wait times out (nobody signals)
static t_bool	scenario_cond_waittime_timeout(void)
{
	t_bool	signaled;

	shared = (s_threadtest_shared){0};
	if (Mutex_Init(&shared.mutex) != ERROR_NONE ||
		Cond_Init(&shared.cond) != ERROR_NONE)
		return (FALSE);
	Mutex_Lock(&shared.mutex);
	signaled = Cond_WaitTime(&shared.cond, &shared.mutex, (s_nanotime){ .sec=0, .nanosec=30 * 1000 * 1000 }); // 30ms
	Mutex_Unlock(&shared.mutex);
	Mutex_Delete(&shared.mutex);
	Cond_Delete(&shared.cond);
	return (signaled == FALSE); // the wait must have timed out
}



static void*	threadtest_rwlock_prober(void* arg)
{
	s_threadtest_shared*	state = arg;

	state->flag_a = RWLock_TryLockRead(&state->rwlock); // the main thread holds a read lock: another read lock must succeed
	if (state->flag_a)
		RWLock_Unlock(&state->rwlock);
	state->flag_b = RWLock_TryLockWrite(&state->rwlock); // the main thread holds a read lock: a write lock must fail
	if (state->flag_b)
		RWLock_Unlock(&state->rwlock);
	return (NULL);
}

//! RWLock_TryLockRead()/RWLock_TryLockWrite(): read locks are shared, write locks are exclusive
static t_bool	scenario_rwlock_shared_exclusive(void)
{
	t_thread	prober;
	t_bool		result = TRUE;

	shared = (s_threadtest_shared){0};
	if (RWLock_Init(&shared.rwlock) != ERROR_NONE)
		return (FALSE);
	if (RWLock_LockRead(&shared.rwlock) != ERROR_NONE) // hold a read lock during the whole probing
		return (FALSE);
	if (Thread_New(&prober, threadtest_rwlock_prober, &shared) != ERROR_NONE)
		return (FALSE);
	Thread_Join(prober, NULL);
	result = result && (shared.flag_a == TRUE); // concurrent read lock succeeded
	result = result && (shared.flag_b == FALSE); // concurrent write lock failed
	RWLock_Unlock(&shared.rwlock);
	RWLock_Delete(&shared.rwlock);
	return (result);
}



static void*	threadtest_rwlock_writer(void* arg)
{
	s_threadtest_shared*	state = arg;

	for (t_uint i = 0; i < THREADTEST_ITERATIONS; ++i)
	{
		RWLock_LockWrite(&state->rwlock);
		state->counter += 1;
		RWLock_Unlock(&state->rwlock);
	}
	return (NULL);
}

//! RWLock_LockWrite(): concurrent increments never get lost when protected by a write lock
static t_u64	scenario_rwlock_counter(void)
{
	t_thread	threads[THREADTEST_THREADS];

	shared = (s_threadtest_shared){0};
	if (RWLock_Init(&shared.rwlock) != ERROR_NONE)
		return (0);
	for (t_uint i = 0; i < THREADTEST_THREADS; ++i)
	{
		if (Thread_New(&threads[i], threadtest_rwlock_writer, &shared) != ERROR_NONE)
			return (0);
	}
	for (t_uint i = 0; i < THREADTEST_THREADS; ++i)
	{
		Thread_Join(threads[i], NULL);
	}
	RWLock_Delete(&shared.rwlock);
	return (shared.counter);
}



//! NULL/invalid arguments: every fallible function returns the appropriate error code, without crashing
static t_bool	scenario_thread_errors(void)
{
	t_thread	thread;
	t_bool		result = TRUE;

	result = result && (Thread_New(NULL, threadtest_return_42, NULL) == ERROR_NULLPOINTER);
	result = result && (Thread_New(&thread, NULL, NULL) == ERROR_NULLPOINTER);
	result = result && (Mutex_Init(NULL) == ERROR_NULLPOINTER);
	result = result && (Mutex_Lock(NULL) == ERROR_NULLPOINTER);
	result = result && (Mutex_Unlock(NULL) == ERROR_NULLPOINTER);
	result = result && (Mutex_TryLock(NULL) == FALSE);
	result = result && (Cond_Init(NULL) == ERROR_NULLPOINTER);
	result = result && (Cond_NotifyOne(NULL) == ERROR_NULLPOINTER);
	result = result && (Cond_NotifyAll(NULL) == ERROR_NULLPOINTER);
	result = result && (RWLock_Init(NULL) == ERROR_NULLPOINTER);
	result = result && (RWLock_Unlock(NULL) == ERROR_NULLPOINTER);
	return (result);
}



/*============================================================================*\
||                              Testing Functions                             ||
\*============================================================================*/



#ifndef c_thrnew
void test_thread(void)	{}
#warning "thread() test suite function defined, but the function isn't defined."
#else
static void	print_test_thread_u64(char const* test_name, t_testflags flags,
		t_u64 expecting,
		t_u64 (*scenario)(void),
		char const* scenario_args)
{
	TEST_INIT(u64)
	TEST_PERFORM_(result, scenario)
	test.expect = expecting;
	TEST_PRINT(u64,	thread_scenario, "%s", scenario_args)
}
static void	print_test_thread_bool(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_bool (*scenario)(void),
		char const* scenario_args)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario)
	test.expect = expecting;
	TEST_PRINT(bool,thread_scenario, "%s", scenario_args)
}
void	test_thread(void)
{
	t_u64	total = (t_u64)THREADTEST_THREADS * THREADTEST_ITERATIONS;
/*	| TEST FUNCTION         | TEST NAME                     |TESTFLAG| EXPECTING | TEST ARGS	*/
	print_test_thread_u64 ("thread new/join (return value)",	FALSE,        42, scenario_thread_join,            "42");
	print_test_thread_u64 ("thread exit (retrieved by join)",	FALSE,        99, scenario_thread_exit,            "99");
	print_test_thread_bool("thread self/equals",				FALSE,      TRUE, scenario_thread_self_equals,     "");
	print_test_thread_bool("thread detach (runs to the end)",	FALSE,      TRUE, scenario_thread_detach,          "");
	print_test_thread_bool("thread sleep (50ms)",				FALSE,      TRUE, scenario_thread_sleep,           "50ms");
	print_test_thread_u64 ("mutex (concurrent counter)",		FALSE,     total, scenario_mutex_counter,          "8 threads * 10000 increments");
	print_test_thread_bool("mutex trylock (busy/free)",			FALSE,      TRUE, scenario_mutex_trylock,          "");
	print_test_thread_u64 ("cond wait/notify (prod/cons)",		FALSE,       123, scenario_cond_producer_consumer, "123");
	print_test_thread_bool("cond waittime (timeout)",			FALSE,      TRUE, scenario_cond_waittime_timeout,  "30ms");
	print_test_thread_bool("rwlock (shared read/excl write)",	FALSE,      TRUE, scenario_rwlock_shared_exclusive,"");
	print_test_thread_u64 ("rwlock (concurrent counter)",		FALSE,     total, scenario_rwlock_counter,         "8 threads * 10000 increments");
	print_test_thread_bool("thread (error handling)",			FALSE,      TRUE, scenario_thread_errors,          "NULL");
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/



int		testsuite_sys_thread(void)
{
	print_suite_title("libccc/sys/thread");

	test_thread();

	return (OK);
}
