
#include "libccc.h"
#include "libccc/sys/socket.h"
#include "libccc/sys/network.h"

#include "../socket/socket_private.h"

#include LIBCONFIG_ERROR_INCLUDE



t_socket	UDP_New(s_sockaddr const* addr)
{
	t_socket	sock;
	e_sockaf	family = (addr ? addr->family : SOCKAF_IPV4);

	sock = Socket_New(family, SOCKTYPE_DGRAM, SOCKPROTO_UDP);
	if (sock == SOCKET_INVALID)
		return (SOCKET_INVALID);
	if (addr != NULL)
	{
		if (Socket_Bind(sock, addr) != ERROR_NONE)
		{
			Socket_Close(sock);
			return (SOCKET_INVALID);
		}
	}
	return (sock);
}



t_sintmax	UDP_SendTo(t_socket sock, void const* data, t_size n, t_char const* host, t_port port)
{
	s_sockaddr	addr;

	if CCCERROR((host == NULL), ERROR_NULLPOINTER, "hostname given is NULL")
		return (-1);
	if (Network_Resolve(&addr, host, port) != ERROR_NONE)
		return (-1);
	return (Socket_SendTo(sock, data, n, SOCKMSG_NONE, &addr));
}



t_sintmax	UDP_RecvFrom(t_socket sock, void* buffer, t_size n, s_sockaddr* dest_addr)
{
	return (Socket_RecvFrom(sock, buffer, n, SOCKMSG_NONE, dest_addr));
}
