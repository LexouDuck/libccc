
#if !(defined(_WIN32) && !defined(__CYGWIN__))
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L	// needed to expose getaddrinfo()/getnameinfo() (and pthread_rwlock_t etc), when compiling with a strict `-std=c**` option
	#endif
#endif

#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/sys/socket.h"
#include "libccc/sys/network.h"

#include "../socket/socket_private.h"

#ifndef __NOSTD__
	#if !(defined(_WIN32) && !defined(__CYGWIN__))
		#include <netdb.h>
	#endif
#endif

#include LIBCONFIG_ERROR_INCLUDE



//! Performs the getaddrinfo() call for the given `host`, returning the native result list (or NULL)
static
struct addrinfo*	__Network_GetAddrInfo(t_char const* host)
{
	struct addrinfo	hints;
	struct addrinfo*	result = NULL;
	int	status;

	Memory_Clear(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC; // accept both IPv4 and IPv6 results
	hints.ai_socktype = SOCK_STREAM; // avoids getting each address in triplicate (one per socktype)
	status = getaddrinfo(host, NULL, &hints, &result);
	if CCCERROR((status != 0), ERROR_NOTFOUND,
		"could not resolve hostname \"%s\": %s", host, gai_strerror(status))
		return (NULL);
	return (result);
}



e_cccerror	Network_Resolve(s_sockaddr* dest, t_char const* host, t_port port)
{
	struct addrinfo*	info;
	struct addrinfo*	current;
	struct sockaddr_storage	native;
	e_cccerror	error = ERROR_NOTFOUND;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination address given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((host == NULL), ERROR_NULLPOINTER, "hostname given is NULL")
		return (ERROR_NULLPOINTER);
	*dest = SOCKADDR_NULL;
	info = __Network_GetAddrInfo(host);
	if (info == NULL)
		return (ERROR_NOTFOUND);
	for (current = info; current != NULL; current = current->ai_next)
	{
		if (current->ai_family != AF_INET && current->ai_family != AF_INET6)
			continue;
		Memory_Clear(&native, sizeof(native));
		Memory_Copy(&native, current->ai_addr, current->ai_addrlen);
		error = __SockAddr_FromNative(dest, &native);
		if (error == ERROR_NONE)
		{
			dest->port = port;
			break;
		}
	}
	freeaddrinfo(info);
	if CCCERROR((error != ERROR_NONE), ERROR_NOTFOUND,
		"no usable address found for hostname \"%s\"", host)
		return (ERROR_NOTFOUND);
	return (ERROR_NONE);
}



_MALLOC()
s_sockaddr*	Network_Resolve_All(t_uint* dest_count, t_char const* host, t_port port)
{
	struct addrinfo*	info;
	struct addrinfo*	current;
	struct sockaddr_storage	native;
	s_sockaddr*	result;
	t_uint	amount = 0;
	t_uint	i = 0;

	if (dest_count != NULL)
		*dest_count = 0;
	if CCCERROR((host == NULL), ERROR_NULLPOINTER, "hostname given is NULL")
		return (NULL);
	info = __Network_GetAddrInfo(host);
	if (info == NULL)
		return (NULL);
	for (current = info; current != NULL; current = current->ai_next)
	{
		if (current->ai_family == AF_INET || current->ai_family == AF_INET6)
			amount += 1;
	}
	if CCCERROR((amount == 0), ERROR_NOTFOUND,
		"no usable address found for hostname \"%s\"", host)
	{
		freeaddrinfo(info);
		return (NULL);
	}
	result = (s_sockaddr*)Memory_New(amount * sizeof(s_sockaddr));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		freeaddrinfo(info);
		return (NULL);
	}
	for (current = info; current != NULL; current = current->ai_next)
	{
		if (current->ai_family != AF_INET && current->ai_family != AF_INET6)
			continue;
		Memory_Clear(&native, sizeof(native));
		Memory_Copy(&native, current->ai_addr, current->ai_addrlen);
		if (__SockAddr_FromNative(&result[i], &native) == ERROR_NONE)
		{
			result[i].port = port;
			i += 1;
		}
	}
	freeaddrinfo(info);
	if (dest_count != NULL)
		*dest_count = i;
	return (result);
}



_MALLOC()
t_char*	Network_GetHostName(s_sockaddr const* addr)
{
	struct sockaddr_storage	native;
	socklen_t	native_length;
	t_char	hostname[NETWORK_HOSTNAME_MAXLENGTH];
	int	status;

	if CCCERROR((addr == NULL), ERROR_NULLPOINTER, "socket address given is NULL")
		return (NULL);
	native_length = __SockAddr_ToNative(&native, addr);
	if CCCERROR((native_length == 0), ERROR_INVALIDARGS,
		"invalid socket address given (family=%i)", (int)addr->family)
		return (NULL);
	status = getnameinfo((struct sockaddr*)&native, native_length,
		hostname, sizeof(hostname), NULL, 0, 0);
	if CCCERROR((status != 0), ERROR_NOTFOUND,
		"could not get hostname for address: %s", gai_strerror(status))
		return (NULL);
	return (String_Duplicate(hostname));
}
