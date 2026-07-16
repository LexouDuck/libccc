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
**	- DNS hostname resolution (Network_Resolve(): a sane `getaddrinfo()` wrapper,
**	  and Network_Resolve_Async(), which resolves on the event loop's thread pool)
**	- one-call TCP client connection setup (TCP_Connect())
**	- one-call TCP server socket setup (TCP_Listen()), with two accept-loop
**	  helpers for callback-based servers: TCP_Serve() (sequential), and
**	  TCP_Serve_Concurrent() (one thread per connection, via `libccc/sys/thread.h`)
**	- one-call UDP socket setup (UDP_New()), with hostname-resolving
**	  send/receive convenience functions (UDP_SendTo()/UDP_RecvFrom())
**	- fully asynchronous, non-blocking, event-driven networking, built on the
**	  `libccc/sys/async.h` event loop: #s_async_tcp_server, #s_async_tcp,
**	  and #s_async_udp handles (analogous to libuv's `uv_tcp_t`/`uv_udp_t`)
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
#include "libccc/sys/async.h"

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



/*============================================================================*\
||                       Asynchronous Networking: Types                       ||
\*============================================================================*/

/*
**	The following handle types integrate networking with the event loop from
**	`libccc/sys/async.h`, for fully non-blocking, callback-driven networking
**	(analogous to libuv's `uv_tcp_t`/`uv_udp_t`/`uv_getaddrinfo_t`).
**
**	Each of these handle structs embeds its underlying async handle as its
**	FIRST member, and exposes a `data` field for your own custom user data
**	(just like the `data` field of any regular #s_asynchandle).
**	As with all async handles, these structs are user-allocated (typically
**	on the stack, or inside one of your own context structs), and every one
**	of their callbacks is invoked on the event loop thread.
*/

//!@doc An asynchronous DNS resolution request handle, for Network_Resolve_Async()
//!@{
typedef struct async_resolve	s_async_resolve;
TYPEDEF_ALIAS(					s_async_resolve, ASYNC_RESOLVE, STRUCT)
//! The type of callback function invoked when a #s_async_resolve request completes
/*!
**	@param	resolve		The resolution request handle which has completed
**	@param	error		`0`(#ERROR_NONE) if resolution succeeded, otherwise a non-zero error code (ie: #ERROR_NOTFOUND)
**	@param	addresses	The array of resolved addresses (or `NULL`, on error);
**						NOTE: this array is freed automatically after this callback returns,
**						so you must copy any address which you wish to keep
**	@param	amount		The amount of addresses in the `addresses` array
*/
typedef void	(*f_async_resolve)(s_async_resolve* resolve, e_cccerror error, s_sockaddr const* addresses, t_uint amount);
TYPEDEF_ALIAS(	f_async_resolve, ASYNC_RESOLVE_FUNCTION, FUNCTION)
struct async_resolve
{
	s_async_work	work;		//!< [internal] the underlying thread pool work handle (must be the first member)
	void*			data;		//!< [PUBLIC] an opaque user pointer: use it to store any custom contextual data
	f_async_resolve	callback;	//!< [internal] the user callback to invoke upon completion
	t_char*			host;		//!< [internal] the hostname being resolved (duplicated, freed automatically)
	t_port			port;		//!< [internal] the port number to store in each resolved address
	s_sockaddr*		addresses;	//!< [internal] the resolved address array (freed automatically)
	t_uint			amount;		//!< [internal] the amount of resolved addresses
	e_cccerror		error;		//!< [internal] the error code of the resolution operation
};
//!@}



//!@doc An asynchronous TCP server handle: accepts incoming connections via a callback
//!@{
typedef struct async_tcp_server	s_async_tcp_server;
TYPEDEF_ALIAS(					s_async_tcp_server, ASYNC_TCP_SERVER, STRUCT)
//! The type of callback function invoked by a #s_async_tcp_server, for each incoming connection
/*!
**	@param	server	The server handle which accepted this connection
**	@param	client	The newly accepted client socket: you now own this socket
**					(typically, you would wrap it with AsyncTCP_Init() to handle
**					it asynchronously; otherwise, remember to Socket_Close() it)
**	@param	addr	The address of the connecting client
*/
typedef void	(*f_async_tcp_accept)(s_async_tcp_server* server, t_socket client, s_sockaddr const* addr);
TYPEDEF_ALIAS(	f_async_tcp_accept, ASYNC_TCP_ACCEPT_FUNCTION, FUNCTION)
struct async_tcp_server
{
	s_async_poll		poll;		//!< [internal] the underlying I/O poll handle (must be the first member)
	void*				data;		//!< [PUBLIC] an opaque user pointer: use it to store any custom contextual data
	t_socket			socket;		//!< [PUBLIC-read-only] the underlying listening socket
	f_async_tcp_accept	on_accept;	//!< [internal] the user callback to invoke for each incoming connection
};
//!@}



//!@doc An asynchronous TCP connection handle: non-blocking reads/writes via callbacks
//!@{
typedef struct async_tcp	s_async_tcp;
TYPEDEF_ALIAS(				s_async_tcp, ASYNC_TCP, STRUCT)
//! The type of callback function invoked when a #s_async_tcp connection attempt completes (see AsyncTCP_Connect())
/*!
**	@param	conn	The connection handle whose connection attempt has completed
**	@param	error	`0`(#ERROR_NONE) if the connection was established, otherwise a non-zero error code
*/
typedef void	(*f_async_tcp_connect)(s_async_tcp* conn, e_cccerror error);
TYPEDEF_ALIAS(	f_async_tcp_connect, ASYNC_TCP_CONNECT_FUNCTION, FUNCTION)
//! The type of callback function invoked when data arrives on a #s_async_tcp connection (see AsyncTCP_StartRead())
/*!
**	@param	conn	The connection handle on which data arrived
**	@param	buffer	The buffer holding the received bytes (only valid for the duration of this callback: copy it if needed)
**	@param	length	The amount of bytes received; `0` means the peer has closed
**					the connection (EOF), and a negative value means a read error occurred
*/
typedef void	(*f_async_tcp_read)(s_async_tcp* conn, t_u8 const* buffer, t_sintmax length);
TYPEDEF_ALIAS(	f_async_tcp_read, ASYNC_TCP_READ_FUNCTION, FUNCTION)
//! [internal] A single pending write buffer, in a #s_async_tcp handle's write queue
struct async_tcp_writebuf
{
	struct async_tcp_writebuf*	next;	//!< [internal] the next pending write buffer in the queue
	t_size						size;	//!< [internal] the total size of this buffer, in bytes
	t_size						sent;	//!< [internal] the amount of bytes of this buffer already sent
	t_u8*						data;	//!< [internal] the bytes to send (allocated copy)
};
struct async_tcp
{
	s_async_poll				poll;		//!< [internal] the underlying I/O poll handle (must be the first member)
	void*						data;		//!< [PUBLIC] an opaque user pointer: use it to store any custom contextual data
	t_socket					socket;		//!< [PUBLIC-read-only] the underlying connection socket
	f_async_tcp_connect			on_connect;	//!< [internal] the user callback to invoke when the pending connection attempt completes
	f_async_tcp_read			on_read;	//!< [internal] the user callback to invoke when data arrives
	t_bool						connecting;	//!< [internal] whether a non-blocking connection attempt is currently pending
	t_bool						reading;	//!< [internal] whether reading is currently enabled (see AsyncTCP_StartRead())
	struct async_tcp_writebuf*	queue_head;	//!< [internal] the first pending write buffer (or `NULL`, if none)
	struct async_tcp_writebuf*	queue_tail;	//!< [internal] the last pending write buffer (or `NULL`, if none)
};
//!@}

//! The size of the (stack) buffer used for each non-blocking read, by #s_async_tcp and #s_async_udp handles
#ifndef ASYNC_NETWORK_BUFFER_SIZE
#define ASYNC_NETWORK_BUFFER_SIZE	(8 * 1024)
#endif



//!@doc An asynchronous UDP handle: non-blocking datagram reception via a callback
//!@{
typedef struct async_udp	s_async_udp;
TYPEDEF_ALIAS(				s_async_udp, ASYNC_UDP, STRUCT)
//! The type of callback function invoked when a datagram arrives on a #s_async_udp handle (see AsyncUDP_StartRecv())
/*!
**	@param	udp		The UDP handle on which a datagram arrived
**	@param	buffer	The buffer holding the datagram bytes (only valid for the duration of this callback: copy it if needed)
**	@param	length	The amount of bytes in the datagram
**	@param	from	The address of the peer which sent this datagram
*/
typedef void	(*f_async_udp_recv)(s_async_udp* udp, t_u8 const* buffer, t_size length, s_sockaddr const* from);
TYPEDEF_ALIAS(	f_async_udp_recv, ASYNC_UDP_RECV_FUNCTION, FUNCTION)
struct async_udp
{
	s_async_poll		poll;		//!< [internal] the underlying I/O poll handle (must be the first member)
	void*				data;		//!< [PUBLIC] an opaque user pointer: use it to store any custom contextual data
	t_socket			socket;		//!< [PUBLIC-read-only] the underlying datagram socket
	f_async_udp_recv	on_recv;	//!< [internal] the user callback to invoke for each received datagram
};
//!@}



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

//!@doc Runs a concurrent accept loop on the socket `sock`, handling each connection in its own thread
/*!
**	@nonstd
**
**	This function behaves like TCP_Serve(), except that each accepted
**	connection is handled in its own newly spawned thread (via
**	`libccc/sys/thread.h`), so that several connections can be served
**	simultaneously, and one slow client cannot stall the others.
**
**	As with TCP_Serve(), the client socket is closed automatically once its
**	handler returns. If any handler returns `FALSE`, the server begins its
**	shutdown: the accept loop stops, and this function waits for every
**	currently running handler thread to finish, before returning.
**
**	NOTE: since handlers run concurrently, your handler function must be
**	thread-safe with regards to whatever shared state it accesses through
**	the `context` pointer (protect it with a #t_mutex, if it is mutable).
**
**	@param	sock	The listening socket (see TCP_Listen()) on which to accept connections
**	@param	handle	The handler function to call (in a new thread) for each accepted connection
**	@param	context	A custom user-data pointer, passed through to each `handle` call (can be `NULL`)
**	@returns
**	`0`(#OK) if the server loop ended normally (ie: a handler returned `FALSE`),
**	otherwise a non-zero error code (ie: if a call to accept() failed)
*/
//!@{
e_cccerror					TCP_Serve_Concurrent(t_socket sock, f_tcp_handler handle, void* context);
#define c_tcpserveconc		TCP_Serve_Concurrent
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



/*============================================================================*\
||                     Asynchronous Networking: Functions                     ||
\*============================================================================*/

/*
**	NOTE: as with the rest of `libccc/sys/async.h`, every one of these
**	functions must be called from the event loop's own thread (with the
**	notable exception of the write-side of #s_async_tcp/#s_async_udp handles,
**	which is safe from handle callbacks, as those run on the loop thread).
*/

//!@doc Resolves the given `host` name asynchronously, on the event loop's thread pool
/*!
**	@nonstd, analogous to libuv's `uv_getaddrinfo()`
**
**	This function behaves like Network_Resolve_All(), except that the
**	(potentially slow, blocking) DNS lookup is performed on one of the event
**	loop's worker pool threads (via AsyncWork_Submit()), so as to not block
**	the event loop; the given `callback` is then invoked back on the event
**	loop thread, with the results (see #f_async_resolve for the details).
**
**	@param	loop		The event loop on which to perform the resolution
**	@param	resolve		The resolution request handle to initialize and submit
**	@param	host		The hostname (or numeric IP address string) to resolve (duplicated internally)
**	@param	port		The port number to store in each resulting address (in host byte order)
**	@param	callback	The function to invoke (on the loop thread) once resolution completes
**	@returns
**	`0`(#OK) if the request was submitted successfully,
**	otherwise a non-zero error code
*/
//!@{
e_cccerror					Network_Resolve_Async(s_asyncloop* loop, s_async_resolve* resolve, t_char const* host, t_port port, f_async_resolve callback);
#define c_netresolveasync	Network_Resolve_Async
//!@}



//!@doc Creates a TCP server listening on `addr`, accepting connections asynchronously on the given event loop
/*!
**	@nonstd, analogous to libuv's `uv_listen()`
**
**	This function sets up a listening TCP socket (like TCP_Listen()), puts it
**	in non-blocking mode, and registers it with the given event loop: the
**	given `on_accept` callback will be invoked (on the loop thread) for each
**	incoming connection, once the loop is running (see AsyncLoop_Run()).
**
**	@param	loop		The event loop on which to serve
**	@param	server		The server handle to initialize
**	@param	addr		The local address to listen on (use SockAddr_Any() to listen on all interfaces)
**	@param	backlog		The maximum amount of pending connections to queue up (if `0`, a reasonable default is used)
**	@param	on_accept	The callback to invoke for each incoming connection (see #f_async_tcp_accept)
**	@returns
**	`0`(#OK) if the server was set up successfully,
**	otherwise a non-zero error code
*/
//!@{
e_cccerror					AsyncTCP_Listen(s_asyncloop* loop, s_async_tcp_server* server, s_sockaddr const* addr, t_uint backlog, f_async_tcp_accept on_accept);
#define c_asynctcplisten	AsyncTCP_Listen
//!@}

//!@doc Stops the given asynchronous TCP server, closing its listening socket
/*!
**	@nonstd
**
**	@param	server	The server handle to stop
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code
*/
//!@{
e_cccerror						AsyncTCP_Server_Stop(s_async_tcp_server* server);
#define c_asynctcpserverstop	AsyncTCP_Server_Stop
//!@}



//!@doc Initializes an asynchronous TCP connection handle, wrapping the given (connected) socket `sock`
/*!
**	@nonstd
**
**	The given socket is put in non-blocking mode, and registered with the
**	given event loop. This is typically used to wrap the client socket
**	received in a #f_async_tcp_accept callback; to create an outgoing
**	connection instead, see AsyncTCP_Connect().
**
**	@param	loop	The event loop on which this connection will be handled
**	@param	conn	The connection handle to initialize
**	@param	sock	The (connected) TCP socket to wrap
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code
*/
//!@{
e_cccerror				AsyncTCP_Init(s_asyncloop* loop, s_async_tcp* conn, t_socket sock);
#define c_asynctcpinit	AsyncTCP_Init
//!@}

//!@doc Creates a TCP socket, and connects it to `addr` asynchronously (without blocking the event loop)
/*!
**	@nonstd, analogous to libuv's `uv_tcp_connect()`
**
**	This function initializes the given connection handle (like AsyncTCP_Init()),
**	and begins a non-blocking connection attempt to the given address:
**	the given `on_connect` callback is invoked (on the loop thread) once the
**	connection attempt completes, whether successfully or not.
**	Any AsyncTCP_Write()/AsyncTCP_StartRead() calls made before the connection
**	completes are handled gracefully (writes are queued, reads begin once connected).
**
**	@param	loop		The event loop on which this connection will be handled
**	@param	conn		The connection handle to initialize
**	@param	addr		The remote address to connect to
**	@param	on_connect	The callback to invoke once the connection attempt completes (see #f_async_tcp_connect)
**	@returns
**	`0`(#OK) if the connection attempt was started successfully,
**	otherwise a non-zero error code
*/
//!@{
e_cccerror					AsyncTCP_Connect(s_asyncloop* loop, s_async_tcp* conn, s_sockaddr const* addr, f_async_tcp_connect on_connect);
#define c_asynctcpconnect	AsyncTCP_Connect
//!@}

//!@doc Starts reading from the given TCP connection: `on_read` is invoked whenever data arrives
/*!
**	@nonstd, analogous to libuv's `uv_read_start()`
**
**	@param	conn	The connection handle to start reading from
**	@param	on_read	The callback to invoke whenever data arrives (see #f_async_tcp_read)
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code
*/
//!@{
e_cccerror						AsyncTCP_StartRead(s_async_tcp* conn, f_async_tcp_read on_read);
#define c_asynctcpread			AsyncTCP_StartRead
//!@}

//!@doc Stops reading from the given TCP connection (its `on_read` callback will no longer be invoked)
/*!
**	@nonstd, analogous to libuv's `uv_read_stop()`
**
**	@param	conn	The connection handle to stop reading from
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code
*/
//!@{
e_cccerror						AsyncTCP_StopRead(s_async_tcp* conn);
#define c_asynctcpstopread		AsyncTCP_StopRead
//!@}

//!@doc Writes `n` bytes of `data` to the given TCP connection, without ever blocking
/*!
**	@nonstd, analogous to libuv's `uv_write()`
**
**	As much of the given data as possible is sent immediately; any remainder
**	is copied to an internal queue, and sent automatically (by the event loop)
**	as soon as the connection becomes writable again. This means the given
**	`data` buffer can be safely discarded as soon as this function returns.
**
**	@param	conn	The connection handle to write to
**	@param	data	The buffer of data to send (copied internally, if it cannot be sent immediately)
**	@param	n		The amount of bytes to send from `data`
**	@returns
**	`0`(#OK) if the data was sent (or queued) successfully,
**	otherwise a non-zero error code
*/
//!@{
e_cccerror					AsyncTCP_Write(s_async_tcp* conn, void const* data, t_size n);
#define c_asynctcpwrite		AsyncTCP_Write
//!@}

//!@doc Closes the given TCP connection, freeing any queued writes, and closing its socket
/*!
**	@nonstd
**
**	NOTE: any data still waiting in the write queue is discarded: if you wish
**	to ensure everything is sent before closing, keep the connection open
**	until your protocol-level exchange confirms reception.
**
**	@param	conn	The connection handle to close
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code
*/
//!@{
e_cccerror				AsyncTCP_Close(s_async_tcp* conn);
#define c_asynctcpclose	AsyncTCP_Close
//!@}



//!@doc Initializes an asynchronous UDP handle, wrapping the given datagram socket `sock`
/*!
**	@nonstd
**
**	The given socket is put in non-blocking mode, and registered with the
**	given event loop. To send datagrams on this handle, simply use
**	Socket_SendTo()/UDP_SendTo() with `udp->socket` (individual datagram
**	sends do not meaningfully block, so no special async variant is needed).
**
**	@param	loop	The event loop on which this UDP handle will be handled
**	@param	udp		The UDP handle to initialize
**	@param	sock	The (#SOCKTYPE_DGRAM) socket to wrap (see UDP_New())
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code
*/
//!@{
e_cccerror				AsyncUDP_Init(s_asyncloop* loop, s_async_udp* udp, t_socket sock);
#define c_asyncudpinit	AsyncUDP_Init
//!@}

//!@doc Starts receiving on the given UDP handle: `on_recv` is invoked for each arriving datagram
/*!
**	@nonstd, analogous to libuv's `uv_udp_recv_start()`
**
**	@param	udp		The UDP handle to start receiving on
**	@param	on_recv	The callback to invoke for each received datagram (see #f_async_udp_recv)
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code
*/
//!@{
e_cccerror					AsyncUDP_StartRecv(s_async_udp* udp, f_async_udp_recv on_recv);
#define c_asyncudprecv		AsyncUDP_StartRecv
//!@}

//!@doc Stops receiving on the given UDP handle (its `on_recv` callback will no longer be invoked)
/*!
**	@nonstd, analogous to libuv's `uv_udp_recv_stop()`
**
**	@param	udp	The UDP handle to stop receiving on
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code
*/
//!@{
e_cccerror					AsyncUDP_StopRecv(s_async_udp* udp);
#define c_asyncudpstoprecv	AsyncUDP_StopRecv
//!@}

//!@doc Closes the given UDP handle, closing its socket
/*!
**	@nonstd
**
**	@param	udp	The UDP handle to close
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code
*/
//!@{
e_cccerror				AsyncUDP_Close(s_async_udp* udp);
#define c_asyncudpclose	AsyncUDP_Close
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
