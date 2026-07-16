/*============================================================================*\
||                                            ______________________________  ||
||  libccc/sys/thread.h                      |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_SYS_THREAD_H
#define __LIBCCC_SYS_THREAD_H
/*!@group{libccc_sys_thread,25,libccc/sys/thread.h}
**
**	This header defines a cross-platform API for concurrency/multithreading:
**	threads, mutexes, condition variables, and read/write locks.
**
**	The libccc thread API is a set of easy-to-use wrappers above the native
**	threading facilities of the platform. The API is identical on every
**	platform, and there are currently two implementation backends:
**	- on POSIX platforms: the POSIX thread library (pthread)
**	- on Windows: the native win32 threading API (`_beginthreadex()`,
**	  `SRWLOCK`, `CONDITION_VARIABLE` - so there is no dependency on any
**	  pthread-compatibility library, even when building with MinGW)
**	The goal is to smooth over the various quirks of these interfaces:
**	- All functions perform the usual libccc `NULL` pointer argument checks
**	  (as configured by #LIBCONFIG_ERROR_HANDLING), rather than segfaulting.
**	- All fallible functions return a libccc #e_cccerror error code, and emit
**	  errors through the libccc error-handling mechanisms (see `libccc_errors.h`),
**	  rather than returning raw platform-specific `errno`-style int values.
**	- The "try" and "timed wait" style functions return a simple #t_bool,
**	  since their "failure" case is an expected, normal occurrence.
**	- Timeouts are expressed as relative durations (using #s_nanotime),
**	  rather than the rather clunky absolute-timestamp API of pthread.
**
**	NOTE: one minor platform difference: on Windows, a #t_thread obtained from
**	Thread_Self() can be compared with Thread_Equals(), but cannot be given to
**	Thread_Join()/Thread_Detach() (only #t_thread values obtained via
**	Thread_New() can be joined/detached on Windows).
**
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/pthread.h.html}
**	@isostd{C,https://en.cppreference.com/w/c/thread}
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#ifndef __NOSTD__
	#if defined(_WIN32)
		// native win32 threading backend: the types below are self-contained
		// (they are binary-compatible with the corresponding win32 types, so
		// this public header does not need to `#include <windows.h>` at all;
		// the implementation files verify this compatibility at compile time)
	#else
		#ifndef _POSIX_C_SOURCE
		#define _POSIX_C_SOURCE	200809L	// needed to expose `pthread_rwlock_t` and friends, when compiling with a strict `-std=c**` option
		#endif
		#include <pthread.h>
	#endif
#else
	#if defined(_WIN32)
		// native win32 threading backend: the types below are self-contained
	#else
		typedef unsigned long int	pthread_t; // TODO find platform-specific type
		typedef union pthread_mutex  { char _data[64]; long int _align; }	pthread_mutex_t; // TODO find platform-specific type
		typedef union pthread_cond   { char _data[64]; long int _align; }	pthread_cond_t; // TODO find platform-specific type
		typedef union pthread_rwlock { char _data[64]; long int _align; }	pthread_rwlock_t; // TODO find platform-specific type
	#endif
#endif

#include "libccc.h"

#ifndef __LIBCCC_SYS_TIME_H
#define	__LIBCCC_SYS_TIME_F
#include "libccc/sys/time.h"
#undef	__LIBCCC_SYS_TIME_H
#undef	__LIBCCC_SYS_TIME_F
#endif

HEADER_CPP

#ifndef __LIBCCC_SYS_THREAD_T
#define __LIBCCC_SYS_THREAD_T

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//!@doc The type used to represent a thread of execution (a thread identifier/handle)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_create.html}
**	@isostd{C,https://en.cppreference.com/w/c/thread/thrd_t}
**
**	This type is an opaque handle, referring to one thread of execution.
**	It is created by calling Thread_New(), and should always be "consumed"
**	by a matching call to either Thread_Join() or Thread_Detach().
**
**	NOTE: You should not assume anything about the underlying representation
**	of this type (it may be an integer, a pointer, or even a struct, depending
**	on the platform). In particular, do not compare two threads with the `==`
**	operator: use the Thread_Equals() function instead.
*/
//!@{
#if defined(_WIN32)
typedef struct thread
{
	void*	handle;	//!< [internal] the win32 `HANDLE` of this thread (is `NULL` for a #t_thread obtained via Thread_Self())
	t_u32	id;		//!< [internal] the win32 thread identifier (this is what Thread_Equals() compares)
	void*	data;	//!< [internal] per-thread bookkeeping block (only for threads created with Thread_New())
}					t_thread;
#else
typedef pthread_t	t_thread;
#endif
TYPEDEF_ALIAS(		t_thread, THREAD, PRIMITIVE)
//!@}

