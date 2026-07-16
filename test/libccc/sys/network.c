
#if (defined(_WIN32) && !defined(__CYGWIN__))
	#include <winsock2.h>
#else
	#include <arpa/inet.h>
#endif

#include "libccc.h"
#include "libccc/bool.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/sys/socket.h"
#include "libccc/sys/network.h"
#include "libccc/sys/thread.h"
#include "libccc/sys/async.h"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                           Test Fixtures (Helpers)                          ||
\*============================================================================*/

/*
**	As with the `libccc/sys/socket` test suite: the pure functions of this
**	header (byte order conversions) are tested directly against their libc
**	equivalents, whereas the stateful/behavioral functions (DNS, TCP servers,
**	UDP, async handles) are exercised through self-contained loopback
**	"scenario" helper functions, each of which reduces its observable outcome
**	to a single comparable value for the standard test framework machinery.
*/

//! The maximum message length used by the scenario fixtures below
#define SCENARIO_BUFFER	1024



//! SCENARIO: resolves `host`, and converts the first resolved address to a string
static
t_char*	scenario_resolve_tostring(t_char const* host, t_port port)
{
	s_sockaddr	addr;

	if (Network_Resolve(&addr, host, port) != ERROR_NONE)
		return (NULL);
	return (SockAddr_ToString(&addr));
}

//! SCENARIO: resolves `host`, and checks that every result is a loopback address
static
t_bool	scenario_resolve_loopback(t_char const* host)
{
	s_sockaddr*	addresses;
	t_uint	amount = 0;
	t_bool	result = TRUE;

	addresses = Network_Resolve_All(&amount, host, 80);
	if (addresses == NULL || amount == 0)
		return (FALSE);
	for (t_uint i = 0; i < amount; ++i)
	{
		if (!((addresses[i].family == SOCKAF_IPV4 && addresses[i].ip.ipv4[0] == 127) ||
			  (addresses[i].family == SOCKAF_IPV6 && addresses[i].ip.ipv6[15] == 1)))
			result = FALSE;
	}
	Memory_Free(addresses);
	return (result);
}

//! SCENARIO: performs a reverse DNS lookup of the IPv4 loopback address
static
t_bool	scenario_gethostname_loopback(void)
{
	s_sockaddr	addr = SockAddr_LocalHost(SOCKAF_IPV4, 0);
	t_char*	name = Network_GetHostName(&addr);
	t_bool	result = (name != NULL && name[0] != '\0');

	if (name != NULL)
		Memory_Free(name);
	return (result);
}



//! The context shared between a TCP_Serve()-based echo fixture and its clients
typedef struct serve_fixture
{
	t_socket	listener;	//!< the listening socket
	s_sockaddr	addr;		//!< the address of the listener (with the resolved ephemeral port)
	t_thread	thread;		//!< the thread running the TCP_Serve()/TCP_Serve_Concurrent() accept loop
	t_mutex		mutex;		//!< protects `handled` (for the concurrent variant)
	int			handled;	//!< how many connections were fully handled
	t_bool		concurrent;	//!< whether to use TCP_Serve_Concurrent() rather than TCP_Serve()
	e_cccerror	serve_result;	//!< the return value of the serve call
}	s_serve_fixture;

//! The connection handler: echoes one message; a "quit" message stops the server
static
t_bool	serve_fixture_handler(t_socket client, s_sockaddr const* addr, void* context)
{
	s_serve_fixture*	fixture = (s_serve_fixture*)context;
	t_char	buffer[SCENARIO_BUFFER] = {0};
	t_sintmax	received;
	(void)addr;

	received = Socket_Recv(client, buffer, SCENARIO_BUFFER, SOCKMSG_NONE);
	if (received > 0)
		Socket_Send_All(client, buffer, (t_size)received);
	Mutex_Lock(&fixture->mutex);
	fixture->handled += 1;
	Mutex_Unlock(&fixture->mutex);
	return (!String_Equals(buffer, "quit"));
}

