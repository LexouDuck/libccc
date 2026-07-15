
#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/sys/socket.h"
#include "libccc/sys/network.h"

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
