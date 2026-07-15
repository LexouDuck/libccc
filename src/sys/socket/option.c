
#include "libccc.h"
#include "libccc/sys/socket.h"

#include "socket_private.h"

#include LIBCONFIG_ERROR_INCLUDE



//! Maps a portable #e_sockopt value to the native (level, option) pair; returns FALSE if invalid
static
t_bool	__Socket_NativeOption(e_sockopt option, int* dest_level, int* dest_option)
{
	switch (option)
	{
		case SOCKOPT_REUSEADDR:	*dest_level = SOL_SOCKET;	*dest_option = SO_REUSEADDR;	return (TRUE);
		case SOCKOPT_KEEPALIVE:	*dest_level = SOL_SOCKET;	*dest_option = SO_KEEPALIVE;	return (TRUE);
		case SOCKOPT_BROADCAST:	*dest_level = SOL_SOCKET;	*dest_option = SO_BROADCAST;	return (TRUE);
		case SOCKOPT_NODELAY:	*dest_level = IPPROTO_TCP;	*dest_option = TCP_NODELAY;		return (TRUE);
		default:	return (FALSE);
	}
}



e_cccerror	Socket_SetOption_Bool(t_socket sock, e_sockopt option, t_bool value)
{
	int	level;
	int	native_option;
	int	native_value = (value ? 1 : 0);
	int	result;

	if CCCERROR(!__Socket_NativeOption(option, &level, &native_option), ERROR_INVALIDENUM,
		"invalid socket option given: %i", (int)option)
		return (ERROR_INVALIDENUM);
	result = setsockopt(sock, level, native_option,
		(char const*)&native_value, sizeof(native_value));
	__Socket_UpdateErrno();
	if CCCERROR((result != 0), ERROR_SYSTEM,
		"could not set option %i for socket %zi", (int)option, (t_size)sock)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
}



t_bool	Socket_GetOption_Bool(t_socket sock, e_sockopt option)
{
	int	level;
	int	native_option;
	int	native_value = 0;
	socklen_t	length = sizeof(native_value);
	int	result;

	if CCCERROR(!__Socket_NativeOption(option, &level, &native_option), ERROR_INVALIDENUM,
		"invalid socket option given: %i", (int)option)
		return (FALSE);
	result = getsockopt(sock, level, native_option,
		(char*)&native_value, &length);
	__Socket_UpdateErrno();
	if CCCERROR((result != 0), ERROR_SYSTEM,
		"could not get option %i for socket %zi", (int)option, (t_size)sock)
		return (FALSE);
	return (native_value != 0);
}



e_cccerror	Socket_SetNonBlocking(t_socket sock, t_bool nonblocking)
{
#if (defined(_WIN32) && !defined(__CYGWIN__))
	u_long	mode = (nonblocking ? 1 : 0);
	int	result = ioctlsocket(sock, FIONBIO, &mode);
	__Socket_UpdateErrno();
	if CCCERROR((result != 0), ERROR_SYSTEM,
		"could not change blocking mode of socket %zi", (t_size)sock)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
#else
	int	flags = fcntl(sock, F_GETFL, 0);
	if CCCERROR((flags < 0), ERROR_SYSTEM,
		"could not get flags of socket %zi", (t_size)sock)
		return (ERROR_SYSTEM);
	if (nonblocking)
		flags |= O_NONBLOCK;
	else
		flags &= ~O_NONBLOCK;
	if CCCERROR((fcntl(sock, F_SETFL, flags) < 0), ERROR_SYSTEM,
		"could not change blocking mode of socket %zi", (t_size)sock)
		return (ERROR_SYSTEM);
	return (ERROR_NONE);
#endif
}