//!@doc The type of function which can be run by a thread (its "main" entry point function)
/*!
**	The function receives a single opaque pointer argument `arg`
**	(which is the `arg` pointer that was given to Thread_New()),
**	and its return value can be retrieved by a call to Thread_Join().
*/
//!@{
typedef void*	(*f_thread)(void* arg);
TYPEDEF_ALIAS(	f_thread, THREAD_FUNCTION, FUNCTION)
//!@}



//!@doc The type used to represent a mutex (MUTual EXclusion lock)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutex_init.html}
**	@isostd{C,https://en.cppreference.com/w/c/thread/mtx_t}
**
**	A mutex is the simplest form of lock: only one thread at a time may hold it.
**	It is used to protect a shared resource from concurrent access, by wrapping
**	each "critical section" of code with Mutex_Lock() and Mutex_Unlock() calls.
**
**	A #t_mutex variable must be initialized before use, either by calling
**	Mutex_Init(), or by assigning the #MUTEX_INITIALIZER static initializer.
*/
//!@{
#if defined(_WIN32)
typedef struct mutex
{
	void*	ptr;	//!< [internal] binary-compatible with the win32 `SRWLOCK` type (verified at compile time, in "src/sys/thread/mutex.c")
}						t_mutex;
#else
typedef pthread_mutex_t	t_mutex;
#endif
TYPEDEF_ALIAS(			t_mutex, MUTEX, PRIMITIVE)
//!@}
//! The static initializer value for a #t_mutex (alternative to calling Mutex_Init())
#if defined(_WIN32)
#define MUTEX_INITIALIZER	{ NULL } // matches the win32 `SRWLOCK_INIT` static initializer
#elif !defined(__NOSTD__)
#define MUTEX_INITIALIZER	PTHREAD_MUTEX_INITIALIZER
#else
#define MUTEX_INITIALIZER	{ 0 } // TODO find platform-specific value
#endif



//!@doc The type used to represent a condition variable
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_cond_init.html}
**	@isostd{C,https://en.cppreference.com/w/c/thread/cnd_t}
**
**	A condition variable allows one or more threads to sleep until they are
**	notified by another thread that some condition has (potentially) become true.
**	A condition variable is always used together with a #t_mutex, which must be
**	held when calling Cond_Wait(), and when changing the awaited-upon condition.
**
**	NOTE: "spurious wakeups" can occur with any condition variable API, so the
**	waiting thread should always re-check the condition when it wakes up
**	(in other words: always call Cond_Wait() within a loop which checks the condition).
**
**	A #t_cond variable must be initialized before use, either by calling
**	Cond_Init(), or by assigning the #COND_INITIALIZER static initializer.
*/
//!@{
#if defined(_WIN32)
typedef struct cond
{
	void*	ptr;	//!< [internal] binary-compatible with the win32 `CONDITION_VARIABLE` type (verified at compile time, in "src/sys/thread/cond.c")
}						t_cond;
#else
typedef pthread_cond_t	t_cond;
#endif
TYPEDEF_ALIAS(			t_cond, COND, PRIMITIVE)
//!@}
//! The static initializer value for a #t_cond (alternative to calling Cond_Init())
#if defined(_WIN32)
#define COND_INITIALIZER	{ NULL } // matches the win32 `CONDITION_VARIABLE_INIT` static initializer
#elif !defined(__NOSTD__)
#define COND_INITIALIZER	PTHREAD_COND_INITIALIZER
#else
#define COND_INITIALIZER	{ 0 } // TODO find platform-specific value
#endif



//!@doc The type used to represent a read/write lock
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_rwlock_init.html}
**
**	A read/write lock is a lock which distinguishes two kinds of accesses:
**	- "read" (shared) access: any number of threads may hold the lock for reading simultaneously
**	- "write" (exclusive) access: only one thread may hold the lock for writing, with no concurrent readers
**	This makes it more efficient than a #t_mutex for resources which are
**	read often, but written to rarely.
**
**	A #t_rwlock variable must be initialized before use, either by calling
**	RWLock_Init(), or by assigning the #RWLOCK_INITIALIZER static initializer.
*/
//!@{
#if defined(_WIN32)
typedef struct rwlock
{
	void*	ptr;	//!< [internal] binary-compatible with the win32 `SRWLOCK` type (verified at compile time, in "src/sys/thread/rwlock.c")
	t_u32	writer;	//!< [internal] the id of the thread currently holding write access, if any (needed by RWLock_Unlock())
}							t_rwlock;
#else
typedef pthread_rwlock_t	t_rwlock;
#endif
TYPEDEF_ALIAS(				t_rwlock, RWLOCK, PRIMITIVE)
//!@}
//! The static initializer value for a #t_rwlock (alternative to calling RWLock_Init())
#if defined(_WIN32)
#define RWLOCK_INITIALIZER	{ NULL, 0 } // matches the win32 `SRWLOCK_INIT` static initializer
#elif !defined(__NOSTD__)
#define RWLOCK_INITIALIZER	PTHREAD_RWLOCK_INITIALIZER
#else
#define RWLOCK_INITIALIZER	{ 0 } // TODO find platform-specific value
#endif



