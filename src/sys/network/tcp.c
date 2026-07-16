
#ifndef __NOSTD__
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L	// needed to expose pthread/socket POSIX APIs, when compiling with a strict `-std=c**` option
	#endif
#endif

#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/sys/socket.h"
#include "libccc/sys/network.h"
#include "libccc/sys/thread.h"

#include "../socket/socket_private.h"

#include LIBCONFIG_ERROR_INCLUDE



t_socket	TCP_Connect_Addr(s_sockaddr const* addr)
{
	t_socket	sock;

	if CCCERROR((addr == NULL), ERROR_NULLPOINTER, "socket address given is NULL")
		return (SOCKET_INVALID);
	sock = Socket_New(addr->family, SOCKTYPE_STREAM, SOCKPROTO_TCP);
	if (sock == SOCKET_INVALID)
		return (SOCKET_INVALID);
	if (Socket_Connect(sock, addr) != ERROR_NONE)
	{
		Socket_Close(sock);
		return (SOCKET_INVALID);
	}
	return (sock);
}



t_socket	TCP_Connect(t_char const* host, t_port port)
{
	s_sockaddr*	addresses;
	t_uint	amount = 0;
	t_socket	sock = SOCKET_INVALID;

	if CCCERROR((host == NULL), ERROR_NULLPOINTER, "hostname given is NULL")
		return (SOCKET_INVALID);
	addresses = Network_Resolve_All(&amount, host, port);
	if (addresses == NULL)
		return (SOCKET_INVALID);
	for (t_uint i = 0; i < amount; ++i)
	{
		sock = TCP_Connect_Addr(&addresses[i]);
		if (sock != SOCKET_INVALID)
			break;
	}
	Memory_Free(addresses);
	if CCCERROR((sock == SOCKET_INVALID), ERROR_SYSTEM,
		"could not connect to host \"%s\" on port %u (%u address(es) tried)",
		host, (unsigned)port, amount)
		return (SOCKET_INVALID);
	return (sock);
}



t_socket	TCP_Listen(s_sockaddr const* addr, t_uint backlog)
{
	t_socket	sock;

	if CCCERROR((addr == NULL), ERROR_NULLPOINTER, "socket address given is NULL")
		return (SOCKET_INVALID);
	sock = Socket_New(addr->family, SOCKTYPE_STREAM, SOCKPROTO_TCP);
	if (sock == SOCKET_INVALID)
		return (SOCKET_INVALID);
	if (Socket_SetOption_Bool(sock, SOCKOPT_REUSEADDR, TRUE) != ERROR_NONE ||
		Socket_Bind(sock, addr) != ERROR_NONE ||
		Socket_Listen(sock, backlog) != ERROR_NONE)
	{
		Socket_Close(sock);
		return (SOCKET_INVALID);
	}
	return (sock);
}



e_cccerror	TCP_Serve(t_socket sock, f_tcp_handler handle, void* context)
{
	t_socket	client;
	s_sockaddr	client_addr;
	t_bool		keep_running = TRUE;

	if CCCERROR((handle == NULL), ERROR_NULLPOINTER, "connection handler function given is NULL")
		return (ERROR_NULLPOINTER);
	while (keep_running)
	{
		client = Socket_Accept(sock, &client_addr);
		if CCCERROR((client == SOCKET_INVALID), ERROR_SYSTEM,
			"server accept loop stopped: could not accept connection")
			return (ERROR_SYSTEM);
		keep_running = handle(client, &client_addr, context);
		Socket_Close(client);
	}
	return (ERROR_NONE);
}



/*
**	Shared state for one TCP_Serve_Concurrent() accept loop:
**	it lives on the accept loop's stack, and is shared (via pointer)
**	with every spawned connection handler thread.
*/
struct tcp_serve_state
{
	t_socket		listener;	//!< the listening socket (shut down to interrupt the accept loop, upon stopping)
	f_tcp_handler	handle;		//!< the user's connection handler function
	void*			context;	//!< the user's custom context pointer
	t_mutex			mutex;		//!< protects the fields below
	t_cond			cond;		//!< signaled whenever `threads` reaches zero
	t_bool			running;	//!< whether the server should keep accepting connections
	t_uint			threads;	//!< the amount of currently running connection handler threads
};

