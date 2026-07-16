
#ifndef __NOSTD__
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L	// needed to expose POSIX socket APIs, when compiling with a strict `-std=c**` option
	#endif
#endif

#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/sys/socket.h"
#include "libccc/sys/network.h"
#include "libccc/sys/async.h"

#include "../socket/socket_private.h"

#include LIBCONFIG_ERROR_INCLUDE



/*============================================================================*\
||                          Asynchronous TCP: Server                          ||
\*============================================================================*/

//! The internal poll callback for a #s_async_tcp_server: accepts every pending connection
static
void	__AsyncTCP_Server_OnPoll(s_async_poll* poll, t_asyncpoll_events events)
{
	s_async_tcp_server*	server = (s_async_tcp_server*)poll; // `poll` is the first member
	struct sockaddr_storage	native;
	socklen_t	native_length;
	s_sockaddr	addr;
	t_socket	client;

	(void)events;
	// NB: the user's `on_accept` callback may call AsyncTCP_Server_Stop() on this
	// very handle: hence the `socket != SOCKET_INVALID` check on each iteration
	while (server->socket != SOCKET_INVALID)
	{	// accept every connection which is currently pending (the socket is non-blocking)
		native_length = sizeof(native);
		client = (t_socket)accept(server->socket, (struct sockaddr*)&native, &native_length);
		__Socket_UpdateErrno();
		if (SOCKET_NATIVE_FAILED(client))
		{
			if CCCERROR((!__Socket_IsErrorWouldBlock()), ERROR_SYSTEM,
				"could not accept connection on async TCP server")
				return;
			return;
		}
		__SockAddr_FromNative(&addr, &native);
		server->on_accept(server, client, &addr);
	}
}