#endif
#ifndef __LIBCCC_SYS_THREAD_F
#define __LIBCCC_SYS_THREAD_F

/*============================================================================*\
||                               Thread Functions                             ||
\*============================================================================*/

//!@doc Creates a new thread, which begins executing the given `function`, with the given `arg`
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_create.html}
**
**	Every thread created with this function should eventually be "consumed" by
**	calling either Thread_Join() (to wait for it, and retrieve its result),
**	or Thread_Detach() (to let it run freely, releasing its resources upon completion).
**
**	@param	dest		The address in which to store the newly created thread handle (cannot be `NULL`)
**	@param	function	The entry point function which the new thread will execute (cannot be `NULL`)
**	@param	arg			An opaque pointer, passed as the one argument given to `function` (can be `NULL`)
**	@returns
**	`0`(#ERROR_NONE) if the thread was created successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror				Thread_New(t_thread* dest, f_thread function, void* arg);
#define c_thrnew		Thread_New
#define Thread_Create	Thread_New
//!@}

//!@doc Waits for the given `thread` to terminate, and retrieves its return value
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_join.html}
**
**	This function blocks the calling thread until the given `thread` terminates
**	(if the given `thread` has already terminated, this function returns immediately).
**	After a thread has been joined, its handle no longer refers to any thread.
**
**	@param	thread		The thread to wait for (must have been created by Thread_New(), and not yet joined/detached)
**	@param	dest_result	The address in which to store the `thread`'s return value (if `NULL`, the return value is discarded)
**	@returns
**	`0`(#ERROR_NONE) if the thread was joined successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror				Thread_Join(t_thread thread, void* *dest_result);
#define c_thrjoin		Thread_Join
#define Thread_Wait		Thread_Join
//!@}

//!@doc Detaches the given `thread`, letting it run freely (its resources are released when it terminates)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_detach.html}
**
**	After a thread has been detached, it can no longer be joined with Thread_Join():
**	its return value is discarded, and its resources are automatically
**	released by the system whenever it terminates.
**
**	@param	thread	The thread to detach (must have been created by Thread_New(), and not yet joined/detached)
**	@returns
**	`0`(#ERROR_NONE) if the thread was detached successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror				Thread_Detach(t_thread thread);
#define c_thrdetach		Thread_Detach
//!@}

//!@doc Terminates the calling thread, with the given `result` as its return value
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_exit.html}
**
**	This is equivalent to the thread's entry point function executing a
**	`return (result);` statement from its top-most stack frame.
**	NOTE: it is generally preferable to simply `return` from the thread's
**	entry point function, rather than calling this function.
**
**	@param	result	The return value for the calling thread (retrievable via Thread_Join())
*/
//!@{
_NORETURN()
void					Thread_Exit(void* result);
#define c_threxit		Thread_Exit
//!@}

//!@doc Returns the thread handle of the calling thread (ie: the current thread)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_self.html}
**
**	@returns
**	The thread handle which refers to the calling thread.
*/
//!@{
t_thread				Thread_Self(void);
#define c_thrself		Thread_Self
#define Thread_Current	Thread_Self
//!@}

//!@doc Checks whether the two given thread handles refer to the same thread
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_equal.html}
**
**	@param	thread1	The first thread to compare
**	@param	thread2	The second thread to compare
**	@returns
**	`TRUE` if the two given thread handles refer to the same thread,
**	otherwise `FALSE`.
*/
//!@{
t_bool					Thread_Equals(t_thread thread1, t_thread thread2);
#define c_threqu		Thread_Equals
//!@}

