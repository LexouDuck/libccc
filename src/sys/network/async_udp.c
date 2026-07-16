
#ifndef __NOSTD__
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L	// needed to expose POSIX socket APIs, when compiling with a strict `-std=c**` option
	#endif
#endif

#include "libccc.h"
#include "libccc/sys/socket.h"
#include "libccc/sys/network.h"
#include "libccc/sys/async.h"

#include "../socket/socket_private.h"

#include LIBCONFIG_ERROR_INCLUDE



//! The internal poll callback for a #s_async_udp handle: receives every pending datagram
static
void	__AsyncUDP_OnPoll(s_async_poll* poll, t_asyncpoll_events events)
{
	s_async_udp*	udp = (s_async_udp*)poll; // `poll` is the first member
	t_u8	buffer[ASYNC_NETWORK_BUFFER_SIZE];
	struct sockaddr_storage	native;
	socklen_t	native_length;
	s_sockaddr	from;
	t_sintmax	received;

	(void)events;
	// NB: the user's `on_recv` callback may call AsyncUDP_Close() on this very
	// handle: hence the `socket != SOCKET_INVALID` check on each iteration
	while (udp->on_recv != NULL && udp->socket != SOCKET_INVALID)
	{	// receive every datagram which is currently pending (the socket is non-blocking)
		native_length = sizeof(native);
		received = (t_sintmax)recvfrom(udp->socket, (char*)buffer, sizeof(buffer), 0,
			(struct sockaddr*)&native, &native_length);
		__Socket_UpdateErrno();
		if (received < 0)
		{
			if CCCERROR((!__Socket_IsErrorWouldBlock()), ERROR_SYSTEM,
				"could not receive datagram on async UDP handle")
				return;
			return; // no more datagrams for now
		}
		__SockAddr_FromNative(&from, &native);
		udp->on_recv(udp, buffer, (t_size)received, &from);
	}
}



e_cccerror	AsyncUDP_Init(s_asyncloop* loop, s_async_udp* udp, t_socket sock)
{
	e_cccerror	error;

	if CCCERROR((udp == NULL), ERROR_NULLPOINTER, "async UDP handle given is NULL")
		return (ERROR_NULLPOINTER);
	error = Socket_SetNonBlocking(sock, TRUE);
	if (error != ERROR_NONE)
		return (error);
	error = AsyncPoll_Init(loop, &udp->poll, (t_fd)sock);
	if (error != ERROR_NONE)
		return (error);
	udp->data = NULL;
	udp->socket = sock;
	udp->on_recv = NULL;
	return (ERROR_NONE);
}



e_cccerror	AsyncUDP_StartRecv(s_async_udp* udp, f_async_udp_recv on_recv)
{
	if CCCERROR((udp == NULL), ERROR_NULLPOINTER, "async UDP handle given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((on_recv == NULL), ERROR_NULLPOINTER, "datagram receive callback given is NULL")
		return (ERROR_NULLPOINTER);
	udp->on_recv = on_recv;
	return (AsyncPoll_Start(&udp->poll, ASYNCPOLL_READABLE, __AsyncUDP_OnPoll));
}



e_cccerror	AsyncUDP_StopRecv(s_async_udp* udp)
{
	if CCCERROR((udp == NULL), ERROR_NULLPOINTER, "async UDP handle given is NULL")
		return (ERROR_NULLPOINTER);
	udp->on_recv = NULL;
	return (AsyncPoll_Stop(&udp->poll));
}



e_cccerror	AsyncUDP_Close(s_async_udp* udp)
{
	if CCCERROR((udp == NULL), ERROR_NULLPOINTER, "async UDP handle given is NULL")
		return (ERROR_NULLPOINTER);
	AsyncPoll_Stop(&udp->poll);
	AsyncHandle_Detach(&udp->poll.base);
	udp->on_recv = NULL;
	if (udp->socket != SOCKET_INVALID)
	{
		Socket_Close(udp->socket);
		udp->socket = SOCKET_INVALID;
	}
	return (ERROR_NONE);
}
