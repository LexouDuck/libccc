/*============================================================================*\
||                                            ______________________________  ||
||  libccc/sys/socket.h                      |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_SYS_SOCKET_H
#define __LIBCCC_SYS_SOCKET_H
/*!@group{libccc_sys_socket,23,libccc/sys/socket.h}
**
**	This header defines a portable API for network sockets (send/recv, etc).
**
**	The functions in this header are, for the most part, simple wrappers over
**	the platform's BSD-style socket API (WinSock2 on Windows, `<sys/socket.h>`
**	on POSIX platforms), with a few key differences which make them easier
**	and safer to use:
**	- All socket addresses are stored in a single, portable #s_sockaddr struct,
**	  (rather than the messy `sockaddr`/`sockaddr_in`/`sockaddr_in6`/`sockaddr_storage`
**	  struct-casting shenanigans that the BSD sockets API mandates).
**	- All multi-byte values (like the `port` number) are stored in host byte
**	  order within libccc structs: the conversion to/from network byte order
**	  (big-endian) is handled internally by the libccc functions themselves.
**	- Enums are used for the address family/socket type/protocol arguments,
**	  so as to not expose any platform-specific `AF_*`/`SOCK_*`/`IPPROTO_*`
**	  macro values in calling code.
**	- On Windows, the WinSock2 DLL requires initialization: this is handled
**	  transparently via Socket_Init()/Socket_Exit(), which are no-ops on
**	  other platforms (so you can call them unconditionally, in portable code).
**
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_socket.h.html}
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_SYS_SOCKET_T
#define __LIBCCC_SYS_SOCKET_T

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//!@doc The type used to store a socket handle/descriptor
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/socket.html}
**
**	On POSIX platforms, a socket is simply a file descriptor (a small `int`).
**	On Windows, a `SOCKET` is an unsigned pointer-sized integer (`UINT_PTR`).
**	This typedef abstracts away that difference: you should only ever compare
**	a #t_socket value against #SOCKET_INVALID, rather than checking `(sock < 0)`.
*/
//!@{
#if (defined(_WIN32) && !defined(__CYGWIN__))
typedef t_uintptr	t_socket;
#else
typedef int			t_socket;
#endif
TYPEDEF_ALIAS(		t_socket, SOCKET, PRIMITIVE)
//!@}

//!@doc The value which represents an invalid (or not-yet-created) socket
//!@{
#if (defined(_WIN32) && !defined(__CYGWIN__))
#define SOCKET_INVALID	((t_socket)~0)	//!< equivalent to winsock2's `INVALID_SOCKET`
#else
#define SOCKET_INVALID	((t_socket)-1)	//!< the standard `-1` error value for POSIX file descriptors
#endif
//!@}

//!@doc The type used to store a network port number
/*!
**	NB: libccc functions always take/return port numbers in host byte order:
**	the conversion to/from network byte order (big-endian) is done internally.
*/
//!@{
typedef t_u16	t_port;
TYPEDEF_ALIAS(	t_port, SOCKET_PORT, PRIMITIVE)
//!@}

//!@doc Special port number value: lets the OS choose any available ephemeral port
#define PORT_ANY	((t_port)0)



//!@doc This enum represents a socket address family (ie: the network layer protocol)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_socket.h.html}
**
**	These values are portable equivalents of the platform `AF_*` macros.
*/
//!@{
typedef enum sockaf
{
	SOCKAF_UNSPEC = 0,	//!< (`AF_UNSPEC`) Unspecified address family
	SOCKAF_LOCAL,		//!< (`AF_UNIX`/`AF_LOCAL`) Local (UNIX domain) socket, for same-machine IPC (NB: #s_sockaddr cannot yet store a UNIX socket filepath — TODO)
	SOCKAF_IPV4,		//!< (`AF_INET`)  Internet Protocol version 4 address family
	SOCKAF_IPV6,		//!< (`AF_INET6`) Internet Protocol version 6 address family
	ENUMLENGTH_SOCKAF
}	e_sockaf;
TYPEDEF_ALIAS(e_sockaf, SOCKET_ADDRESSFAMILY, ENUM)
//!@}

