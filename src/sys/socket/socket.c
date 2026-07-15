
#include "libccc.h"
#include "libccc/sys/socket.h"

#include "socket_private.h"

#include LIBCONFIG_ERROR_INCLUDE



t_socket	Socket_New(e_sockaf family, e_socktype type, e_sockproto protocol)
{
	t_socket	result;
	int	native_family = __Socket_NativeAF(family);
	int	native_type = __Socket_NativeType(type);
	int	native_proto = __Socket_NativeProto(protocol);

	if CCCERROR((native_family < 0), ERROR_INVALIDENUM,
		"invalid socket address family given: %i", (int)family)
		return (SOCKET_INVALID);
	if CCCERROR((native_type < 0), ERROR_INVALIDENUM,
		"invalid socket type given: %i", (int)type)
		return (SOCKET_INVALID);
	if CCCERROR((native_proto < 0), ERROR_INVALIDENUM,
		"invalid socket protocol given: %i", (int)protocol)
		return (SOCKET_INVALID);
	result = (t_socket)socket(native_family, native_type, native_proto);
	__Socket_UpdateErrno();
	if CCCERROR(SOCKET_NATIVE_FAILED(result), ERROR_SYSTEM,
		"could not create socket (family=%i, type=%i, protocol=%i)",
		(int)family, (int)type, (int)protocol)
		return (SOCKET_INVALID);
	return (result);
}



e_cccerror	Socket_Close(t_socket sock)
{
	int	result;

#if (defined(_WIN32) && !defined(__CYGWIN__))
	result = closesocket((SOCKET)sock);
#else
	result = close(sock);
#endif
	__Socket_UpdateErrno();
	if CCCERROR((result != 0), ERROR_SYSTEM,
		"could not close socket %zi", (t_size)sock)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



e_cccerror	Socket_Shutdown(t_socket sock, e_sockshutdown how)
{
	int	result;
	int	native_how;

	switch (how)
	{
#if (defined(_WIN32) && !defined(__CYGWIN__))
		case SOCKSHUTDOWN_RECV:	native_how = SD_RECEIVE;	break;
		case SOCKSHUTDOWN_SEND:	native_how = SD_SEND;		break;
		case SOCKSHUTDOWN_BOTH:	native_how = SD_BOTH;		break;
#else
		case SOCKSHUTDOWN_RECV:	native_how = SHUT_RD;		break;
		case SOCKSHUTDOWN_SEND:	native_how = SHUT_WR;		break;
		case SOCKSHUTDOWN_BOTH:	native_how = SHUT_RDWR;		break;
#endif
		default:
			if CCCERROR(TRUE, ERROR_INVALIDENUM,
				"invalid socket shutdown mode given: %i", (int)how)
				return (ERROR_INVALIDENUM);
			return (ERROR_INVALIDENUM);
	}
	result = shutdown(sock, native_how);
	__Socket_UpdateErrno();
	if CCCERROR((result != 0), ERROR_SYSTEM,
		"could not shutdown socket %zi", (t_size)sock)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}
