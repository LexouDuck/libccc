
#include "libccc.h"
#include "libccc/sys/socket.h"

#include "socket_private.h"

#include LIBCONFIG_ERROR_INCLUDE



e_cccerror	Socket_GetAddress(s_sockaddr* dest_addr, t_socket sock)
{
	struct sockaddr_storage	native;
	socklen_t	native_length = sizeof(native);
	int	result;

	if CCCERROR((dest_addr == NULL), ERROR_NULLPOINTER, "destination address given is NULL")
		return (ERROR_NULLPOINTER);
	result = getsockname(sock, (struct sockaddr*)&native, &native_length);
	__Socket_UpdateErrno();
	if CCCERROR((result != 0), ERROR_SYSTEM,
		"could not get local address of socket %zi", (t_size)sock)
		return (ERROR_SYSTEM);
	return (__SockAddr_FromNative(dest_addr, &native));
}



e_cccerror	Socket_GetPeerAddress(s_sockaddr* dest_addr, t_socket sock)
{
	struct sockaddr_storage	native;
	socklen_t	native_length = sizeof(native);
	int	result;

	if CCCERROR((dest_addr == NULL), ERROR_NULLPOINTER, "destination address given is NULL")
		return (ERROR_NULLPOINTER);
	result = getpeername(sock, (struct sockaddr*)&native, &native_length);
	__Socket_UpdateErrno();
	if CCCERROR((result != 0), ERROR_SYSTEM,
		"could not get peer address of socket %zi", (t_size)sock)
		return (ERROR_SYSTEM);
	return (__SockAddr_FromNative(dest_addr, &native));
}