//! The thread which runs the blocking accept loop
static
void*	serve_fixture_thread(void* arg)
{
	s_serve_fixture*	fixture = (s_serve_fixture*)arg;

	if (fixture->concurrent)
		fixture->serve_result = TCP_Serve_Concurrent(fixture->listener, serve_fixture_handler, fixture);
	else
		fixture->serve_result = TCP_Serve(fixture->listener, serve_fixture_handler, fixture);
	return (NULL);
}

//! Sets up a loopback echo server fixture, running TCP_Serve() (or its concurrent variant) in a thread
static
e_cccerror	serve_fixture_start(s_serve_fixture* fixture, t_bool concurrent)
{
	s_sockaddr	local = SockAddr_LocalHost(SOCKAF_IPV4, PORT_ANY);

	fixture->handled = 0;
	fixture->concurrent = concurrent;
	fixture->serve_result = ERROR_UNSPECIFIED;
	if (Mutex_Init(&fixture->mutex) != ERROR_NONE)
		return (ERROR_SYSTEM);
	fixture->listener = TCP_Listen(&local, 8);
	if (fixture->listener == SOCKET_INVALID)
		return (ERROR_SYSTEM);
	if (Socket_GetAddress(&fixture->addr, fixture->listener) != ERROR_NONE ||
		Thread_New(&fixture->thread, serve_fixture_thread, fixture) != ERROR_NONE)
	{
		Socket_Close(fixture->listener);
		return (ERROR_SYSTEM);
	}
	return (ERROR_NONE);
}

//! Sends one message to the fixture server (via TCP_Connect()), returns the echoed reply
static
t_char*	serve_fixture_exchange(s_serve_fixture* fixture, t_char const* message)
{
	t_char	buffer[SCENARIO_BUFFER] = {0};
	t_socket	client;
	t_size	length = String_Length(message);

	client = TCP_Connect("localhost", fixture->addr.port);
	if (client == SOCKET_INVALID)
		return (NULL);
	if (Socket_Send_All(client, message, length) != ERROR_NONE ||
		Socket_Recv_All(client, buffer, length) != (t_sintmax)length)
	{
		Socket_Close(client);
		return (NULL);
	}
	Socket_Close(client);
	return (String_Duplicate(buffer));
}

//! Stops the fixture server (sends the "quit" message), and joins its thread
static
void	serve_fixture_stop(s_serve_fixture* fixture)
{
	t_char*	reply = serve_fixture_exchange(fixture, "quit");

	if (reply != NULL)
		Memory_Free(reply);
	Thread_Join(fixture->thread, NULL);
	Socket_Close(fixture->listener);
	Mutex_Delete(&fixture->mutex);
}

//! SCENARIO: TCP_Listen() + TCP_Serve() + TCP_Connect(): echoes `message` through a loopback server
static
t_char*	scenario_tcp_serve_echo(t_char const* message)
{
	s_serve_fixture	fixture;
	t_char*	reply;

	if (serve_fixture_start(&fixture, FALSE) != ERROR_NONE)
		return (NULL);
	reply = serve_fixture_exchange(&fixture, message);
	serve_fixture_stop(&fixture);
	if (fixture.serve_result != ERROR_NONE && reply != NULL)
	{	// the accept loop should have ended gracefully (returning ERROR_NONE)
		Memory_Free(reply);
		return (NULL);
	}
	return (reply);
}

//! SCENARIO: serves `clients` simultaneous connections with TCP_Serve_Concurrent(); returns the handled count
static
t_sintmax	scenario_tcp_serve_concurrent(t_sintmax clients)
{
	s_serve_fixture	fixture;
	t_char*	replies[16] = {0};
	t_sintmax	handled;
	t_bool	all_ok = TRUE;

	if (clients > 16)
		return (-1);
	if (serve_fixture_start(&fixture, TRUE) != ERROR_NONE)
		return (-1);
	for (t_sintmax i = 0; i < clients; ++i)
	{
		replies[i] = serve_fixture_exchange(&fixture, "hello");
		if (replies[i] == NULL || !String_Equals(replies[i], "hello"))
			all_ok = FALSE;
		if (replies[i] != NULL)
			Memory_Free(replies[i]);
	}
	serve_fixture_stop(&fixture); // sends "quit": counts as one more handled connection
	handled = fixture.handled;
	if (!all_ok || fixture.serve_result != ERROR_NONE)
		return (-1);
	return (handled);
}