//!@doc This enum represents a socket type (ie: the transport semantics)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_socket.h.html}
**
**	These values are portable equivalents of the platform `SOCK_*` macros.
*/
//!@{
typedef enum socktype
{
	SOCKTYPE_STREAM = 0,	//!< (`SOCK_STREAM`) Connection-oriented, reliable, ordered byte stream (this is what TCP uses)
	SOCKTYPE_DGRAM,			//!< (`SOCK_DGRAM`)  Connectionless, unreliable datagrams of fixed maximum length (this is what UDP uses)
	SOCKTYPE_RAW,			//!< (`SOCK_RAW`)    Raw network protocol access (usually requires elevated privileges)
	ENUMLENGTH_SOCKTYPE
}	e_socktype;
TYPEDEF_ALIAS(e_socktype, SOCKET_TYPE, ENUM)
//!@}

//!@doc This enum represents a transport layer protocol, for the Socket_New() function
/*!
**	These values are portable equivalents of the platform `IPPROTO_*` macros.
*/
//!@{
typedef enum sockproto
{
	SOCKPROTO_DEFAULT = 0,	//!< Use the default protocol for the given socket type (TCP for #SOCKTYPE_STREAM, UDP for #SOCKTYPE_DGRAM)
	SOCKPROTO_TCP,			//!< (`IPPROTO_TCP`) Transmission Control Protocol
	SOCKPROTO_UDP,			//!< (`IPPROTO_UDP`) User Datagram Protocol
	ENUMLENGTH_SOCKPROTO
}	e_sockproto;
TYPEDEF_ALIAS(e_sockproto, SOCKET_PROTOCOL, ENUM)
//!@}

//!@doc This enum represents which directions of transmission to shut down, for the Socket_Shutdown() function
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/shutdown.html}
**
**	These values are portable equivalents of the platform `SHUT_*`/`SD_*` macros.
*/
//!@{
typedef enum sockshutdown
{
	SOCKSHUTDOWN_RECV = 0,	//!< (`SHUT_RD`)   Disable further receive operations on the socket
	SOCKSHUTDOWN_SEND,		//!< (`SHUT_WR`)   Disable further send operations on the socket
	SOCKSHUTDOWN_BOTH,		//!< (`SHUT_RDWR`) Disable further send and receive operations
	ENUMLENGTH_SOCKSHUTDOWN
}	e_sockshutdown;
TYPEDEF_ALIAS(e_sockshutdown, SOCKET_SHUTDOWN, ENUM)
//!@}

//!@doc This enum represents a socket option, for the Socket_SetOption_Bool() function
/*!
**	These values are portable equivalents of the platform `SO_*`/`TCP_*` macros.
*/
//!@{
typedef enum sockopt
{
	SOCKOPT_REUSEADDR = 0,	//!< (`SO_REUSEADDR`) Allow reusing a local address which is in `TIME_WAIT` state (you almost always want this for a server's listening socket)
	SOCKOPT_KEEPALIVE,		//!< (`SO_KEEPALIVE`) Periodically probe an idle connection, to check whether the peer is still reachable
	SOCKOPT_BROADCAST,		//!< (`SO_BROADCAST`) Allow sending datagrams to a broadcast address (only meaningful for #SOCKTYPE_DGRAM sockets)
	SOCKOPT_NODELAY,		//!< (`TCP_NODELAY`)  Disable Nagle's algorithm: send small packets immediately, rather than coalescing them (only meaningful for TCP sockets)
	ENUMLENGTH_SOCKOPT
}	e_sockopt;
TYPEDEF_ALIAS(e_sockopt, SOCKET_OPTION, ENUM)
//!@}



//!@doc This type represents the bitflag value which holds options for the Socket_Send()/Socket_Recv() functions
//!@{
typedef t_uint	t_sockmsg;
TYPEDEF_ALIAS(	t_sockmsg, SOCKET_MSGFLAGS, PRIMITIVE)
//!@}

//!@doc Option bitflags for the send/recv function family, used with the `t_sockmsg` type
/*!
**	These values are portable equivalents of the platform `MSG_*` macros
**	(they are converted to the appropriate platform-specific values internally,
**	and can be combined together with the bitwise OR `|` operator, as usual).
*/
//!@{
#define SOCKMSG_NONE		(0)			//!< The default behavior (no option flags set)
#define SOCKMSG_PEEK		(1 << 0)	//!< (`MSG_PEEK`)     Peek at the incoming data without removing it from the receive queue
#define SOCKMSG_OUTOFBAND	(1 << 1)	//!< (`MSG_OOB`)      Send/receive out-of-band data (ie: TCP urgent data)
#define SOCKMSG_WAITALL		(1 << 2)	//!< (`MSG_WAITALL`)  Block a recv operation until the full requested amount of data is received
#define SOCKMSG_DONTWAIT	(1 << 3)	//!< (`MSG_DONTWAIT`) Perform this one operation in non-blocking mode (not supported on Windows: use Socket_SetNonBlocking() instead)
//!@}



