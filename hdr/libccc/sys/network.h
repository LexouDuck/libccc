/*============================================================================*\
||                                            ______________________________  ||
||  libccc/sys/network.h                     |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_SYS_NETWORK_H
#define __LIBCCC_SYS_NETWORK_H
/*!@group{libccc_sys_network,24,libccc/sys/network.h}
**
**	This header defines high-level utility functions for common network
**	protocols (TCP/IP and UDP), built on top of `libccc/sys/socket.h`.
**
**	Whereas `libccc/sys/socket.h` offers thin, portable wrappers over each
**	individual BSD socket call, this header offers the functions you actually
**	want to call in typical application code:
**	- DNS hostname resolution (Network_Resolve(): a sane `getaddrinfo()` wrapper)
**	- one-call TCP client connection setup (TCP_Connect())
**	- one-call TCP server socket setup (TCP_Listen()), and a simple
**	  accept-loop helper (TCP_Serve()) for callback-based servers
**	- one-call UDP socket setup (UDP_New()), with hostname-resolving
**	  send/receive convenience functions (UDP_SendTo()/UDP_RecvFrom())
**	- endianness-safe byte order conversion functions (which work regardless
**	  of the host machine's endianness, without any platform detection macros)
**
**	NB: as with `libccc/sys/socket.h`, remember to call Socket_Init() once at
**	program startup (this is required on Windows, and harmless elsewhere).
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"
#include "libccc/sys/socket.h"

HEADER_CPP

#ifndef __LIBCCC_SYS_NETWORK_T
#define __LIBCCC_SYS_NETWORK_T

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//!@doc This function pointer type is a connection handler, for the TCP_Serve() accept loop
/*!
**	@param	client	The socket for the newly accepted client connection
**					(this socket is closed automatically by TCP_Serve(), after the handler returns)
**	@param	addr	The address of the connecting client
**	@param	context	The custom user-data pointer which was given to TCP_Serve()
**	@returns
**	`TRUE` if the server should keep running (ie: accept the next connection),
**	or `FALSE` if the server should stop (making TCP_Serve() return).
*/
//!@{
typedef t_bool	(*f_tcp_handler)(t_socket client, s_sockaddr const* addr, void* context);
//!@}

//! The maximum length for a hostname string filled by Network_GetHostName() (as per RFC 1035)
#define NETWORK_HOSTNAME_MAXLENGTH	256



#endif
#ifndef __LIBCCC_SYS_NETWORK_F
#define __LIBCCC_SYS_NETWORK_F

/*============================================================================*\
||                        Byte Order (Endianness) Functions                   ||
\*============================================================================*/

//!@doc Converts a 16-bit integer from host byte order to network byte order (big-endian)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/htons.html}
**
**	NB: unlike the standard `htons()`, this function is implemented in a fully
**	endianness-agnostic manner (it works on any machine, without any need for
**	platform/endianness detection macros).
*/
//!@{
t_u16				Network_HostToNet_U16(t_u16 value);
#define c_htons		Network_HostToNet_U16
//!@}

//!@doc Converts a 32-bit integer from host byte order to network byte order (big-endian)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/htonl.html}
*/
//!@{
t_u32				Network_HostToNet_U32(t_u32 value);
#define c_htonl		Network_HostToNet_U32
//!@}

//!@doc Converts a 64-bit integer from host byte order to network byte order (big-endian)
/*!
**	@nonstd
*/
//!@{
t_u64				Network_HostToNet_U64(t_u64 value);
#define c_htonll	Network_HostToNet_U64
//!@}

//!@doc Converts a 16-bit integer from network byte order (big-endian) to host byte order
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/ntohs.html}
*/
//!@{
t_u16				Network_NetToHost_U16(t_u16 value);
#define c_ntohs		Network_NetToHost_U16
//!@}

//!@doc Converts a 32-bit integer from network byte order (big-endian) to host byte order
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/ntohl.html}
*/
//!@{
t_u32				Network_NetToHost_U32(t_u32 value);
#define c_ntohl		Network_NetToHost_U32
//!@}

//!@doc Converts a 64-bit integer from network byte order (big-endian) to host byte order
/*!
**	@nonstd
*/
//!@{
t_u64				Network_NetToHost_U64(t_u64 value);
#define c_ntohll	Network_NetToHost_U64
//!@}



/*============================================================================*\
||                        Hostname Resolution Functions                       ||
\*============================================================================*/