//!@doc Makes the calling thread sleep (do nothing) for the given `duration`
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/nanosleep.html}
**
**	This function suspends the execution of the calling thread for (at least)
**	the given `duration`. If the sleep is interrupted by a system signal,
**	it is automatically resumed, so as to always sleep the full `duration`.
**
**	@param	duration	The amount of time which the calling thread should spend sleeping
**	@returns
**	`0`(#ERROR_NONE) if the thread slept for the full duration successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror				Thread_Sleep(s_nanotime duration);
#define c_thrsleep		Thread_Sleep
//!@}

//!@doc Makes the calling thread yield its remaining execution time-slice to other threads
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/sched_yield.html}
**
**	This function offers a hint to the OS scheduler, telling it that the
**	calling thread is willing to relinquish the CPU to other threads.
**
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror				Thread_Yield(void);
#define c_thryield		Thread_Yield
//!@}



/*============================================================================*\
||                                Mutex Functions                             ||
\*============================================================================*/

//!@doc Initializes the given `mutex` (with default attributes)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutex_init.html}
**
**	Every mutex initialized with this function should eventually be
**	deleted with a matching call to Mutex_Delete().
**	NOTE: for `static`-storage mutexes, you can instead simply assign
**	the #MUTEX_INITIALIZER value, rather than calling this function.
**
**	@param	mutex	The mutex to initialize (cannot be `NULL`)
**	@returns
**	`0`(#ERROR_NONE) if the mutex was initialized successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror				Mutex_Init(t_mutex* mutex);
#define c_mutexinit		Mutex_Init
#define Mutex_New		Mutex_Init
//!@}

//!@doc Deletes the given `mutex` (which must be unlocked), releasing any resources associated with it
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutex_destroy.html}
**
**	@param	mutex	The mutex to delete (cannot be `NULL`, must be initialized and unlocked)
**	@returns
**	`0`(#ERROR_NONE) if the mutex was deleted successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror				Mutex_Delete(t_mutex* mutex);
#define c_mutexdel		Mutex_Delete
#define Mutex_Destroy	Mutex_Delete
//!@}

//!@doc Locks the given `mutex` (waiting for it to become available, if needed)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutex_lock.html}
**
**	If the given `mutex` is currently locked by another thread, then this
**	function blocks the calling thread until the mutex becomes available.
**
**	@param	mutex	The mutex to lock (cannot be `NULL`, must be initialized)
**	@returns
**	`0`(#ERROR_NONE) if the mutex was locked successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror				Mutex_Lock(t_mutex* mutex);
#define c_mutexlock		Mutex_Lock
//!@}

//!@doc Attempts to lock the given `mutex`, without ever blocking the calling thread
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutex_trylock.html}
**
**	This function is identical to Mutex_Lock(), except that it never blocks:
**	if the mutex is already locked by another thread, it immediately returns `FALSE`.
**
**	@param	mutex	The mutex to attempt to lock (cannot be `NULL`, must be initialized)
**	@returns
**	`TRUE` if the mutex was locked successfully by the calling thread,
**	otherwise `FALSE` (ie: the mutex is currently locked by another thread, or an error occurred).
*/
//!@{
t_bool					Mutex_TryLock(t_mutex* mutex);
#define c_mutextrylock	Mutex_TryLock
//!@}

//!@doc Unlocks the given `mutex` (which must be locked by the calling thread)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutex_unlock.html}
**
**	@param	mutex	The mutex to unlock (cannot be `NULL`, must be locked by the calling thread)
**	@returns
**	`0`(#ERROR_NONE) if the mutex was unlocked successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror				Mutex_Unlock(t_mutex* mutex);
#define c_mutexunlock	Mutex_Unlock
//!@}



/*============================================================================*\
||                        Condition Variable Functions                        ||
\*============================================================================*/

//!@doc Initializes the given condition variable `cond` (with default attributes)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_cond_init.html}
**
**	Every condition variable initialized with this function should eventually
**	be deleted with a matching call to Cond_Delete().
**	NOTE: for `static`-storage condition variables, you can instead simply
**	assign the #COND_INITIALIZER value, rather than calling this function.
**
**	@param	cond	The condition variable to initialize (cannot be `NULL`)
**	@returns
**	`0`(#ERROR_NONE) if the condition variable was initialized successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror				Cond_Init(t_cond* cond);
#define c_condinit		Cond_Init
#define Cond_New		Cond_Init
//!@}

//!@doc Deletes the given condition variable `cond` (which must have no waiting threads)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_cond_destroy.html}
**
**	@param	cond	The condition variable to delete (cannot be `NULL`, must be initialized, with no threads waiting on it)
**	@returns
**	`0`(#ERROR_NONE) if the condition variable was deleted successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror				Cond_Delete(t_cond* cond);
#define c_conddel		Cond_Delete
#define Cond_Destroy	Cond_Delete
//!@}

//!@doc Wakes up one of the threads which are waiting on the given condition variable `cond`
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_cond_signal.html}
**
**	If no threads are currently waiting on `cond`, this function does nothing.
**
**	@param	cond	The condition variable to signal (cannot be `NULL`, must be initialized)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror				Cond_NotifyOne(t_cond* cond);
#define c_condnotify1	Cond_NotifyOne
#define Cond_Signal		Cond_NotifyOne
//!@}

//!@doc Wakes up all of the threads which are waiting on the given condition variable `cond`
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_cond_broadcast.html}
**
**	If no threads are currently waiting on `cond`, this function does nothing.
**
**	@param	cond	The condition variable to broadcast to (cannot be `NULL`, must be initialized)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror				Cond_NotifyAll(t_cond* cond);
#define c_condnotify	Cond_NotifyAll
#define Cond_Broadcast	Cond_NotifyAll
//!@}

//!@doc Makes the calling thread wait on the given condition variable `cond`, releasing the given `mutex` while it waits
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_cond_wait.html}
**
**	This function atomically unlocks the given `mutex` (which must be locked
**	by the calling thread), and blocks the calling thread until the condition
**	variable `cond` is signaled by another thread (via Cond_NotifyOne() or
**	Cond_NotifyAll()). When the thread wakes up, the `mutex` is re-locked by
**	the calling thread, before this function returns.
**
**	NOTE: "spurious wakeups" can occur, so this function should always
**	be called within a loop which re-checks the awaited-upon condition.
**
**	@param	cond	The condition variable to wait upon (cannot be `NULL`, must be initialized)
**	@param	mutex	The mutex to release while waiting (cannot be `NULL`, must be locked by the calling thread)
**	@returns
**	`0`(#ERROR_NONE) if the function completed successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror				Cond_Wait(t_cond* cond, t_mutex* mutex);
#define c_condwait		Cond_Wait
//!@}

//!@doc Like Cond_Wait(), but stops waiting if the given `duration` of time elapses
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_cond_timedwait.html}
**
**	This function is identical to Cond_Wait(), except that the calling thread
**	will wake up (re-locking the `mutex` as usual) if the given (relative)
**	`duration` of time elapses without the condition variable being signaled.
**
**	NOTE: "spurious wakeups" can occur, so this function should always
**	be called within a loop which re-checks the awaited-upon condition.
**
**	@param	cond		The condition variable to wait upon (cannot be `NULL`, must be initialized)
**	@param	mutex		The mutex to release while waiting (cannot be `NULL`, must be locked by the calling thread)
**	@param	duration	The maximum amount of time to spend waiting, relative to the moment this function is called
**	@returns
**	`TRUE` if the thread was woken up by the condition variable being signaled,
**	otherwise `FALSE` (ie: the `duration` timeout elapsed, or an error occurred).
*/
//!@{
t_bool					Cond_WaitTime(t_cond* cond, t_mutex* mutex, s_nanotime duration);
#define c_condwaittime	Cond_WaitTime
#define Cond_TimedWait	Cond_WaitTime
//!@}



/*============================================================================*\
||                          Read/Write Lock Functions                         ||
\*============================================================================*/

//!@doc Initializes the given read/write lock `rwlock` (with default attributes)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_rwlock_init.html}
**
**	Every read/write lock initialized with this function should eventually
**	be deleted with a matching call to RWLock_Delete().
**	NOTE: for `static`-storage read/write locks, you can instead simply
**	assign the #RWLOCK_INITIALIZER value, rather than calling this function.
**
**	@param	rwlock	The read/write lock to initialize (cannot be `NULL`)
**	@returns
**	`0`(#ERROR_NONE) if the read/write lock was initialized successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					RWLock_Init(t_rwlock* rwlock);
#define c_rwlockinit		RWLock_Init
#define RWLock_New			RWLock_Init
//!@}

//!@doc Deletes the given read/write lock `rwlock` (which must be unlocked), releasing any resources associated with it
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_rwlock_destroy.html}
**
**	@param	rwlock	The read/write lock to delete (cannot be `NULL`, must be initialized and unlocked)
**	@returns
**	`0`(#ERROR_NONE) if the read/write lock was deleted successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					RWLock_Delete(t_rwlock* rwlock);
#define c_rwlockdel			RWLock_Delete
#define RWLock_Destroy		RWLock_Delete
//!@}

//!@doc Locks the given `rwlock` for reading (shared access)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_rwlock_rdlock.html}
**
**	Multiple threads may hold the same read/write lock for reading simultaneously.
**	If the given `rwlock` is currently locked for writing by another thread, then
**	this function blocks the calling thread until the lock becomes available.
**
**	@param	rwlock	The read/write lock to lock for reading (cannot be `NULL`, must be initialized)
**	@returns
**	`0`(#ERROR_NONE) if the lock was acquired successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					RWLock_LockRead(t_rwlock* rwlock);
#define c_rwlockread		RWLock_LockRead
//!@}

//!@doc Locks the given `rwlock` for writing (exclusive access)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_rwlock_wrlock.html}
**
**	Only one thread at a time may hold a read/write lock for writing (with no
**	concurrent readers). If the given `rwlock` is currently locked (for either
**	reading or writing) by any other thread, then this function blocks the
**	calling thread until the lock becomes available.
**
**	@param	rwlock	The read/write lock to lock for writing (cannot be `NULL`, must be initialized)
**	@returns
**	`0`(#ERROR_NONE) if the lock was acquired successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					RWLock_LockWrite(t_rwlock* rwlock);
#define c_rwlockwrite		RWLock_LockWrite
//!@}

//!@doc Attempts to lock the given `rwlock` for reading, without ever blocking the calling thread
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_rwlock_tryrdlock.html}
**
**	@param	rwlock	The read/write lock to attempt to lock for reading (cannot be `NULL`, must be initialized)
**	@returns
**	`TRUE` if the lock was acquired successfully by the calling thread,
**	otherwise `FALSE` (ie: the lock is currently held for writing by another thread, or an error occurred).
*/
//!@{
t_bool						RWLock_TryLockRead(t_rwlock* rwlock);
#define c_rwlocktryread		RWLock_TryLockRead
//!@}

//!@doc Attempts to lock the given `rwlock` for writing, without ever blocking the calling thread
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_rwlock_trywrlock.html}
**
**	@param	rwlock	The read/write lock to attempt to lock for writing (cannot be `NULL`, must be initialized)
**	@returns
**	`TRUE` if the lock was acquired successfully by the calling thread,
**	otherwise `FALSE` (ie: the lock is currently held by another thread, or an error occurred).
*/
//!@{
t_bool						RWLock_TryLockWrite(t_rwlock* rwlock);
#define c_rwlocktrywrite	RWLock_TryLockWrite
//!@}

//!@doc Unlocks the given `rwlock` (which must be locked by the calling thread)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_rwlock_unlock.html}
**
**	This function releases the given read/write lock, whether it was locked
**	for reading or for writing by the calling thread.
**
**	@param	rwlock	The read/write lock to unlock (cannot be `NULL`, must be locked by the calling thread)
**	@returns
**	`0`(#ERROR_NONE) if the lock was released successfully,
**	otherwise a non-zero error code (#e_cccerror)
*/
//!@{
e_cccerror					RWLock_Unlock(t_rwlock* rwlock);
#define c_rwlockunlock		RWLock_Unlock
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