//!@doc This struct is used to store any kind of socket address, in a portable manner
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/netinet_in.h.html}
**
**	This struct replaces the standard sockets API's `sockaddr`/`sockaddr_in`/
**	`sockaddr_in6`/`sockaddr_storage` structs (and the pointer-casting between
**	them that the standard API requires). The `.ip` bytes are always stored in
**	network byte order (ie: as they would appear when written out as text),
**	whereas the `.port` number is stored in host byte order, for convenience.
*/
//!@{
typedef struct sockaddr_ipc
{
	e_sockaf	family;		//!< The address family of this address (#SOCKAF_IPV4, #SOCKAF_IPV6, etc)
	t_port		port;		//!< The port number (in host byte order, ie: `80` really means port 80)
	union
	{
		t_u8	ipv4[4];	//!< IPv4 address bytes (if `family` is #SOCKAF_IPV4), ie: `{127,0,0,1}` for localhost
		t_u8	ipv6[16];	//!< IPv6 address bytes (if `family` is #SOCKAF_IPV6), in network byte order
	}	ip;					//!< The IP address bytes themselves
}	s_sockaddr;
TYPEDEF_ALIAS(s_sockaddr, SOCKET_ADDRESS, STRUCT)
//!@}

//!@doc The default/null value for a #s_sockaddr struct (all fields set to zero)
#define SOCKADDR_NULL	((s_sockaddr){ .family = SOCKAF_UNSPEC, .port = 0, .ip = {{0}} })

//! The minimum buffer size needed to hold any address string made by SockAddr_ToString_Buf() (with port suffix and null terminator)
#define SOCKADDR_STRING_MAXLENGTH	64



#endif
#ifndef __LIBCCC_SYS_SOCKET_F
#define __LIBCCC_SYS_SOCKET_F

/*============================================================================*\
||                          Socket Library Lifecycle                          ||
\*============================================================================*/

//!@doc Initializes the platform's socket library (needed on Windows: WSAStartup)
/*!
**	@nonstd
**
**	On Windows, this calls `WSAStartup()`, which is required before using any
**	socket functions. On every other platform, this function does nothing.
**	This function can safely be called several times (subsequent calls are no-ops).
**	You should call this once at program startup, in portable code.
**
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code
*/
//!@{
e_cccerror				Socket_Init(void);
#define c_sockinit		Socket_Init
//!@}

//!@doc Cleans up the platform's socket library (needed on Windows: WSACleanup)
/*!
**	@nonstd
**
**	On Windows, this calls `WSACleanup()`. On every other platform, this
**	function does nothing. You should call this once at program exit.
**
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code
*/
//!@{
e_cccerror				Socket_Exit(void);
#define c_sockexit		Socket_Exit
//!@}



/*============================================================================*\
||                          Socket Creation/Deletion                          ||
\*============================================================================*/