//!@doc Resolves the given `host` name to a socket address (performing a DNS lookup, if needed)
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/getaddrinfo.html}
**
**	The `host` string can be a DNS hostname (ie: `"example.com"`), a numeric
**	IPv4 address (ie: `"93.184.216.34"`), or a numeric IPv6 address (ie: `"::1"`).
**	If several addresses exist for the given hostname, the first one returned
**	by the system resolver is used (to get all of them, use Network_Resolve_All()).
**
**	@param	dest	The address struct to fill with the resolved address
**	@param	host	The hostname (or numeric IP address string) to resolve
**	@param	port	The port number to store in the resulting address (in host byte order)
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: #ERROR_NOTFOUND if the hostname could not be resolved)
*/
//!@{
e_cccerror				Network_Resolve(s_sockaddr* dest, t_char const* host, t_port port);
#define c_netresolve	Network_Resolve
//!@}

//!@doc Resolves the given `host` name to the full list of its socket addresses
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/getaddrinfo.html}
**
**	Unlike Network_Resolve(), this function returns every address which the
**	system resolver knows for the given hostname (both IPv4 and IPv6).
**
**	@param	dest_count	If non-NULL, this is set to the amount of addresses in the returned array
**	@param	host		The hostname (or numeric IP address string) to resolve
**	@param	port		The port number to store in each resulting address (in host byte order)
**	@returns
**	A newly allocated array of socket addresses (which must be freed by the caller),
**	or `NULL` if there was an error (ie: the hostname could not be resolved).
*/
//!@{
_MALLOC()
s_sockaddr*				Network_Resolve_All(t_uint* dest_count, t_char const* host, t_port port);
#define c_netresolveall	Network_Resolve_All
//!@}

//!@doc Performs a reverse DNS lookup: gets the hostname for the given socket address `addr`
/*!
**	@isostd{POSIX,https://pubs.opengroup.org/onlinepubs/9699919799/functions/getnameinfo.html}
**
**	@param	addr	The socket address whose hostname should be looked up
**	@returns
**	A newly allocated string holding the hostname for the given address
**	(or its numeric IP address string, if no hostname could be found),
**	or `NULL` if there was an error.
*/
//!@{
_MALLOC()
t_char*					Network_GetHostName(s_sockaddr const* addr);
#define c_nethostname	Network_GetHostName
//!@}



/*============================================================================*\
||                             TCP Client Functions                           ||
\*============================================================================*/

//!@doc Creates a TCP socket, and connects it to the given `host` and `port`
/*!
**	@nonstd
**
**	This is the typical one-call setup function for a TCP client:
**	it resolves the given `host` name (see Network_Resolve_All()), and then
**	attempts to connect to each of the resolved addresses in turn, returning
**	the first successful connection.
**
**	@param	host	The hostname (or numeric IP address string) of the server to connect to
**	@param	port	The port number to connect to (in host byte order)
**	@returns
**	The newly created and connected socket handle,
**	or #SOCKET_INVALID if the connection could not be established
*/
//!@{
t_socket				TCP_Connect(t_char const* host, t_port port);
#define c_tcpconnect	TCP_Connect
//!@}

//!@doc Creates a TCP socket, and connects it to the given socket address `addr`
/*!
**	@nonstd
**
**	Like TCP_Connect(), but for when you already have a resolved #s_sockaddr
**	(so, no hostname resolution is performed).
**
**	@param	addr	The address of the server to connect to
**	@returns
**	The newly created and connected socket handle,
**	or #SOCKET_INVALID if the connection could not be established
*/
//!@{
t_socket					TCP_Connect_Addr(s_sockaddr const* addr);
#define c_tcpconnectaddr	TCP_Connect_Addr
//!@}



/*============================================================================*\
||                             TCP Server Functions                           ||
\*============================================================================*/

//!@doc Creates a TCP server socket, listening on the given socket address `addr`
/*!
**	@nonstd
**
**	This is the typical one-call setup function for a TCP server: it creates
**	a #SOCKTYPE_STREAM socket, sets the #SOCKOPT_REUSEADDR option, binds it
**	to the given address, and marks it as listening.
**	You can then call Socket_Accept() on the resulting socket (or use the
**	TCP_Serve() helper, for a simple callback-based accept loop).
**
**	@param	addr	The local address to listen on (use SockAddr_Any() to listen on all interfaces)
**	@param	backlog	The maximum amount of pending connections to queue up (if `0`, a reasonable default is used)
**	@returns
**	The newly created listening socket handle,
**	or #SOCKET_INVALID if there was an error during setup
*/
//!@{
t_socket				TCP_Listen(s_sockaddr const* addr, t_uint backlog);
#define c_tcplisten		TCP_Listen
//!@}