//! SCENARIO: sends a datagram through UDP_New()/UDP_SendTo() (hostname-resolving), returns the payload
static
t_char*	scenario_udp_sendto(t_char const* message)
{
	s_sockaddr	local = SockAddr_LocalHost(SOCKAF_IPV4, PORT_ANY);
	s_sockaddr	bound = SOCKADDR_NULL;
	s_sockaddr	from = SOCKADDR_NULL;
	t_char		buffer[SCENARIO_BUFFER] = {0};
	t_socket	receiver;
	t_socket	sender;
	t_sintmax	transferred;
	t_size		length = String_Length(message);

	receiver = UDP_New(&local);
	sender   = UDP_New(NULL);
	if (receiver == SOCKET_INVALID || sender == SOCKET_INVALID)
		return (NULL);
	if (Socket_GetAddress(&bound, receiver) != ERROR_NONE)
	{
		Socket_Close(receiver);
		Socket_Close(sender);
		return (NULL);
	}
	transferred = UDP_SendTo(sender, message, length, "localhost", bound.port);
	if (transferred == (t_sintmax)length)
		transferred = UDP_RecvFrom(receiver, buffer, SCENARIO_BUFFER, &from);
	Socket_Close(receiver);
	Socket_Close(sender);
	if (transferred != (t_sintmax)length)
		return (NULL);
	return (String_Duplicate(buffer));
}



/*
**	Asynchronous (event loop) scenario: a full echo exchange (async server +
**	async client) driven by a single AsyncLoop_Run() call, on a single thread.
*/
typedef struct async_scenario
{
	s_asyncloop*		loop;
	s_async_tcp_server	server;
	s_async_tcp			server_conn;
	s_async_tcp			client;
	t_char const*		message;
	t_char				reply[SCENARIO_BUFFER];
	t_bool				connected;
}	s_async_scenario;

static
void	async_scenario_server_on_read(s_async_tcp* conn, t_u8 const* buffer, t_sintmax length)
{
	s_async_scenario*	ctx = (s_async_scenario*)conn->data;

	if (length <= 0)
	{	// client closed: shut everything down, so the loop can end
		AsyncTCP_Close(conn);
		AsyncTCP_Server_Stop(&ctx->server);
		return;
	}
	AsyncTCP_Write(conn, buffer, (t_size)length); // echo
}

static
void	async_scenario_on_accept(s_async_tcp_server* server, t_socket client, s_sockaddr const* addr)
{
	s_async_scenario*	ctx = (s_async_scenario*)server->data;
	(void)addr;

	if (AsyncTCP_Init(ctx->loop, &ctx->server_conn, client) != ERROR_NONE)
		return;
	ctx->server_conn.data = ctx;
	AsyncTCP_StartRead(&ctx->server_conn, async_scenario_server_on_read);
}

static
void	async_scenario_client_on_read(s_async_tcp* conn, t_u8 const* buffer, t_sintmax length)
{
	s_async_scenario*	ctx = (s_async_scenario*)conn->data;

	if (length > 0 && (t_size)length < SCENARIO_BUFFER)
		Memory_Copy(ctx->reply, buffer, (t_size)length);
	AsyncTCP_Close(conn); // the server-side connection sees EOF, and stops the server
}

static
void	async_scenario_client_on_connect(s_async_tcp* conn, e_cccerror error)
{
	s_async_scenario*	ctx = (s_async_scenario*)conn->data;

	if (error != ERROR_NONE)
		return;
	ctx->connected = TRUE;
	AsyncTCP_Write(conn, ctx->message, String_Length(ctx->message));
	AsyncTCP_StartRead(conn, async_scenario_client_on_read);
}

