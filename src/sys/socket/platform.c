
#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/sys/socket.h"

#include "socket_private.h"

#include LIBCONFIG_ERROR_INCLUDE



/*============================================================================*\
||                          Socket Library Lifecycle                          ||
\*============================================================================*/

#if (defined(_WIN32) && !defined(__CYGWIN__))

#include "libccc/sys/thread.h"

static t_bool	socket_wsa_initialized = FALSE;
static t_mutex	socket_wsa_mutex = MUTEX_INITIALIZER;

e_cccerror	Socket_Init(void)
{
	WSADATA	wsadata;
	int		result;

	Mutex_Lock(&socket_wsa_mutex);
	if (socket_wsa_initialized)
	{
		Mutex_Unlock(&socket_wsa_mutex);
		return (ERROR_NONE);
	}
	result = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if CCCERROR((result != 0), ERROR_SYSTEM,
		"call to WSAStartup() failed, with error code %i", result)
	{
		Mutex_Unlock(&socket_wsa_mutex);
		return (ERROR_SYSTEM);
	}
	socket_wsa_initialized = TRUE;
	Mutex_Unlock(&socket_wsa_mutex);
	return (ERROR_NONE);
}

e_cccerror	Socket_Exit(void)
{
	int	result;

	Mutex_Lock(&socket_wsa_mutex);
	if (!socket_wsa_initialized)
	{
		Mutex_Unlock(&socket_wsa_mutex);
		return (ERROR_NONE);
	}
	socket_wsa_initialized = FALSE;
	result = WSACleanup();
	Mutex_Unlock(&socket_wsa_mutex);
	if CCCERROR((result != 0), ERROR_SYSTEM,
		"call to WSACleanup() failed")
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}

#else

e_cccerror	Socket_Init(void)
{
	return (ERROR_NONE);
}

e_cccerror	Socket_Exit(void)
{
	return (ERROR_NONE);
}

#endif



/*============================================================================*\
||                        Internal Conversion Helpers                         ||
\*============================================================================*/

void	__Socket_UpdateErrno(void)
{
#if (defined(_WIN32) && !defined(__CYGWIN__))
	errno = WSAGetLastError();
#endif
}

t_bool	__Socket_IsErrorWouldBlock(void)
{
#if (defined(_WIN32) && !defined(__CYGWIN__))
	return (errno == WSAEWOULDBLOCK);
#else
	return (errno == EWOULDBLOCK || errno == EAGAIN);
#endif
}

t_bool	__Socket_IsErrorInProgress(void)
{
#if (defined(_WIN32) && !defined(__CYGWIN__))
	return (errno == WSAEWOULDBLOCK); // winsock reports in-progress connects with WSAEWOULDBLOCK
#else
	return (errno == EINPROGRESS);
#endif
}



int	__Socket_NativeAF(e_sockaf family)
{
	switch (family)
	{
		case SOCKAF_UNSPEC:	return (AF_UNSPEC);
#if (defined(_WIN32) && !defined(__CYGWIN__))
		case SOCKAF_LOCAL:	return (-1); // AF_UNIX requires <afunix.h>, and a path-capable address struct: TODO
#else
		case SOCKAF_LOCAL:	return (AF_UNIX);
#endif
		case SOCKAF_IPV4:	return (AF_INET);
		case SOCKAF_IPV6:	return (AF_INET6);
		default:			return (-1);
	}
}

e_sockaf	__Socket_FromNativeAF(int native_family)
{
	switch (native_family)
	{
#if !(defined(_WIN32) && !defined(__CYGWIN__))
		case AF_UNIX:	return (SOCKAF_LOCAL);
#endif
		case AF_INET:	return (SOCKAF_IPV4);
		case AF_INET6:	return (SOCKAF_IPV6);
		default:		return (SOCKAF_UNSPEC);
	}
}

int	__Socket_NativeType(e_socktype type)
{
	switch (type)
	{
		case SOCKTYPE_STREAM:	return (SOCK_STREAM);
		case SOCKTYPE_DGRAM:	return (SOCK_DGRAM);
		case SOCKTYPE_RAW:		return (SOCK_RAW);
		default:				return (-1);
	}
}

int	__Socket_NativeProto(e_sockproto protocol)
{
	switch (protocol)
	{
		case SOCKPROTO_DEFAULT:	return (0);
		case SOCKPROTO_TCP:		return (IPPROTO_TCP);
		case SOCKPROTO_UDP:		return (IPPROTO_UDP);
		default:				return (-1);
	}
}

int	__Socket_NativeMsgFlags(t_sockmsg flags)
{
	int	result = 0;

	if (flags & SOCKMSG_PEEK)		result |= MSG_PEEK;
	if (flags & SOCKMSG_OUTOFBAND)	result |= MSG_OOB;
	if (flags & SOCKMSG_WAITALL)	result |= MSG_WAITALL;
#ifdef MSG_DONTWAIT
	if (flags & SOCKMSG_DONTWAIT)	result |= MSG_DONTWAIT;
#endif
	return (result);
}



socklen_t	__SockAddr_ToNative(struct sockaddr_storage* dest, s_sockaddr const* addr)
{
	Memory_Clear(dest, sizeof(struct sockaddr_storage));
	if (addr->family == SOCKAF_IPV4)
	{
		struct sockaddr_in*	native = (struct sockaddr_in*)dest;
		native->sin_family = AF_INET;
		native->sin_port = htons(addr->port);
		Memory_Copy(&native->sin_addr, addr->ip.ipv4, 4);
		return ((socklen_t)sizeof(struct sockaddr_in));
	}
	else if (addr->family == SOCKAF_IPV6)
	{
		struct sockaddr_in6*	native = (struct sockaddr_in6*)dest;
		native->sin6_family = AF_INET6;
		native->sin6_port = htons(addr->port);
		Memory_Copy(&native->sin6_addr, addr->ip.ipv6, 16);
		return ((socklen_t)sizeof(struct sockaddr_in6));
	}
	return ((socklen_t)0);
}

e_cccerror	__SockAddr_FromNative(s_sockaddr* dest, struct sockaddr_storage const* src)
{
	*dest = SOCKADDR_NULL;
	if (src->ss_family == AF_INET)
	{
		struct sockaddr_in const*	native = (struct sockaddr_in const*)src;
		dest->family = SOCKAF_IPV4;
		dest->port = ntohs(native->sin_port);
		Memory_Copy(dest->ip.ipv4, &native->sin_addr, 4);
		return (ERROR_NONE);
	}
	else if (src->ss_family == AF_INET6)
	{
		struct sockaddr_in6 const*	native = (struct sockaddr_in6 const*)src;
		dest->family = SOCKAF_IPV6;
		dest->port = ntohs(native->sin6_port);
		Memory_Copy(dest->ip.ipv6, &native->sin6_addr, 16);
		return (ERROR_NONE);
	}
	dest->family = __Socket_FromNativeAF(src->ss_family);
	return (ERROR_NONE);
}