//!@doc Creates a new socket with the given address `family`, socket `type`, and `protocol`
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/socket.html}
**
**	@param	family		The address family for the new socket (#SOCKAF_IPV4, #SOCKAF_IPV6, etc)
**	@param	type		The type of socket to create (#SOCKTYPE_STREAM for TCP, #SOCKTYPE_DGRAM for UDP)
**	@param	protocol	The transport protocol to use (you can just pass #SOCKPROTO_DEFAULT)
**	@returns
**	The newly created socket handle,
**	or #SOCKET_INVALID if there was an error while attempting to create the socket
*/
//!@{
t_socket				Socket_New(e_sockaf family, e_socktype type, e_sockproto protocol);
#define c_socknew		Socket_New
#define c_socket		Socket_New
//!@}

//!@doc Closes the given socket `sock`, so that it no longer refers to any connection, and may be reused
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/close.html}
**
**	@param	sock	The socket to close
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror				Socket_Close(t_socket sock);
#define c_sockclose		Socket_Close
//!@}

//!@doc Shuts down all or part of a full-duplex connection on the given socket `sock`
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/shutdown.html}
**
**	Unlike Socket_Close(), this does not free the socket handle itself: it only
**	signals the end of transmission (a TCP `FIN`), in the given direction(s).
**	A typical use is `Socket_Shutdown(sock, SOCKSHUTDOWN_SEND)` to tell the
**	peer that you are done sending, while still being able to receive their reply.
**
**	@param	sock	The socket whose connection should be shut down
**	@param	how		Which direction(s) of transmission to shut down
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror				Socket_Shutdown(t_socket sock, e_sockshutdown how);
#define c_sockshutdown	Socket_Shutdown
//!@}



/*============================================================================*\
||                        Connection-related Functions                        ||
\*============================================================================*/

//!@doc Binds the given socket `sock` to the given local address `addr`
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/bind.html}
**
**	This assigns a local address (IP and port) to a socket: this is typically
**	done for a server socket, before calling Socket_Listen().
**	To bind to all available network interfaces, use SockAddr_Any().
**
**	@param	sock	The socket to bind
**	@param	addr	The local address to bind the socket to
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror				Socket_Bind(t_socket sock, s_sockaddr const* addr);
#define c_sockbind		Socket_Bind
//!@}

//!@doc Marks the given socket `sock` as a passive socket, which will accept incoming connections
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/listen.html}
**
**	@param	sock	The socket to mark as listening (must be bound, see Socket_Bind())
**	@param	backlog	The maximum amount of pending connections to queue up (a typical value is `16`; if `0`, a reasonable platform default is used)
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror				Socket_Listen(t_socket sock, t_uint backlog);
#define c_socklisten	Socket_Listen
//!@}

//!@doc Accepts an incoming connection on the given listening socket `sock`
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/accept.html}
**
**	This function blocks until an incoming connection arrives (unless the
**	socket was set to non-blocking mode, see Socket_SetNonBlocking()).
**
**	@param	sock		The listening socket (see Socket_Listen()) on which to accept a connection
**	@param	dest_addr	If non-NULL, this address struct is filled with the address of the connecting peer
**	@returns
**	The newly created socket handle for the accepted connection,
**	or #SOCKET_INVALID if there was an error while attempting to accept
*/
//!@{
t_socket				Socket_Accept(t_socket sock, s_sockaddr* dest_addr);
#define c_sockaccept	Socket_Accept
//!@}

//!@doc Connects the given socket `sock` to the given remote address `addr`
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/connect.html}
**
**	For a #SOCKTYPE_STREAM socket, this performs the connection handshake with
**	the remote host. For a #SOCKTYPE_DGRAM socket, this simply sets the default
**	destination address for subsequent Socket_Send() calls.
**
**	@param	sock	The socket to connect
**	@param	addr	The remote address to connect to
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror				Socket_Connect(t_socket sock, s_sockaddr const* addr);
#define c_sockconnect	Socket_Connect
//!@}



//!@doc Gets the local address to which the given socket `sock` is currently bound
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/getsockname.html}
**
**	This is especially useful after binding to #PORT_ANY, to find out which
**	ephemeral port number the operating system actually assigned to the socket.
**
**	@param	dest_addr	The address struct to fill with the socket's local address
**	@param	sock		The socket whose local address should be queried
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror				Socket_GetAddress(s_sockaddr* dest_addr, t_socket sock);
#define c_sockgetaddr	Socket_GetAddress
//!@}

//!@doc Gets the address of the peer to which the given socket `sock` is connected
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/getpeername.html}
**
**	@param	dest_addr	The address struct to fill with the peer's address
**	@param	sock		The (connected) socket whose peer address should be queried
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror				Socket_GetPeerAddress(s_sockaddr* dest_addr, t_socket sock);
#define c_sockgetpeer	Socket_GetPeerAddress
//!@}



/*============================================================================*\
||                              Sending Functions                             ||
\*============================================================================*/

