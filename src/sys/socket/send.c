
#include "libccc.h"
#include "libccc/string.h"
#include "libccc/sys/socket.h"

#include "socket_private.h"

#include LIBCONFIG_ERROR_INCLUDE



t_sintmax	Socket_Send(t_socket sock, void const* data, t_size n, t_sockmsg flags)
{
	t_sintmax	result;

	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (-1);
	if (n == 0)
		return (0);
	result = (t_sintmax)send(sock, (char const*)data, n, __Socket_NativeMsgFlags(flags));
	__Socket_UpdateErrno();
	if CCCERROR((result < 0), ERROR_SYSTEM,
		"could not send %zu bytes on socket %zi", n, (t_size)sock)
		return (result);
	return (result);
}



e_cccerror	Socket_Send_All(t_socket sock, void const* data, t_size n)
{
	t_sintmax	sent;
	t_size		total = 0;

	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (ERROR_NULLPOINTER);
	while (total < n)
	{
		sent = (t_sintmax)send(sock,
			(char const*)data + total,
			(n - total),
			0);
		__Socket_UpdateErrno();
		if CCCERROR((sent < 0), ERROR_SYSTEM,
			"could not send %zu bytes on socket %zi (%zu bytes were sent)",
			n, (t_size)sock, total)
			return (ERROR_SYSTEM);
		total += (t_size)sent;
	}
	return (ERROR_NONE);
}



e_cccerror	Socket_Send_String(t_socket sock, t_char const* str)
{
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (ERROR_NULLPOINTER);
	return (Socket_Send_All(sock, str, String_Length(str)));
}



t_sintmax	Socket_SendTo(t_socket sock, void const* data, t_size n, t_sockmsg flags, s_sockaddr const* addr)
{
	struct sockaddr_storage	native;
	socklen_t	native_length;
	t_sintmax	result;

	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (-1);
	if CCCERROR((addr == NULL), ERROR_NULLPOINTER, "socket address given is NULL")
		return (-1);
	native_length = __SockAddr_ToNative(&native, addr);
	if CCCERROR((native_length == 0), ERROR_INVALIDARGS,
		"invalid socket address given (family=%i)", (int)addr->family)
		return (-1);
	result = (t_sintmax)sendto(sock,
		(char const*)data, n,
		__Socket_NativeMsgFlags(flags),
		(struct sockaddr*)&native, native_length);
	__Socket_UpdateErrno();
	if CCCERROR((result < 0), ERROR_SYSTEM,
		"could not send %zu bytes on socket %zi, to port %u",
		n, (t_size)sock, (unsigned)addr->port)
		return (result);
	return (result);
}