//! SCENARIO: echoes `message` through an async loopback server+client, on one event loop
static
t_char*	scenario_async_tcp_echo(t_char const* message)
{
	s_async_scenario	ctx = {0};
	s_sockaddr	local = SockAddr_LocalHost(SOCKAF_IPV4, PORT_ANY);
	s_sockaddr	bound = SOCKADDR_NULL;

	ctx.message = message;
	ctx.loop = AsyncLoop_New();
	if (ctx.loop == NULL)
		return (NULL);
	if (AsyncTCP_Listen(ctx.loop, &ctx.server, &local, 1, async_scenario_on_accept) != ERROR_NONE ||
		Socket_GetAddress(&bound, ctx.server.socket) != ERROR_NONE)
	{
		AsyncLoop_Delete(&ctx.loop);
		return (NULL);
	}
	ctx.server.data = &ctx;
	if (AsyncTCP_Connect(ctx.loop, &ctx.client, &bound, async_scenario_client_on_connect) != ERROR_NONE)
	{
		AsyncTCP_Server_Stop(&ctx.server);
		AsyncLoop_Delete(&ctx.loop);
		return (NULL);
	}
	ctx.client.data = &ctx;
	AsyncLoop_Run(ctx.loop, ASYNCRUN_DEFAULT);
	AsyncLoop_Delete(&ctx.loop);
	if (!ctx.connected)
		return (NULL);
	return (String_Duplicate(ctx.reply));
}



//! The context for the async DNS resolution scenario
typedef struct async_resolve_scenario
{
	e_cccerror	error;
	t_bool		callback_ran;
	t_bool		found_loopback;
}	s_async_resolve_scenario;

static
void	async_resolve_scenario_callback(s_async_resolve* resolve, e_cccerror error, s_sockaddr const* addresses, t_uint amount)
{
	s_async_resolve_scenario*	ctx = (s_async_resolve_scenario*)resolve->data;

	ctx->callback_ran = TRUE;
	ctx->error = error;
	for (t_uint i = 0; i < amount; ++i)
	{
		if ((addresses[i].family == SOCKAF_IPV4 && addresses[i].ip.ipv4[0] == 127) ||
			(addresses[i].family == SOCKAF_IPV6 && addresses[i].ip.ipv6[15] == 1))
			ctx->found_loopback = TRUE;
	}
}

//! SCENARIO: resolves `host` on the event loop's thread pool; TRUE if it resolves to loopback
static
t_bool	scenario_async_resolve(t_char const* host, t_bool expect_success)
{
	s_asyncloop*	loop = AsyncLoop_New();
	s_async_resolve	request;
	s_async_resolve_scenario	ctx = {0};

	if (loop == NULL)
		return (FALSE);
	if (Network_Resolve_Async(loop, &request, host, 80, async_resolve_scenario_callback) != ERROR_NONE)
	{
		AsyncLoop_Delete(&loop);
		return (FALSE);
	}
	request.data = &ctx;
	AsyncLoop_Run(loop, ASYNCRUN_DEFAULT);
	AsyncLoop_Delete(&loop);
	if (!ctx.callback_ran)
		return (FALSE);
	if (expect_success)
		return (ctx.error == ERROR_NONE && ctx.found_loopback);
	else
		return (ctx.error != ERROR_NONE && !ctx.found_loopback);
}



/*============================================================================*\
||                      Testing Functions: byte order                         ||
\*============================================================================*/



#ifndef c_htons
void test_htons(void)	{}
#warning "htons() test suite function defined, but the function isn't defined."
#else
void	print_test_htons(char const* test_name, t_testflags flags,
		t_u16 value)
{
	TEST_INIT(u16)
	TEST_PERFORM_LIBC(	htons, value)
	TEST_PRINT_LIBC(u16,htons, "value=0x%04X", value)
}
void	test_htons(void)
{
/*	| TEST FUNCTION | TEST NAME       |TESTFLAG| TEST ARGS	*/
	print_test_htons("htons           ",	FALSE, 0x0000);
	print_test_htons("htons           ",	FALSE, 0x0001);
	print_test_htons("htons           ",	FALSE, 0x1234);
	print_test_htons("htons           ",	FALSE, 0x8000);
	print_test_htons("htons           ",	FALSE, 0xABCD);
	print_test_htons("htons           ",	FALSE, 0xFFFF);
}
#endif