//!@doc Sends `n` bytes of the given `data` buffer through the given socket `sock`
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/send.html}
**
**	NB: like the underlying `send()` call, this function may send fewer bytes
**	than requested (a "partial send"): check the return value, or use
**	Socket_Send_All() if you want a function which loops until everything is sent.
**
**	@param	sock	The (connected) socket through which to send data
**	@param	data	The buffer of data to send
**	@param	n		The amount of bytes to send from `data`
**	@param	flags	Option flags for this operation (bitflag, can be bitwise OR'd, ie: `(SOCKMSG_OUTOFBAND|SOCKMSG_DONTWAIT)`), or #SOCKMSG_NONE
**	@returns
**	The amount of bytes which were actually sent.
**	If the return value is a negative number, there was a send error:
**	You should then check `errno`, and/or use `Error_STD_Get()` immediately after.
*/
//!@{
t_sintmax				Socket_Send(t_socket sock, void const* data, t_size n, t_sockmsg flags);
#define c_socksend		Socket_Send
#define c_send			Socket_Send
//!@}

//!@doc Sends the full `n` bytes of the given `data` buffer through the given socket `sock`, looping if necessary
/*!
**	@nonstd
**
**	Unlike Socket_Send(), this function will loop over the underlying `send()`
**	call until every last byte has been sent (or until an error occurs).
**
**	@param	sock	The (connected) socket through which to send data
**	@param	data	The buffer of data to send
**	@param	n		The amount of bytes to send from `data`
**	@returns
**	`0`(#OK) if all `n` bytes were sent successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror				Socket_Send_All(t_socket sock, void const* data, t_size n);
#define c_socksendall	Socket_Send_All
//!@}

//!@doc Sends the given string `str` through the given socket `sock` (in full, looping if necessary)
/*!
**	@nonstd
**
**	@param	sock	The (connected) socket through which to send data
**	@param	str		The null-terminated string to send (the null terminator itself is not sent)
**	@returns
**	`0`(#OK) if the whole string was sent successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror				Socket_Send_String(t_socket sock, t_char const* str);
#define c_socksendstr	Socket_Send_String
//!@}

//!@doc Sends `n` bytes of the given `data` buffer to the given address `addr`, through the socket `sock`
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/sendto.html}
**
**	This is the function to use for connectionless (#SOCKTYPE_DGRAM, ie: UDP)
**	sockets, where each datagram can be sent to a different destination address.
**
**	@param	sock	The socket through which to send data
**	@param	data	The buffer of data to send
**	@param	n		The amount of bytes to send from `data`
**	@param	flags	Option flags for this operation (bitflag, can be bitwise OR'd), or #SOCKMSG_NONE
**	@param	addr	The destination address to send this data to
**	@returns
**	The amount of bytes which were actually sent.
**	If the return value is a negative number, there was a send error:
**	You should then check `errno`, and/or use `Error_STD_Get()` immediately after.
*/
//!@{
t_sintmax				Socket_SendTo(t_socket sock, void const* data, t_size n, t_sockmsg flags, s_sockaddr const* addr);
#define c_socksendto	Socket_SendTo
#define c_sendto		Socket_SendTo
//!@}



/*============================================================================*\
||                             Receiving Functions                            ||
\*============================================================================*/

//!@doc Receives up to `n` bytes of data from the given socket `sock`, into the given `buffer`
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/recv.html}
**
**	This function blocks until at least some data arrives (unless the socket
**	was set to non-blocking mode, see Socket_SetNonBlocking()).
**
**	@param	sock	The (connected) socket from which to receive data
**	@param	buffer	The buffer to fill with the received data
**	@param	n		The maximum amount of bytes to receive (ie: the size of `buffer`)
**	@param	flags	Option flags for this operation (bitflag, can be bitwise OR'd, ie: `(SOCKMSG_PEEK|SOCKMSG_DONTWAIT)`), or #SOCKMSG_NONE
**	@returns
**	The amount of bytes which were actually received.
**	A return value of `0` means the peer has performed an orderly shutdown
**	(ie: the connection was closed).
**	If the return value is a negative number, there was a receive error:
**	You should then check `errno`, and/or use `Error_STD_Get()` immediately after.
*/
//!@{
t_sintmax				Socket_Recv(t_socket sock, void* buffer, t_size n, t_sockmsg flags);
#define c_sockrecv		Socket_Recv
#define c_recv			Socket_Recv
//!@}

//!@doc Receives exactly `n` bytes of data from the given socket `sock`, looping if necessary
/*!
**	@nonstd
**
**	Unlike Socket_Recv(), this function will loop over the underlying `recv()`
**	call until exactly `n` bytes have been received (or until an error occurs,
**	or the connection is closed by the peer).
**
**	@param	sock	The (connected) socket from which to receive data
**	@param	buffer	The buffer to fill with the received data (must be at least `n` bytes large)
**	@param	n		The exact amount of bytes to receive
**	@returns
**	The amount of bytes which were actually received: this will be equal to `n`,
**	unless the connection was closed by the peer before `n` bytes could be read
**	(in which case the amount of bytes read before closing is returned).
**	If the return value is a negative number, there was a receive error:
**	You should then check `errno`, and/or use `Error_STD_Get()` immediately after.
*/
//!@{
t_sintmax				Socket_Recv_All(t_socket sock, void* buffer, t_size n);
#define c_sockrecvall	Socket_Recv_All
//!@}

//!@doc Receives up to `n` bytes of data from the socket `sock`, also getting the sender's address
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/recvfrom.html}
**
**	This is the function to use for connectionless (#SOCKTYPE_DGRAM, ie: UDP)
**	sockets, where you typically need to know which peer sent each datagram.
**
**	@param	sock		The socket from which to receive data
**	@param	buffer		The buffer to fill with the received data
**	@param	n			The maximum amount of bytes to receive (ie: the size of `buffer`)
**	@param	flags		Option flags for this operation (bitflag, can be bitwise OR'd), or #SOCKMSG_NONE
**	@param	dest_addr	If non-NULL, this address struct is filled with the address of the sending peer
**	@returns
**	The amount of bytes which were actually received.
**	If the return value is a negative number, there was a receive error:
**	You should then check `errno`, and/or use `Error_STD_Get()` immediately after.
*/
//!@{
t_sintmax				Socket_RecvFrom(t_socket sock, void* buffer, t_size n, t_sockmsg flags, s_sockaddr* dest_addr);
#define c_sockrecvfrom	Socket_RecvFrom
#define c_recvfrom		Socket_RecvFrom
//!@}



/*============================================================================*\
||                               Socket Options                               ||
\*============================================================================*/

//!@doc Sets the given boolean socket `option` to the given `value`, for the given socket `sock`
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/setsockopt.html}
**
**	@param	sock	The socket whose option should be set
**	@param	option	The option to set (see the #e_sockopt enum)
**	@param	value	The new value to set for this option (`TRUE` to enable, `FALSE` to disable)
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror				Socket_SetOption_Bool(t_socket sock, e_sockopt option, t_bool value);
#define c_sockoptset	Socket_SetOption_Bool
//!@}

//!@doc Gets the current value of the given boolean socket `option`, for the given socket `sock`
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/getsockopt.html}
**
**	@param	sock	The socket whose option should be queried
**	@param	option	The option to get (see the #e_sockopt enum)
**	@returns
**	`TRUE` if the given option is currently enabled for this socket, otherwise `FALSE`
**	(also returns `FALSE` if there was an error while querying the option)
*/
//!@{
t_bool					Socket_GetOption_Bool(t_socket sock, e_sockopt option);
#define c_sockoptget	Socket_GetOption_Bool
//!@}

//!@doc Sets the given socket `sock` to blocking or non-blocking mode
/*!
**	@nonstd
**
**	When a socket is in non-blocking mode, operations which would normally
**	block (like Socket_Recv() or Socket_Accept()) will instead return
**	immediately with an error (`EWOULDBLOCK`/`EAGAIN`) if they cannot proceed.
**
**	@param	sock		The socket whose blocking mode should be changed
**	@param	nonblocking	If `TRUE`, set the socket to non-blocking mode; if `FALSE`, set it to (the default) blocking mode
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
//!@{
e_cccerror					Socket_SetNonBlocking(t_socket sock, t_bool nonblocking);
#define c_socknonblock		Socket_SetNonBlocking
//!@}



/*============================================================================*\
||                          Socket Address Functions                          ||
\*============================================================================*/

//!@doc Creates a socket address struct from the given IP address string `ip` and port number `port`
/*!
**	@nonstd
**
**	The address family (IPv4 or IPv6) is deduced from the contents of the `ip`
**	string itself. If `ip` is `NULL`, an IPv4 "any" wildcard address is returned
**	(equivalent to `SockAddr_Any(SOCKAF_IPV4, port)`).
**
**	@param	ip		The IP address, as a string (ie: `"127.0.0.1"`, or `"::1"`)
**	@param	port	The port number (in host byte order, ie: just write `80` for port 80)
**	@returns
**	The newly filled socket address struct.
**	If the `ip` string could not be parsed, the resulting struct will have its
**	`.family` field set to #SOCKAF_UNSPEC (and an #ERROR_PARSE error is raised).
*/
//!@{
s_sockaddr				SockAddr_New(t_char const* ip, t_port port);
#define c_sockaddrnew	SockAddr_New
//!@}

//!@doc Creates a "wildcard" socket address, which binds to all available network interfaces
/*!
**	@nonstd
**
**	This is the address you typically want to give to Socket_Bind(), for a
**	server which should accept connections on any of the machine's addresses
**	(this is the equivalent of the standard `INADDR_ANY`/`in6addr_any` values).
**
**	@param	family	The address family for the address (#SOCKAF_IPV4 or #SOCKAF_IPV6)
**	@param	port	The port number (in host byte order)
**	@returns
**	The newly filled socket address struct.
*/
//!@{
s_sockaddr				SockAddr_Any(e_sockaf family, t_port port);
#define c_sockaddrany	SockAddr_Any
//!@}

//!@doc Creates a "loopback" (localhost) socket address
/*!
**	@nonstd
**
**	@param	family	The address family for the address (#SOCKAF_IPV4 gives `127.0.0.1`, #SOCKAF_IPV6 gives `::1`)
**	@param	port	The port number (in host byte order)
**	@returns
**	The newly filled socket address struct.
*/
//!@{
s_sockaddr					SockAddr_LocalHost(e_sockaf family, t_port port);
#define c_sockaddrlocal		SockAddr_LocalHost
//!@}

//!@doc Parses the given IP address string `str`, filling the given address struct `dest`
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/inet_ntop.html}
**
**	Accepts both IPv4 dotted-decimal notation (ie: `"192.168.0.1"`),
**	and IPv6 hexadecimal colon notation (ie: `"2001:db8::1"`).
**	NB: this function does not perform any DNS hostname resolution
**	(that is to be the role of `libccc/sys/network.h`).
**
**	@param	dest	The address struct to fill (only the `.family` and `.ip` fields are written; `.port` is left untouched)
**	@param	str		The IP address string to parse
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: #ERROR_PARSE if the string is not a valid IP address)
*/
//!@{
e_cccerror				SockAddr_Parse(s_sockaddr* dest, t_char const* str);
#define c_sockaddrparse	SockAddr_Parse
//!@}

//!@doc Writes the given socket address `addr` as a string, into the given buffer `dest`
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/inet_ntop.html}
**
**	The output format is `"192.168.0.1:80"` for IPv4, and `"[2001:db8::1]:80"`
**	for IPv6 (the port suffix is omitted if the address' `.port` is #PORT_ANY).
**
**	@param	dest		The buffer in which to write the address string
**	@param	addr		The socket address to convert to a string
**	@param	max_length	The size of the `dest` buffer (should be at least #SOCKADDR_STRING_MAXLENGTH)
**	@returns
**	The amount of characters written to `dest` (not counting the null terminator),
**	or `0` if there was an error (invalid address, or buffer too small).
*/
//!@{
t_size						SockAddr_ToString_Buf(t_char* dest, s_sockaddr const* addr, t_size max_length);
#define c_sockaddrtostrbuf	SockAddr_ToString_Buf
//!@}

//!@doc Allocates and returns a string representation of the given socket address `addr`
/*!
**	@nonstd
**
**	The output format is `"192.168.0.1:80"` for IPv4, and `"[2001:db8::1]:80"`
**	for IPv6 (the port suffix is omitted if the address' `.port` is #PORT_ANY).
**
**	@param	addr	The socket address to convert to a string
**	@returns
**	A newly allocated string representation of the given address,
**	or `NULL` if there was an error.
*/
//!@{
_MALLOC()
t_char*					SockAddr_ToString(s_sockaddr const* addr);
#define c_sockaddrtostr	SockAddr_ToString
//!@}

//!@doc Checks whether the two given socket addresses are equal
/*!
**	@nonstd
**
**	@param	addr1	The first address to compare
**	@param	addr2	The second address to compare
**	@returns
**	`TRUE` if the two addresses have the same family, IP address and port,
**	otherwise `FALSE`.
*/
//!@{
t_bool					SockAddr_Equals(s_sockaddr const* addr1, s_sockaddr const* addr2);
#define c_sockaddrequ	SockAddr_Equals
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
