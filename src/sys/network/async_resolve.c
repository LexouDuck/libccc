
#ifndef __NOSTD__
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L	// needed to expose POSIX APIs (pthread_rwlock_t etc), when compiling with a strict `-std=c**` option
	#endif
#endif
#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/sys/socket.h"
#include "libccc/sys/network.h"
#include "libccc/sys/async.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	The DNS resolution itself (a potentially slow, blocking getaddrinfo() call)
**	is performed on one of the event loop's worker pool threads, and its result
**	is then delivered back on the event loop thread, via the `done` callback
**	(this is the exact same architecture as libuv's `uv_getaddrinfo()`).
*/



//! The thread pool work callback: performs the blocking DNS lookup (runs on a worker thread)
static
void	__Network_Resolve_Work(s_async_work* work)
{
	s_async_resolve*	resolve = (s_async_resolve*)work; // `work` is the first member

	resolve->addresses = Network_Resolve_All(&resolve->amount, resolve->host, resolve->port);
	resolve->error = (resolve->addresses == NULL ? ERROR_NOTFOUND : ERROR_NONE);
}

//! The completion callback: delivers the results to the user (runs on the event loop thread)
static
void	__Network_Resolve_Done(s_async_work* work)
{
	s_async_resolve*	resolve = (s_async_resolve*)work; // `work` is the first member

	resolve->callback(resolve, resolve->error, resolve->addresses, resolve->amount);
	// the results are owned by this request handle: free them now that the callback has run
	if (resolve->addresses != NULL)
		Memory_Delete((void**)&resolve->addresses);
	if (resolve->host != NULL)
		Memory_Delete((void**)&resolve->host);
}



e_cccerror	Network_Resolve_Async(s_asyncloop* loop, s_async_resolve* resolve, t_char const* host, t_port port, f_async_resolve callback)
{
	e_cccerror	error;

	if CCCERROR((resolve == NULL), ERROR_NULLPOINTER, "async resolve handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((host == NULL), ERROR_NULLPOINTER, "hostname given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((callback == NULL), ERROR_NULLPOINTER, "resolve callback function given is NULL")
		return (ERROR_NULLPOINTER);
	resolve->data = NULL;
	resolve->callback = callback;
	resolve->port = port;
	resolve->addresses = NULL;
	resolve->amount = 0;
	resolve->error = ERROR_UNSPECIFIED;
	resolve->host = String_Duplicate(host); // duplicated: the worker thread may outlive the caller's string
	if CCCERROR((resolve->host == NULL), ERROR_ALLOCFAILURE, NULL)
		return (ERROR_ALLOCFAILURE);
	error = AsyncWork_Submit(loop, &resolve->work,
		__Network_Resolve_Work,
		__Network_Resolve_Done);
	if (error != ERROR_NONE)
	{
		Memory_Delete((void**)&resolve->host);
		return (error);
	}
	return (ERROR_NONE);
}