#ifndef c_htonl
void test_htonl(void)	{}
#warning "htonl() test suite function defined, but the function isn't defined."
#else
void	print_test_htonl(char const* test_name, t_testflags flags,
		t_u32 value)
{
	TEST_INIT(u32)
	TEST_PERFORM_LIBC(	htonl, value)
	TEST_PRINT_LIBC(u32,htonl, "value=0x%08X", value)
}
void	test_htonl(void)
{
/*	| TEST FUNCTION | TEST NAME       |TESTFLAG| TEST ARGS	*/
	print_test_htonl("htonl           ",	FALSE, 0x00000000);
	print_test_htonl("htonl           ",	FALSE, 0x00000001);
	print_test_htonl("htonl           ",	FALSE, 0x12345678);
	print_test_htonl("htonl           ",	FALSE, 0x80000001);
	print_test_htonl("htonl           ",	FALSE, 0xDEADBEEF);
	print_test_htonl("htonl           ",	FALSE, 0xFFFFFFFF);
}
#endif

#ifndef c_ntohs
void test_ntohs(void)	{}
#warning "ntohs() test suite function defined, but the function isn't defined."
#else
void	print_test_ntohs(char const* test_name, t_testflags flags,
		t_u16 value)
{
	TEST_INIT(u16)
	TEST_PERFORM_LIBC(	ntohs, value)
	TEST_PRINT_LIBC(u16,ntohs, "value=0x%04X", value)
}
void	test_ntohs(void)
{
/*	| TEST FUNCTION | TEST NAME       |TESTFLAG| TEST ARGS	*/
	print_test_ntohs("ntohs           ",	FALSE, 0x0000);
	print_test_ntohs("ntohs           ",	FALSE, 0x0100);
	print_test_ntohs("ntohs           ",	FALSE, 0x3412);
	print_test_ntohs("ntohs           ",	FALSE, 0xCDAB);
	print_test_ntohs("ntohs           ",	FALSE, 0xFFFF);
}
#endif

#ifndef c_ntohl
void test_ntohl(void)	{}
#warning "ntohl() test suite function defined, but the function isn't defined."
#else
void	print_test_ntohl(char const* test_name, t_testflags flags,
		t_u32 value)
{
	TEST_INIT(u32)
	TEST_PERFORM_LIBC(	ntohl, value)
	TEST_PRINT_LIBC(u32,ntohl, "value=0x%08X", value)
}
void	test_ntohl(void)
{
/*	| TEST FUNCTION | TEST NAME       |TESTFLAG| TEST ARGS	*/
	print_test_ntohl("ntohl           ",	FALSE, 0x00000000);
	print_test_ntohl("ntohl           ",	FALSE, 0x01000000);
	print_test_ntohl("ntohl           ",	FALSE, 0x78563412);
	print_test_ntohl("ntohl           ",	FALSE, 0xEFBEADDE);
	print_test_ntohl("ntohl           ",	FALSE, 0xFFFFFFFF);
}
#endif