/*
**	The per-connection argument struct for each spawned handler thread
**	(allocated by the accept loop, freed by the handler thread).
*/
struct tcp_serve_conn
{
	struct tcp_serve_state*	state;	//!< the shared server state
	t_socket				client;	//!< the accepted client socket
	s_sockaddr				addr;	//!< the address of the connecting client
};

//! The thread entry point for each connection accepted by TCP_Serve_Concurrent()
static
void*	__TCP_Serve_Thread(void* arg)
{
	struct tcp_serve_conn*	conn = (struct tcp_serve_conn*)arg;
	struct tcp_serve_state*	state = conn->state;
	t_bool	keep_running;

	keep_running = state->handle(conn->client, &conn->addr, state->context);
	Socket_Close(conn->client);
	Memory_Free(conn);
	Mutex_Lock(&state->mutex);
	if (!keep_running && state->running)
	{	// this handler requested a server shutdown:
		// shutting down the listener interrupts the blocked accept() in the main loop
		state->running = FALSE;
		Socket_Shutdown(state->listener, SOCKSHUTDOWN_BOTH);
	}
	state->threads -= 1;
	if (state->threads == 0)
		Cond_NotifyAll(&state->cond);
	Mutex_Unlock(&state->mutex);
	return (NULL);
}

e_cccerror	TCP_Serve_Concurrent(t_socket sock, f_tcp_handler handle, void* context)
{
	struct tcp_serve_state	state;
	struct tcp_serve_conn*	conn;
	struct sockaddr_storage	native;
	socklen_t	native_length;
	t_socket	client;
	t_thread	thread;
	t_bool		running;
	e_cccerror	error = ERROR_NONE;

	if CCCERROR((handle == NULL), ERROR_NULLPOINTER, "connection handler function given is NULL")
		return (ERROR_NULLPOINTER);
	state.listener = sock;
	state.handle = handle;
	state.context = context;
	state.running = TRUE;
	state.threads = 0;
	if (Mutex_Init(&state.mutex) != ERROR_NONE)
		return (ERROR_SYSTEM);
	if (Cond_Init(&state.cond) != ERROR_NONE)
	{
		Mutex_Delete(&state.mutex);
		return (ERROR_SYSTEM);
	}
	while (TRUE)
	{
		// accept with the native call: upon graceful shutdown, the listener is
		// shut down by a handler thread, and this accept() fails on purpose
		// (so we should not raise a libccc error for that expected case)
		native_length = sizeof(native);
		client = (t_socket)accept(sock, (struct sockaddr*)&native, &native_length);
		__Socket_UpdateErrno();
		Mutex_Lock(&state.mutex);
		running = state.running;
		Mutex_Unlock(&state.mutex);
		if (!running)
		{	// graceful shutdown was requested by a handler
			if (!SOCKET_NATIVE_FAILED(client))
				Socket_Close(client); // a connection raced with the shutdown: close it
			break;
		}
		if CCCERROR(SOCKET_NATIVE_FAILED(client), ERROR_SYSTEM,
			"server accept loop stopped: could not accept connection")
		{
			error = ERROR_SYSTEM;
			break;
		}
		conn = (struct tcp_serve_conn*)Memory_New(sizeof(struct tcp_serve_conn));
		if CCCERROR((conn == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			Socket_Close(client);
			error = ERROR_ALLOCFAILURE;
			break;
		}
		conn->state = &state;
		conn->client = client;
		__SockAddr_FromNative(&conn->addr, &native);
		Mutex_Lock(&state.mutex);
		state.threads += 1;
		Mutex_Unlock(&state.mutex);
		if (Thread_New(&thread, __TCP_Serve_Thread, conn) != ERROR_NONE)
		{	// could not spawn a thread: gracefully degrade to handling this connection synchronously
			Mutex_Lock(&state.mutex);
			state.threads -= 1;
			Mutex_Unlock(&state.mutex);
			running = handle(client, &conn->addr, context);
			Socket_Close(client);
			Memory_Free(conn);
			if (!running)
				break;
			continue;
		}
		Thread_Detach(thread); // completion is tracked via `state.threads`, not via joining
	}
	// wait for every currently running connection handler thread to finish
	Mutex_Lock(&state.mutex);
	state.running = FALSE;
	while (state.threads > 0)
		Cond_Wait(&state.cond, &state.mutex);
	Mutex_Unlock(&state.mutex);
	Cond_Delete(&state.cond);
	Mutex_Delete(&state.mutex);
	return (error);
}
