
#include <stdio.h>
#include <assert.h>
#include "libccc.h"
#include "libccc/sys/thread.h"

#define N_THREADS	8
#define N_LOOPS		10000

static t_mutex	g_mutex = MUTEX_INITIALIZER;
static int		g_counter = 0;

static void*	worker_count(void* arg)
{
	(void)arg;
	for (int i = 0; i < N_LOOPS; ++i)
	{
		Mutex_Lock(&g_mutex);
		g_counter += 1;
		Mutex_Unlock(&g_mutex);
	}
	return (NULL);
}

static void*	worker_return(void* arg)
{
	if (arg && *(int*)arg == 42)
		Thread_Exit((void*)0xCAFE);
	return ((void*)0xBEEF);
}

// condition variable test: simple producer/consumer flag
static t_mutex	g_cv_mutex = MUTEX_INITIALIZER;
static t_cond	g_cv = COND_INITIALIZER;
static t_bool	g_ready = FALSE;

static void*	worker_producer(void* arg)
{
	(void)arg;
	Thread_Sleep((s_nanotime){ .sec=0, .nanosec=50 * 1000 * 1000 }); // 50ms
	Mutex_Lock(&g_cv_mutex);
	g_ready = TRUE;
	Cond_NotifyAll(&g_cv);
	Mutex_Unlock(&g_cv_mutex);
	return (NULL);
}

static t_rwlock	g_rwlock = RWLOCK_INITIALIZER;
static int		g_shared = 0;

static void*	worker_rw(void* arg)
{
	int	writes = *(int*)arg;
	for (int i = 0; i < writes; ++i)
	{
		RWLock_LockWrite(&g_rwlock);
		g_shared += 1;
		RWLock_Unlock(&g_rwlock);
		RWLock_LockRead(&g_rwlock);
		volatile int read = g_shared; (void)read;
		RWLock_Unlock(&g_rwlock);
	}
	return (NULL);
}

int	main(void)
{
	t_thread	threads[N_THREADS];

	// 1) mutex + many threads incrementing a counter
	for (int i = 0; i < N_THREADS; ++i)
		assert(Thread_New(&threads[i], worker_count, NULL) == ERROR_NONE);
	for (int i = 0; i < N_THREADS; ++i)
		assert(Thread_Join(threads[i], NULL) == ERROR_NONE);
	printf("counter = %d (expected %d)\n", g_counter, N_THREADS * N_LOOPS);
	assert(g_counter == N_THREADS * N_LOOPS);

	// 2) thread return value, via `return` and via Thread_Exit()
	t_thread	t;
	void*		result = NULL;
	int			magic = 42;
	assert(Thread_New(&t, worker_return, NULL) == ERROR_NONE);
	assert(Thread_Join(t, &result) == ERROR_NONE);
	assert(result == (void*)0xBEEF);
	assert(Thread_New(&t, worker_return, &magic) == ERROR_NONE);
	assert(Thread_Join(t, &result) == ERROR_NONE);
	assert(result == (void*)0xCAFE);
	printf("thread return values: OK\n");

	// 3) detach
	assert(Thread_New(&t, worker_return, NULL) == ERROR_NONE);
	assert(Thread_Detach(t) == ERROR_NONE);
	printf("thread detach: OK\n");

	// 4) self/equals
	assert(Thread_Equals(Thread_Self(), Thread_Self()) == TRUE);
	printf("thread self/equals: OK\n");

	// 5) mutex trylock
	t_mutex	m;
	assert(Mutex_Init(&m) == ERROR_NONE);
	assert(Mutex_TryLock(&m) == TRUE);
	// NOTE: recursive trylock on the same thread is UB with default mutexes on some
	// platforms, so we only test the "acquired" path here; contention is tested above
	assert(Mutex_Unlock(&m) == ERROR_NONE);
	assert(Mutex_Delete(&m) == ERROR_NONE);
	printf("mutex init/trylock/delete: OK\n");

	// 6) condition variable: wait for producer
	assert(Thread_New(&t, worker_producer, NULL) == ERROR_NONE);
	Mutex_Lock(&g_cv_mutex);
	while (!g_ready)
		assert(Cond_Wait(&g_cv, &g_cv_mutex) == ERROR_NONE);
	Mutex_Unlock(&g_cv_mutex);
	assert(Thread_Join(t, NULL) == ERROR_NONE);
	printf("condition variable wait/notify: OK\n");

	// 7) condition variable timed wait: expect timeout (nobody signals)
	t_cond	cv;
	t_mutex	cvm;
	assert(Cond_Init(&cv) == ERROR_NONE);
	assert(Mutex_Init(&cvm) == ERROR_NONE);
	Mutex_Lock(&cvm);
	t_bool woken = Cond_WaitTime(&cv, &cvm, (s_nanotime){ .sec=0, .nanosec=20 * 1000 * 1000 }); // 20ms
	Mutex_Unlock(&cvm);
	assert(woken == FALSE);
	assert(Cond_Delete(&cv) == ERROR_NONE);
	assert(Mutex_Delete(&cvm) == ERROR_NONE);
	printf("condition variable timed wait (timeout): OK\n");

	// 8) rwlock, multithreaded
	int	writes = 1000;
	for (int i = 0; i < N_THREADS; ++i)
		assert(Thread_New(&threads[i], worker_rw, &writes) == ERROR_NONE);
	for (int i = 0; i < N_THREADS; ++i)
		assert(Thread_Join(threads[i], NULL) == ERROR_NONE);
	assert(g_shared == N_THREADS * writes);
	// trylock paths
	t_rwlock	rw;
	assert(RWLock_Init(&rw) == ERROR_NONE);
	assert(RWLock_TryLockRead(&rw) == TRUE);
	assert(RWLock_TryLockWrite(&rw) == FALSE); // already read-locked -> write trylock fails
	assert(RWLock_Unlock(&rw) == ERROR_NONE);
	assert(RWLock_TryLockWrite(&rw) == TRUE);
	assert(RWLock_Unlock(&rw) == ERROR_NONE);
	assert(RWLock_Delete(&rw) == ERROR_NONE);
	printf("rwlock: OK\n");

	// 9) sleep & yield
	assert(Thread_Yield() == ERROR_NONE);
	assert(Thread_Sleep((s_nanotime){ .sec=0, .nanosec=1000000 }) == ERROR_NONE);
	printf("sleep/yield: OK\n");

	printf("\nAll libccc/sys/thread tests passed!\n");
	return (0);
}