#ifndef c_htonll
void test_htonll(void)	{}
#warning "htonll() test suite function defined, but the function isn't defined."
#else
//! (there is no standard libc `htonll()`: so, check the byte layout explicitly, and check round-trips)
static
void const*	helper_htonll_bytes(t_u64 value)
{
	static t_u64	result;

	result = c_htonll(value);
	return (&result);
}
void	print_test_htonll(char const* test_name, t_testflags flags,
		t_u8 const* expecting, // the expected 8 bytes, in memory order
		t_u64 value)
{
	TEST_INIT(mem)
	test.length = sizeof(t_u64);
	TEST_PERFORM_(result, helper_htonll_bytes, value)
	test.expect = (void const*)expecting;
	TEST_PRINT(mem,	htonll, "value=0x%016llX", (unsigned long long)value)
}
void	print_test_ntohll_roundtrip(char const* test_name, t_testflags flags,
		t_u64 value)
{
	TEST_INIT(u64)
	TEST_PERFORM_(result, c_ntohll, c_htonll(value))
	test.expect = value;
	TEST_PRINT(u64,	ntohll, "value=0x%016llX (round-trip)", (unsigned long long)value)
}
void	test_htonll(void)
{
	static t_u8 const bytes_zero[8]    = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	static t_u8 const bytes_one[8]     = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
	static t_u8 const bytes_pattern[8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
	static t_u8 const bytes_full[8]    = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
/*	| TEST FUNCTION  | TEST NAME       |TESTFLAG| EXPECTING     | TEST ARGS	*/
	print_test_htonll("htonll           ",	FALSE, bytes_zero,    0x0000000000000000ull);
	print_test_htonll("htonll           ",	FALSE, bytes_one,     0x0000000000000001ull);
	print_test_htonll("htonll           ",	FALSE, bytes_pattern, 0x0123456789ABCDEFull);
	print_test_htonll("htonll           ",	FALSE, bytes_full,    0xFFFFFFFFFFFFFFFFull);
	print_test_ntohll_roundtrip("ntohll (round-trip)",	FALSE, 0x0123456789ABCDEFull);
	print_test_ntohll_roundtrip("ntohll (round-trip)",	FALSE, 0x8000000000000001ull);
}
#endif



/*============================================================================*\
||                   Testing Functions: hostname resolution                   ||
\*============================================================================*/



#ifndef c_netresolve
void test_netresolve(void)	{}
#warning "netresolve() test suite function defined, but the function isn't defined."
#else
void	print_test_netresolve(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* host,
		t_port port)
{
	TEST_INIT(str)
	TEST_PERFORM_(result, scenario_resolve_tostring, host, port)
	test.expect = expecting;
	TEST_PRINT(str,	netresolve, "host=\"%s\", port=%u", host, (unsigned)port)
	TEST_FREE()
}
void	print_test_netresolve_loopback(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* host)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_resolve_loopback, host)
	test.expect = expecting;
	TEST_PRINT(bool,netresolveall, "host=\"%s\" (expecting only loopback addresses)", host)
}
void	test_netresolve(void)
{
/*	| TEST FUNCTION      | TEST NAME                          |TESTFLAG| EXPECTING          | TEST ARGS			*/
	print_test_netresolve("netresolve (numeric ipv4)          ",	FALSE,     "127.0.0.1:80", "127.0.0.1",       80);
	print_test_netresolve("netresolve (numeric ipv4, private) ",	FALSE, "10.20.30.40:8080", "10.20.30.40",   8080);
	print_test_netresolve("netresolve (numeric ipv6)          ",	FALSE,        "[::1]:443", "::1",            443);
	print_test_netresolve("netresolve (bad: invalid hostname) ",	FALSE,               NULL, "no.such.host.invalid", 80);
	print_test_netresolve("netresolve (bad: empty hostname)   ",	FALSE,               NULL, "",                80);
	print_test_netresolve_loopback(
	                      "netresolveall (\"localhost\")        ",	FALSE, TRUE, "localhost");
}
#endif



#ifndef c_nethostname
void test_nethostname(void)	{}
#warning "nethostname() test suite function defined, but the function isn't defined."
#else
void	print_test_nethostname(char const* test_name, t_testflags flags,
		t_bool expecting)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_gethostname_loopback)
	test.expect = expecting;
	TEST_PRINT(bool,nethostname, "(reverse lookup of 127.0.0.1: expecting a non-empty name)")
}
void	test_nethostname(void)
{
	print_test_nethostname("nethostname (reverse loopback)    ",	FALSE, TRUE);
}
#endif



/*============================================================================*\
||                     Testing Functions: TCP/UDP servers                     ||
\*============================================================================*/



#ifndef c_tcpserve
void test_tcpserve(void)	{}
#warning "tcpserve() test suite function defined, but the function isn't defined."
#else
void	print_test_tcpserve(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* message)
{
	TEST_INIT(str)
	TEST_PERFORM_(result, scenario_tcp_serve_echo, message)
	test.expect = expecting;
	TEST_PRINT(str,	tcpserve, "message=\"%s\" (tcplisten + tcpserve + tcpconnect, loopback echo)", message)
	TEST_FREE()
}
void	test_tcpserve(void)
{
/*	| TEST FUNCTION    | TEST NAME                     |TESTFLAG| EXPECTING          | TEST ARGS			*/
	print_test_tcpserve("tcpserve (loopback echo)      ",	FALSE,   "Hello, Server!", "Hello, Server!");
	print_test_tcpserve("tcpserve (single char)        ",	FALSE,                "!", "!");
}
#endif



