
#include "libccc.h"
#include "libccc/sys/socket.h"

#include "socket_private.h"

#include LIBCONFIG_ERROR_INCLUDE



//! The default `backlog` value used by Socket_Listen(), when given a `backlog` of `0`
#define SOCKET_LISTEN_DEFAULT_BACKLOG	16



e_cccerror	Socket_Bind(t_socket sock, s_sockaddr const* addr)
{
	struct sockaddr_storage	native;
	socklen_t	native_length;
	int	result;

	if CCCERROR((addr == NULL), ERROR_NULLPOINTER, "socket address given is NULL")
		return (ERROR_NULLPOINTER);
	native_length = __SockAddr_ToNative(&native, addr);
	if CCCERROR((native_length == 0), ERROR_INVALIDARGS,
		"invalid socket address given (family=%i)", (int)addr->family)
		return (ERROR_INVALIDARGS);
	result = bind(sock, (struct sockaddr*)&native, native_length);
	__Socket_UpdateErrno();
	if CCCERROR((result != 0), ERROR_SYSTEM,
		"could not bind socket %zi to port %u", (t_size)sock, (unsigned)addr->port)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



e_cccerror	Socket_Listen(t_socket sock, t_uint backlog)
{
	int	result;

	if (backlog == 0)
		backlog = SOCKET_LISTEN_DEFAULT_BACKLOG;
	result = listen(sock, (int)backlog);
	__Socket_UpdateErrno();
	if CCCERROR((result != 0), ERROR_SYSTEM,
		"could not listen on socket %zi", (t_size)sock)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



t_socket	Socket_Accept(t_socket sock, s_sockaddr* dest_addr)
{
	struct sockaddr_storage	native;
	socklen_t	native_length = sizeof(native);
	t_socket	result;

	result = (t_socket)accept(sock, (struct sockaddr*)&native, &native_length);
	__Socket_UpdateErrno();
	if CCCERROR(SOCKET_NATIVE_FAILED(result), ERROR_SYSTEM,
		"could not accept connection on socket %zi", (t_size)sock)
		return (SOCKET_INVALID);
	if (dest_addr != NULL)
		__SockAddr_FromNative(dest_addr, &native);
	return (result);
}



e_cccerror	Socket_Connect(t_socket sock, s_sockaddr const* addr)
{
	struct sockaddr_storage	native;
	socklen_t	native_length;
	int	result;

	if CCCERROR((addr == NULL), ERROR_NULLPOINTER, "socket address given is NULL")
		return (ERROR_NULLPOINTER);
	native_length = __SockAddr_ToNative(&native, addr);
	if CCCERROR((native_length == 0), ERROR_INVALIDARGS,
		"invalid socket address given (family=%i)", (int)addr->family)
		return (ERROR_INVALIDARGS);
	result = connect(sock, (struct sockaddr*)&native, native_length);
	__Socket_UpdateErrno();
	if CCCERROR((result != 0), ERROR_SYSTEM,
		"could not connect socket %zi to port %u", (t_size)sock, (unsigned)addr->port)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}
