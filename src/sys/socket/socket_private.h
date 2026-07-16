/*============================================================================*\
||                                            ______________________________  ||
||  src/sys/socket/socket_private.h          |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_SYS_SOCKET_PRIVATE_H
#define __LIBCCC_SYS_SOCKET_PRIVATE_H

/*
**	This private header is shared by the source files of `libccc/sys/socket.h`:
**	it holds the platform-specific includes, and the declarations for the
**	internal helper functions which convert between libccc's portable
**	socket enums/structs and the platform's native equivalents.
*/

#include "libccc.h"
#include "libccc/sys/socket.h"

#ifndef __NOSTD__
	#if (defined(_WIN32) && !defined(__CYGWIN__))
		#include <winsock2.h>
		#include <ws2tcpip.h>
		typedef int	socklen_t;
	#else
		#include <sys/types.h>
		#include <sys/socket.h>
		#include <netinet/in.h>
		#include <netinet/tcp.h>
		#include <arpa/inet.h>
		#include <unistd.h>
		#include <fcntl.h>
	#endif
	#include <errno.h>
#endif



/*
**	This macro holds the platform-appropriate expression to check whether
**	the result of a native socket-creating call (socket()/accept()) failed.
*/
#if (defined(_WIN32) && !defined(__CYGWIN__))
	#define SOCKET_NATIVE_FAILED(SOCK)	((SOCK) == SOCKET_INVALID)
#else
	#define SOCKET_NATIVE_FAILED(SOCK)	((SOCK) < 0)
#endif



//! Updates `errno` from the platform's socket error state (WSAGetLastError() on win32, no-op elsewhere)
void		__Socket_UpdateErrno(void);
//! Checks whether the current `errno` value indicates a non-blocking operation which would have blocked (`EWOULDBLOCK`/`EAGAIN`/`WSAEWOULDBLOCK`)
t_bool		__Socket_IsErrorWouldBlock(void);
//! Checks whether the current `errno` value indicates a non-blocking connect operation which is still in progress (`EINPROGRESS`/`WSAEWOULDBLOCK`)
t_bool		__Socket_IsErrorInProgress(void);

//! Converts a portable #e_sockaf value to the platform's native `AF_*` value (returns `-1` if invalid)
int			__Socket_NativeAF(e_sockaf family);
//! Converts a platform-native `AF_*` value to the portable #e_sockaf equivalent (returns #SOCKAF_UNSPEC if unknown)
e_sockaf	__Socket_FromNativeAF(int native_family);
//! Converts a portable #e_socktype value to the platform's native `SOCK_*` value (returns `-1` if invalid)
int			__Socket_NativeType(e_socktype type);
//! Converts a portable #e_sockproto value to the platform's native `IPPROTO_*` value (returns `-1` if invalid)
int			__Socket_NativeProto(e_sockproto protocol);
//! Converts a portable #t_sockmsg bitflag value to the platform's native `MSG_*` bitflag equivalent
int			__Socket_NativeMsgFlags(t_sockmsg flags);

//! Fills a native `sockaddr_storage` struct from the given portable address; returns the native address length, or `0` if invalid
socklen_t	__SockAddr_ToNative(struct sockaddr_storage* dest, s_sockaddr const* addr);
//! Fills a portable #s_sockaddr struct from the given native address; returns `0`(#OK), or a non-zero error code
e_cccerror	__SockAddr_FromNative(s_sockaddr* dest, struct sockaddr_storage const* src);



#endif