e_cccerror	AsyncTCP_Listen(s_asyncloop* loop, s_async_tcp_server* server, s_sockaddr const* addr, t_uint backlog, f_async_tcp_accept on_accept)
{
	t_socket	sock;
	e_cccerror	error;

	if CCCERROR((server == NULL), ERROR_NULLPOINTER, "async TCP server handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((on_accept == NULL), ERROR_NULLPOINTER, "connection accept callback given is NULL")
		return (ERROR_NULLPOINTER);
	sock = TCP_Listen(addr, backlog);
	if (sock == SOCKET_INVALID)
		return (ERROR_SYSTEM);
	error = Socket_SetNonBlocking(sock, TRUE);
	if (error == ERROR_NONE)
		error = AsyncPoll_Init(loop, &server->poll, (t_fd)sock);
	if (error == ERROR_NONE)
		error = AsyncPoll_Start(&server->poll, ASYNCPOLL_READABLE, __AsyncTCP_Server_OnPoll);
	if (error != ERROR_NONE)
	{
		Socket_Close(sock);
		return (error);
	}
	server->data = NULL;
	server->socket = sock;
	server->on_accept = on_accept;
	return (ERROR_NONE);
}



e_cccerror	AsyncTCP_Server_Stop(s_async_tcp_server* server)
{
	if CCCERROR((server == NULL), ERROR_NULLPOINTER, "async TCP server handle given is NULL")
		return (ERROR_NULLPOINTER);
	AsyncPoll_Stop(&server->poll);
	AsyncHandle_Detach(&server->poll.base);
	if (server->socket != SOCKET_INVALID)
	{
		Socket_Close(server->socket);
		server->socket = SOCKET_INVALID;
	}
	return (ERROR_NONE);
}



/*============================================================================*\
||                        Asynchronous TCP: Connections                       ||
\*============================================================================*/

//! (forward declaration) The internal poll callback for a #s_async_tcp handle
static
void	__AsyncTCP_OnPoll(s_async_poll* poll, t_asyncpoll_events events);

//! Updates the set of I/O events being watched for the given connection, from its current state
static
void	__AsyncTCP_UpdateEvents(s_async_tcp* conn)
{
	t_asyncpoll_events	events = 0;

	if (conn->reading)
		events |= ASYNCPOLL_READABLE;
	if (conn->connecting || conn->queue_head != NULL)
		events |= ASYNCPOLL_WRITABLE;
	if (events == 0)
		AsyncPoll_Stop(&conn->poll);
	else
		AsyncPoll_Start(&conn->poll, events, __AsyncTCP_OnPoll);
}

//! Frees every pending write buffer of the given connection
static
void	__AsyncTCP_ClearQueue(s_async_tcp* conn)
{
	struct async_tcp_writebuf*	buf;
	struct async_tcp_writebuf*	next;

	for (buf = conn->queue_head; buf != NULL; buf = next)
	{
		next = buf->next;
		Memory_Free(buf->data);
		Memory_Free(buf);
	}
	conn->queue_head = NULL;
	conn->queue_tail = NULL;
}

//! Attempts to send as much of the pending write queue as possible (the socket is non-blocking)
static
e_cccerror	__AsyncTCP_FlushQueue(s_async_tcp* conn)
{
	struct async_tcp_writebuf*	buf;
	t_sintmax	sent;

	while ((buf = conn->queue_head) != NULL)
	{
		sent = (t_sintmax)send(conn->socket,
			(char const*)buf->data + buf->sent,
			(buf->size - buf->sent), 0);
		__Socket_UpdateErrno();
		if (sent < 0)
		{
			if (__Socket_IsErrorWouldBlock())
				return (ERROR_NONE); // try again once the socket becomes writable
			if CCCERROR(TRUE, ERROR_SYSTEM,
				"could not send queued data on async TCP connection")
				return (ERROR_SYSTEM);
		}
		buf->sent += (t_size)sent;
		if (buf->sent < buf->size)
			return (ERROR_NONE); // partial send: try again once the socket becomes writable
		conn->queue_head = buf->next;
		if (conn->queue_head == NULL)
			conn->queue_tail = NULL;
		Memory_Free(buf->data);
		Memory_Free(buf);
	}
	return (ERROR_NONE);
}

//! Checks the completion status of a pending non-blocking connection attempt
static
e_cccerror	__AsyncTCP_CheckConnect(s_async_tcp* conn)
{
	int	so_error = 0;
	socklen_t	length = sizeof(so_error);

	if (getsockopt(conn->socket, SOL_SOCKET, SO_ERROR, (char*)&so_error, &length) != 0)
	{
		__Socket_UpdateErrno();
		return (ERROR_SYSTEM);
	}
	if (so_error != 0)
	{
		errno = so_error;
		return (ERROR_SYSTEM);
	}
	return (ERROR_NONE);
}

//! The internal poll callback for a #s_async_tcp: dispatches connect/read/write events
static
void	__AsyncTCP_OnPoll(s_async_poll* poll, t_asyncpoll_events events)
{
	s_async_tcp*	conn = (s_async_tcp*)poll; // `poll` is the first member
	t_u8		buffer[ASYNC_NETWORK_BUFFER_SIZE];
	t_sintmax	received;
	e_cccerror	error;

	if (conn->connecting && (events & (ASYNCPOLL_WRITABLE | ASYNCPOLL_ERROR | ASYNCPOLL_DISCONNECT)))
	{	// a pending non-blocking connection attempt has completed (successfully or not)
		conn->connecting = FALSE;
		error = __AsyncTCP_CheckConnect(conn);
		if (error != ERROR_NONE)
			__AsyncTCP_ClearQueue(conn);
		__AsyncTCP_UpdateEvents(conn);
		if (conn->on_connect != NULL)
			conn->on_connect(conn, error);
		if (error != ERROR_NONE || conn->socket == SOCKET_INVALID)
			return; // the connection failed, or was closed from within the `on_connect` callback
		events &= ~(t_asyncpoll_events)ASYNCPOLL_WRITABLE; // the writability only signaled connect completion
	}
	if ((events & ASYNCPOLL_WRITABLE) && conn->queue_head != NULL)
	{
		__AsyncTCP_FlushQueue(conn);
		__AsyncTCP_UpdateEvents(conn);
	}
	if ((events & (ASYNCPOLL_READABLE | ASYNCPOLL_DISCONNECT)) && conn->reading)
	{	// read every byte which is currently available (the socket is non-blocking)
		// NB: the user's `on_read` callback may call AsyncTCP_Close() on this very
		// handle: hence the `socket != SOCKET_INVALID` checks after each invocation
		while (conn->reading && conn->socket != SOCKET_INVALID)
		{
			received = (t_sintmax)recv(conn->socket, (char*)buffer, sizeof(buffer), 0);
			__Socket_UpdateErrno();
			if (received < 0 && __Socket_IsErrorWouldBlock())
				break; // no more data for now
			if (received <= 0)
			{	// EOF, or read error: stop watching for reads, before invoking the callback
				// (the user typically calls AsyncTCP_Close() from within it)
				conn->reading = FALSE;
				__AsyncTCP_UpdateEvents(conn);
				conn->on_read(conn, buffer, received);
				break;
			}
			conn->on_read(conn, buffer, received);
			if ((t_size)received < sizeof(buffer))
				break; // we most likely drained the socket: poll again rather than looping
		}
	}
}



e_cccerror	AsyncTCP_Init(s_asyncloop* loop, s_async_tcp* conn, t_socket sock)
{
	e_cccerror	error;

	if CCCERROR((conn == NULL), ERROR_NULLPOINTER, "async TCP connection handle given is NULL")
		return (ERROR_NULLPOINTER);
	error = Socket_SetNonBlocking(sock, TRUE);
	if (error != ERROR_NONE)
		return (error);
	error = AsyncPoll_Init(loop, &conn->poll, (t_fd)sock);
	if (error != ERROR_NONE)
		return (error);
	conn->data = NULL;
	conn->socket = sock;
	conn->on_connect = NULL;
	conn->on_read = NULL;
	conn->connecting = FALSE;
	conn->reading = FALSE;
	conn->queue_head = NULL;
	conn->queue_tail = NULL;
	return (ERROR_NONE);
}



e_cccerror	AsyncTCP_Connect(s_asyncloop* loop, s_async_tcp* conn, s_sockaddr const* addr, f_async_tcp_connect on_connect)
{
	struct sockaddr_storage	native;
	socklen_t	native_length;
	t_socket	sock;
	e_cccerror	error;
	int	result;

	if CCCERROR((addr == NULL), ERROR_NULLPOINTER, "socket address given is NULL")
		return (ERROR_NULLPOINTER);
	native_length = __SockAddr_ToNative(&native, addr);
	if CCCERROR((native_length == 0), ERROR_INVALIDARGS,
		"invalid socket address given (family=%i)", (int)addr->family)
		return (ERROR_INVALIDARGS);
	sock = Socket_New(addr->family, SOCKTYPE_STREAM, SOCKPROTO_TCP);
	if (sock == SOCKET_INVALID)
		return (ERROR_SYSTEM);
	error = AsyncTCP_Init(loop, conn, sock);
	if (error != ERROR_NONE)
	{
		Socket_Close(sock);
		return (error);
	}
	conn->on_connect = on_connect;
	result = connect(sock, (struct sockaddr*)&native, native_length);
	__Socket_UpdateErrno();
	if (result == 0)
	{	// the connection was established immediately (typical for loopback connections):
		// still deliver the completion via the callback, for consistent user code
		if (on_connect != NULL)
			on_connect(conn, ERROR_NONE);
		return (ERROR_NONE);
	}
	if CCCERROR((!__Socket_IsErrorInProgress()), ERROR_SYSTEM,
		"could not connect async TCP connection to port %u", (unsigned)addr->port)
	{
		AsyncTCP_Close(conn);
		return (ERROR_SYSTEM);
	}
	conn->connecting = TRUE; // completion will be signaled by the socket becoming writable
	return (AsyncPoll_Start(&conn->poll, ASYNCPOLL_WRITABLE, __AsyncTCP_OnPoll));
}



e_cccerror	AsyncTCP_StartRead(s_async_tcp* conn, f_async_tcp_read on_read)
{
	if CCCERROR((conn == NULL), ERROR_NULLPOINTER, "async TCP connection handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((on_read == NULL), ERROR_NULLPOINTER, "read callback function given is NULL")
		return (ERROR_NULLPOINTER);
	conn->on_read = on_read;
	conn->reading = TRUE;
	return (AsyncPoll_Start(&conn->poll,
		(conn->connecting || conn->queue_head) ? (ASYNCPOLL_READABLE | ASYNCPOLL_WRITABLE) : ASYNCPOLL_READABLE,
		__AsyncTCP_OnPoll));
}



e_cccerror	AsyncTCP_StopRead(s_async_tcp* conn)
{
	if CCCERROR((conn == NULL), ERROR_NULLPOINTER, "async TCP connection handle given is NULL")
		return (ERROR_NULLPOINTER);
	conn->reading = FALSE;
	__AsyncTCP_UpdateEvents(conn);
	return (ERROR_NONE);
}



e_cccerror	AsyncTCP_Write(s_async_tcp* conn, void const* data, t_size n)
{
	struct async_tcp_writebuf*	buf;
	t_sintmax	sent = 0;

	if CCCERROR((conn == NULL), ERROR_NULLPOINTER, "async TCP connection handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (ERROR_NULLPOINTER);
	if (n == 0)
		return (ERROR_NONE);
	if (!conn->connecting && conn->queue_head == NULL)
	{	// nothing is queued: attempt to send as much as possible immediately
		sent = (t_sintmax)send(conn->socket, (char const*)data, n, 0);
		__Socket_UpdateErrno();
		if (sent < 0)
		{
			if CCCERROR((!__Socket_IsErrorWouldBlock()), ERROR_SYSTEM,
				"could not send data on async TCP connection")
				return (ERROR_SYSTEM);
			sent = 0;
		}
		if ((t_size)sent == n)
			return (ERROR_NONE); // everything was sent immediately: no queueing needed
	}
	// copy the unsent remainder to the write queue, to be flushed once the socket is writable
	buf = (struct async_tcp_writebuf*)Memory_New(sizeof(struct async_tcp_writebuf));
	if CCCERROR((buf == NULL), ERROR_ALLOCFAILURE, NULL)
		return (ERROR_ALLOCFAILURE);
	buf->next = NULL;
	buf->size = (n - (t_size)sent);
	buf->sent = 0;
	buf->data = (t_u8*)Memory_Duplicate((t_u8 const*)data + sent, buf->size);
	if CCCERROR((buf->data == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Free(buf);
		return (ERROR_ALLOCFAILURE);
	}
	if (conn->queue_tail != NULL)
		conn->queue_tail->next = buf;
	else
		conn->queue_head = buf;
	conn->queue_tail = buf;
	return (AsyncPoll_Start(&conn->poll,
		conn->reading ? (ASYNCPOLL_READABLE | ASYNCPOLL_WRITABLE) : ASYNCPOLL_WRITABLE,
		__AsyncTCP_OnPoll));
}



e_cccerror	AsyncTCP_Close(s_async_tcp* conn)
{
	if CCCERROR((conn == NULL), ERROR_NULLPOINTER, "async TCP connection handle given is NULL")
		return (ERROR_NULLPOINTER);
	AsyncPoll_Stop(&conn->poll);
	AsyncHandle_Detach(&conn->poll.base);
	__AsyncTCP_ClearQueue(conn);
	conn->connecting = FALSE;
	conn->reading = FALSE;
	if (conn->socket != SOCKET_INVALID)
	{
		Socket_Close(conn->socket);
		conn->socket = SOCKET_INVALID;
	}
	return (ERROR_NONE);
}