#ifndef c_tcpserveconc
void test_tcpserveconcurrent(void)	{}
#warning "tcpserveconcurrent() test suite function defined, but the function isn't defined."
#else
void	print_test_tcpserveconcurrent(char const* test_name, t_testflags flags,
		t_sintmax expecting, // the expected amount of handled connections (clients + the final "quit")
		t_sintmax clients)
{
	TEST_INIT(sintmax)
	TEST_PERFORM_(result, scenario_tcp_serve_concurrent, clients)
	test.expect = expecting;
	TEST_PRINT(sintmax,	tcpserveconc, "clients=%li (each connection handled in its own thread)", (long)clients)
}
void	test_tcpserveconcurrent(void)
{
/*	| TEST FUNCTION              | TEST NAME                          |TESTFLAG| EXPECTING | TEST ARGS	*/
	print_test_tcpserveconcurrent("tcpserveconc (1 client + quit)     ",	FALSE,        2, 1);
	print_test_tcpserveconcurrent("tcpserveconc (3 clients + quit)    ",	FALSE,        4, 3);
}
#endif



#ifndef c_udpsendto
void test_udpsendto(void)	{}
#warning "udpsendto() test suite function defined, but the function isn't defined."
#else
void	print_test_udpsendto(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* message)
{
	TEST_INIT(str)
	TEST_PERFORM_(result, scenario_udp_sendto, message)
	test.expect = expecting;
	TEST_PRINT(str,	udpsendto, "message=\"%s\" (udpnew + udpsendto \"localhost\" + udprecvfrom)", message)
	TEST_FREE()
}
void	test_udpsendto(void)
{
/*	| TEST FUNCTION     | TEST NAME                     |TESTFLAG| EXPECTING       | TEST ARGS			*/
	print_test_udpsendto("udpsendto (loopback datagram) ",	FALSE, "ping datagram", "ping datagram");
}
#endif



/*============================================================================*\
||                   Testing Functions: async networking                      ||
\*============================================================================*/



#ifndef c_asynctcplisten
void test_asynctcp(void)	{}
#warning "asynctcp() test suite function defined, but the function isn't defined."
#else
void	print_test_asynctcp(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* message)
{
	TEST_INIT(str)
	TEST_PERFORM_(result, scenario_async_tcp_echo, message)
	test.expect = expecting;
	TEST_PRINT(str,	asynctcplisten, "message=\"%s\" (async loopback echo, single event loop)", message)
	TEST_FREE()
}
void	test_asynctcp(void)
{
/*	| TEST FUNCTION    | TEST NAME                       |TESTFLAG| EXPECTING     | TEST ARGS			*/
	print_test_asynctcp("asynctcp (event-driven echo)    ",	FALSE, "async hello!", "async hello!");
	print_test_asynctcp("asynctcp (event-driven echo)    ",	FALSE,            "x", "x");
}
#endif



#ifndef c_netresolveasync
void test_asyncresolve(void)	{}
#warning "asyncresolve() test suite function defined, but the function isn't defined."
#else
void	print_test_asyncresolve(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* host,
		t_bool expect_success)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_async_resolve, host, expect_success)
	test.expect = expecting;
	TEST_PRINT(bool,netresolveasync, "host=\"%s\" (resolved on the event loop's thread pool)", host)
}
void	test_asyncresolve(void)
{
/*	| TEST FUNCTION        | TEST NAME                        |TESTFLAG| EXPECTING | TEST ARGS			*/
	print_test_asyncresolve("netresolveasync (localhost)      ",	FALSE,     TRUE, "localhost",            TRUE);
	print_test_asyncresolve("netresolveasync (invalid host)   ",	FALSE,     TRUE, "no.such.host.invalid", FALSE);
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/



int		testsuite_sys_network(void)
{
	print_suite_title("libccc/sys/network");

	if (Socket_Init() != ERROR_NONE)
		return (ERROR);

	test_htons();
	test_htonl();
	test_ntohs();
	test_ntohl();
	test_htonll();

	test_netresolve();
	test_nethostname();

	test_tcpserve();
	test_tcpserveconcurrent();
	test_udpsendto();

	test_asynctcp();
	test_asyncresolve();

	Socket_Exit();
	return (OK);
}
