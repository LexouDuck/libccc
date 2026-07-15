
#include "libccc.h"
#include "libccc/sys/socket.h"

#include "socket_private.h"

#include LIBCONFIG_ERROR_INCLUDE



t_sintmax	Socket_Recv(t_socket sock, void* buffer, t_size n, t_sockmsg flags)
{
	t_sintmax	result;

	if CCCERROR((buffer == NULL), ERROR_NULLPOINTER, "buffer given is NULL")
		return (-1);
	if (n == 0)
		return (0);
	result = (t_sintmax)recv(sock, (char*)buffer, n, __Socket_NativeMsgFlags(flags));
	__Socket_UpdateErrno();
	if CCCERROR((result < 0), ERROR_SYSTEM,
		"could not receive data on socket %zi", (t_size)sock)
		return (result);
	return (result);
}



t_sintmax	Socket_Recv_All(t_socket sock, void* buffer, t_size n)
{
	t_sintmax	received;
	t_size		total = 0;

	if CCCERROR((buffer == NULL), ERROR_NULLPOINTER, "buffer given is NULL")
		return (-1);
	while (total < n)
	{
		received = (t_sintmax)recv(sock,
			(char*)buffer + total,
			(n - total),
			0);
		__Socket_UpdateErrno();
		if CCCERROR((received < 0), ERROR_SYSTEM,
			"could not receive %zu bytes on socket %zi (%zu bytes were received)",
			n, (t_size)sock, total)
			return (received);
		if (received == 0) // the peer has closed the connection
			break;
		total += (t_size)received;
	}
	return ((t_sintmax)total);
}



t_sintmax	Socket_RecvFrom(t_socket sock, void* buffer, t_size n, t_sockmsg flags, s_sockaddr* dest_addr)
{
	struct sockaddr_storage	native;
	socklen_t	native_length = sizeof(native);
	t_sintmax	result;

	if CCCERROR((buffer == NULL), ERROR_NULLPOINTER, "buffer given is NULL")
		return (-1);
	result = (t_sintmax)recvfrom(sock,
		(char*)buffer, n,
		__Socket_NativeMsgFlags(flags),
		(struct sockaddr*)&native, &native_length);
	__Socket_UpdateErrno();
	if CCCERROR((result < 0), ERROR_SYSTEM,
		"could not receive data on socket %zi", (t_size)sock)
		return (result);
	if (dest_addr != NULL)
		__SockAddr_FromNative(dest_addr, &native);
	return (result);
}