//!@doc Runs a simple accept loop on the given listening socket `sock`, calling `handle` for each connection
/*!
**	@nonstd
**
**	This function blocks, accepting incoming connections on the given
**	listening socket, one after the other. For each accepted connection,
**	the given `handle` function is called (with the client socket, the
**	client's address, and the given `context` pointer); once the handler
**	returns, the client socket is closed automatically.
**	The loop continues for as long as the handler returns `TRUE`.
**
**	NB: this is a sequential (single-threaded) accept loop, meant for simple
**	servers and tests: connections are handled one at a time, in full.
**
**	@param	sock	The listening socket (see TCP_Listen()) on which to accept connections
**	@param	handle	The handler function to call for each accepted connection
**	@param	context	A custom user-data pointer, passed through to each `handle` call (can be `NULL`)
**	@returns
**	`0`(#OK) if the server loop ended normally (ie: the handler returned `FALSE`),
**	otherwise a non-zero error code (ie: if a call to accept() failed)
*/
//!@{
e_cccerror				TCP_Serve(t_socket sock, f_tcp_handler handle, void* context);
#define c_tcpserve		TCP_Serve
//!@}



/*============================================================================*\
||                                UDP Functions                               ||
\*============================================================================*/

//!@doc Creates a UDP socket, optionally binding it to the given local address `addr`
/*!
**	@nonstd
**
**	This is the typical one-call setup function for UDP:
**	- For a UDP "server" (receiver), pass the local address to bind to
**	  (ie: `UDP_New(&SockAddr_Any(SOCKAF_IPV4, 12345))`-style usage).
**	- For a UDP "client" (sender), you can simply pass `NULL`: the resulting
**	  (IPv4) socket will be bound automatically on the first send operation.
**
**	@param	addr	The local address to bind the socket to (or `NULL`, for an unbound IPv4 socket)
**	@returns
**	The newly created socket handle,
**	or #SOCKET_INVALID if there was an error during setup
*/
//!@{
t_socket				UDP_New(s_sockaddr const* addr);
#define c_udpnew		UDP_New
//!@}

//!@doc Sends `n` bytes of the given `data` buffer as a UDP datagram, to the given `host` and `port`
/*!
**	@nonstd
**
**	Like Socket_SendTo(), except that the destination is given as a hostname
**	string (which is resolved via Network_Resolve()) rather than a #s_sockaddr.
**
**	@param	sock	The (#SOCKTYPE_DGRAM) socket through which to send the datagram
**	@param	data	The buffer of data to send
**	@param	n		The amount of bytes to send from `data`
**	@param	host	The hostname (or numeric IP address string) of the destination
**	@param	port	The destination port number (in host byte order)
**	@returns
**	The amount of bytes which were actually sent.
**	If the return value is a negative number, there was a send error:
**	You should then check `errno`, and/or use `Error_STD_Get()` immediately after.
*/
//!@{
t_sintmax				UDP_SendTo(t_socket sock, void const* data, t_size n, t_char const* host, t_port port);
#define c_udpsendto		UDP_SendTo
//!@}

//!@doc Receives a single UDP datagram of up to `n` bytes from the socket `sock`, into the given `buffer`
/*!
**	@nonstd
**
**	This is a simple convenience alias of Socket_RecvFrom() (with no flags),
**	provided here for API symmetry with UDP_SendTo().
**
**	@param	sock		The (#SOCKTYPE_DGRAM) socket from which to receive a datagram
**	@param	buffer		The buffer to fill with the received data
**	@param	n			The maximum amount of bytes to receive (ie: the size of `buffer`)
**	@param	dest_addr	If non-NULL, this address struct is filled with the address of the sending peer
**	@returns
**	The amount of bytes which were actually received.
**	If the return value is a negative number, there was a receive error:
**	You should then check `errno`, and/or use `Error_STD_Get()` immediately after.
*/
//!@{
t_sintmax				UDP_RecvFrom(t_socket sock, void* buffer, t_size n, s_sockaddr* dest_addr);
#define c_udprecvfrom	UDP_RecvFrom
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
