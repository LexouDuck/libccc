
#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/text/format.h"
#include "libccc/sys/socket.h"

#include "socket_private.h"

#include LIBCONFIG_ERROR_INCLUDE



s_sockaddr	SockAddr_New(t_char const* ip, t_port port)
{
	s_sockaddr	result = SOCKADDR_NULL;

	if (ip == NULL)
		return (SockAddr_Any(SOCKAF_IPV4, port));
	if (SockAddr_Parse(&result, ip) != ERROR_NONE)
		return (SOCKADDR_NULL);
	result.port = port;
	return (result);
}



s_sockaddr	SockAddr_Any(e_sockaf family, t_port port)
{
	s_sockaddr	result = SOCKADDR_NULL;

	if CCCERROR((family != SOCKAF_IPV4 && family != SOCKAF_IPV6), ERROR_INVALIDENUM,
		"invalid socket address family given: %i", (int)family)
		return (SOCKADDR_NULL);
	result.family = family;
	result.port = port;
	// the "any" wildcard address is all-zero bytes, for both IPv4 and IPv6
	return (result);
}



s_sockaddr	SockAddr_LocalHost(e_sockaf family, t_port port)
{
	s_sockaddr	result = SOCKADDR_NULL;

	if CCCERROR((family != SOCKAF_IPV4 && family != SOCKAF_IPV6), ERROR_INVALIDENUM,
		"invalid socket address family given: %i", (int)family)
		return (SOCKADDR_NULL);
	result.family = family;
	result.port = port;
	if (family == SOCKAF_IPV4)
	{	// 127.0.0.1
		result.ip.ipv4[0] = 127;
		result.ip.ipv4[3] = 1;
	}
	else
	{	// ::1
		result.ip.ipv6[15] = 1;
	}
	return (result);
}



e_cccerror	SockAddr_Parse(s_sockaddr* dest, t_char const* str)
{
	t_u8	tmp[16];

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination address given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "address string given is NULL")
		return (ERROR_NULLPOINTER);
	if (inet_pton(AF_INET, str, tmp) == 1)
	{
		dest->family = SOCKAF_IPV4;
		Memory_Copy(dest->ip.ipv4, tmp, 4);
		return (ERROR_NONE);
	}
	if (inet_pton(AF_INET6, str, tmp) == 1)
	{
		dest->family = SOCKAF_IPV6;
		Memory_Copy(dest->ip.ipv6, tmp, 16);
		return (ERROR_NONE);
	}
	dest->family = SOCKAF_UNSPEC;
	if CCCERROR(TRUE, ERROR_PARSE,
		"could not parse IP address from string: \"%s\"", str)
		return (ERROR_PARSE);
	return (ERROR_PARSE);
}



t_size	SockAddr_ToString_Buf(t_char* dest, s_sockaddr const* addr, t_size max_length)
{
	t_char	ip_str[SOCKADDR_STRING_MAXLENGTH];
	int	native_family;
	void const*	native_ip;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination buffer given is NULL")
		return (0);
	if CCCERROR((addr == NULL), ERROR_NULLPOINTER, "socket address given is NULL")
		return (0);
	if (addr->family == SOCKAF_IPV4)
	{
		native_family = AF_INET;
		native_ip = addr->ip.ipv4;
	}
	else if (addr->family == SOCKAF_IPV6)
	{
		native_family = AF_INET6;
		native_ip = addr->ip.ipv6;
	}
	else
	{
		if CCCERROR(TRUE, ERROR_INVALIDARGS,
			"invalid socket address given (family=%i)", (int)addr->family)
			return (0);
		return (0);
	}
	if CCCERROR((inet_ntop(native_family, (void*)native_ip, ip_str, sizeof(ip_str)) == NULL),
		ERROR_SYSTEM, "could not convert IP address to string")
		return (0);
	if (addr->port == PORT_ANY)
		return (String_Format_N(dest, max_length, "%s", ip_str));
	else if (addr->family == SOCKAF_IPV6)
		return (String_Format_N(dest, max_length, "[%s]:%u", ip_str, (unsigned)addr->port));
	else
		return (String_Format_N(dest, max_length, "%s:%u", ip_str, (unsigned)addr->port));
}



_MALLOC()
t_char*	SockAddr_ToString(s_sockaddr const* addr)
{
	t_char	buffer[SOCKADDR_STRING_MAXLENGTH];

	if (SockAddr_ToString_Buf(buffer, addr, sizeof(buffer)) == 0)
		return (NULL);
	return (String_Duplicate(buffer));
}



t_bool	SockAddr_Equals(s_sockaddr const* addr1, s_sockaddr const* addr2)
{
	if (addr1 == addr2)
		return (TRUE);
	if (addr1 == NULL || addr2 == NULL)
		return (FALSE);
	if (addr1->family != addr2->family)
		return (FALSE);
	if (addr1->port != addr2->port)
		return (FALSE);
	if (addr1->family == SOCKAF_IPV4)
		return (Memory_Equals(addr1->ip.ipv4, addr2->ip.ipv4, 4));
	if (addr1->family == SOCKAF_IPV6)
		return (Memory_Equals(addr1->ip.ipv6, addr2->ip.ipv6, 16));
	return (TRUE);
}
