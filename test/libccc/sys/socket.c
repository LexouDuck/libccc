
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
#include "libccc/sys/thread.h"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                              Testing Variables                             ||
\*============================================================================*/

//! An IPv6 loopback address struct ("::1"), for tests
static
s_sockaddr	sockaddr_ipv6_loopback(t_port port)
{
	s_sockaddr	result = SOCKADDR_NULL;

	result.family = SOCKAF_IPV6;
	result.port = port;
	result.ip.ipv6[15] = 1;
	return (result);
}



/*============================================================================*\
||                           Test Fixtures (Helpers)                          ||
\*============================================================================*/

/*
**	The functions of the socket API are inherently stateful (they operate on
**	live system resources), so most of them cannot be tested as lone pure
**	functions. Instead, each of the "scenario" helper functions below runs a
**	full self-contained loopback exchange (spawning a peer thread when one is
**	needed), and reduces its observable outcome to a single comparable value
**	(a string, a boolean, or an integer), which the standard test framework
**	machinery can then compare against an expected value, as usual.
*/

//! The maximum message length used by the scenario fixtures below
#define SCENARIO_BUFFER	1024

typedef struct tcp_echo_server
{
	t_socket	listener;	//!< the listening socket (bound to a loopback ephemeral port)
	s_sockaddr	addr;		//!< the address of the listener (with the resolved ephemeral port)
	t_thread	thread;		//!< the server thread (accepts one connection, echoes, and exits)
}	s_tcp_echo_server;

//! The server thread: accepts a single connection, echoes everything until EOF, then exits
static
void*	tcp_echo_server_thread(void* arg)
{
	s_tcp_echo_server*	server = (s_tcp_echo_server*)arg;
	t_char	buffer[SCENARIO_BUFFER];
	t_socket	client;
	t_sintmax	received;

	client = Socket_Accept(server->listener, NULL);
	if (client == SOCKET_INVALID)
		return (NULL);
	while ((received = Socket_Recv(client, buffer, SCENARIO_BUFFER, SOCKMSG_NONE)) > 0)
	{
		if (Socket_Send_All(client, buffer, (t_size)received) != ERROR_NONE)
			break;
	}
	Socket_Close(client);
	return (NULL);
}

//! Sets up a loopback TCP echo server (listener + thread); returns `ERROR_NONE` on success
static
e_cccerror	tcp_echo_server_start(s_tcp_echo_server* server)
{
	s_sockaddr	local = SockAddr_LocalHost(SOCKAF_IPV4, PORT_ANY);

	server->listener = Socket_New(SOCKAF_IPV4, SOCKTYPE_STREAM, SOCKPROTO_TCP);
	if (server->listener == SOCKET_INVALID)
		return (ERROR_SYSTEM);
	if (Socket_Bind(server->listener, &local) != ERROR_NONE ||
		Socket_Listen(server->listener, 1) != ERROR_NONE ||
		Socket_GetAddress(&server->addr, server->listener) != ERROR_NONE ||
		Thread_New(&server->thread, tcp_echo_server_thread, server) != ERROR_NONE)
	{
		Socket_Close(server->listener);
		return (ERROR_SYSTEM);
	}
	return (ERROR_NONE);
}

//! Tears down a loopback TCP echo server (joins the thread, closes the listener)
static
void	tcp_echo_server_stop(s_tcp_echo_server* server)
{
	Thread_Join(server->thread, NULL);
	Socket_Close(server->listener);
}



//! SCENARIO: parses `str`, then converts the parsed address back to a string (round-trip)
static
t_char*	scenario_sockaddr_roundtrip(t_char const* str, t_port port)
{
	s_sockaddr	addr = SOCKADDR_NULL;

	if (SockAddr_Parse(&addr, str) != ERROR_NONE)
		return (NULL);
	addr.port = port; // SockAddr_Parse() only fills the `.family` and `.ip` fields
	return (SockAddr_ToString(&addr));
}

//! SCENARIO: connects to a loopback echo server, sends `message`, returns what comes back
static
t_char*	scenario_tcp_echo(t_char const* message)
{
	s_tcp_echo_server	server;
	t_char		buffer[SCENARIO_BUFFER] = {0};
	t_socket	client;
	t_size		length = String_Length(message);

	if (tcp_echo_server_start(&server) != ERROR_NONE)
		return (NULL);
	client = Socket_New(SOCKAF_IPV4, SOCKTYPE_STREAM, SOCKPROTO_TCP);
	if (client == SOCKET_INVALID)
		return (tcp_echo_server_stop(&server), NULL);
	if (Socket_Connect(client, &server.addr) != ERROR_NONE ||
		Socket_Send_All(client, message, length) != ERROR_NONE ||
		Socket_Recv_All(client, buffer, length) != (t_sintmax)length)
	{
		Socket_Close(client);
		tcp_echo_server_stop(&server);
		return (NULL);
	}
	Socket_Close(client);
	tcp_echo_server_stop(&server);
	return (String_Duplicate(buffer));
}

//! SCENARIO: checks that a socket option, once set, reads back with the same value
static
t_bool	scenario_option_roundtrip(e_sockopt option, t_bool value)
{
	t_socket	sock = Socket_New(SOCKAF_IPV4, SOCKTYPE_STREAM, SOCKPROTO_TCP);
	t_bool		result;

	if (sock == SOCKET_INVALID)
		return (FALSE);
	if (Socket_SetOption_Bool(sock, option, value) != ERROR_NONE)
		return (Socket_Close(sock), FALSE);
	result = Socket_GetOption_Bool(sock, option);
	Socket_Close(sock);
	return (result == value);
}

//! SCENARIO: binds a socket to a loopback ephemeral port, and checks Socket_GetAddress() output
static
t_bool	scenario_bind_getaddress(void)
{
	s_sockaddr	local = SockAddr_LocalHost(SOCKAF_IPV4, PORT_ANY);
	s_sockaddr	bound = SOCKADDR_NULL;
	t_socket	sock = Socket_New(SOCKAF_IPV4, SOCKTYPE_STREAM, SOCKPROTO_TCP);
	t_bool		result;

	if (sock == SOCKET_INVALID)
		return (FALSE);
	if (Socket_Bind(sock, &local) != ERROR_NONE ||
		Socket_GetAddress(&bound, sock) != ERROR_NONE)
		return (Socket_Close(sock), FALSE);
	result = (bound.family == SOCKAF_IPV4
		&& bound.port != 0 // an actual ephemeral port was assigned
		&& bound.ip.ipv4[0] == 127); // and it is bound to the loopback interface
	Socket_Close(sock);
	return (result);
}

//! SCENARIO: checks that Socket_GetPeerAddress() of a connected client matches the server address
static
t_bool	scenario_getpeeraddress(void)
{
	s_tcp_echo_server	server;
	s_sockaddr	peer = SOCKADDR_NULL;
	t_socket	client;
	t_bool		result;

	if (tcp_echo_server_start(&server) != ERROR_NONE)
		return (FALSE);
	client = Socket_New(SOCKAF_IPV4, SOCKTYPE_STREAM, SOCKPROTO_TCP);
	if (client == SOCKET_INVALID)
		return (tcp_echo_server_stop(&server), FALSE);
	result = (Socket_Connect(client, &server.addr) == ERROR_NONE
		&& Socket_GetPeerAddress(&peer, client) == ERROR_NONE
		&& SockAddr_Equals(&peer, &server.addr));
	Socket_Close(client);
	tcp_echo_server_stop(&server);
	return (result);
}

//! SCENARIO: checks that, after the peer shuts down writing, Socket_Recv() returns `0` (EOF)
static
t_sintmax	scenario_shutdown_eof(void)
{
	s_tcp_echo_server	server;
	t_char		buffer[8];
	t_socket	client;
	t_sintmax	received = -1;

	if (tcp_echo_server_start(&server) != ERROR_NONE)
		return (-1);
	client = Socket_New(SOCKAF_IPV4, SOCKTYPE_STREAM, SOCKPROTO_TCP);
	if (client == SOCKET_INVALID)
		return (tcp_echo_server_stop(&server), -1);
	if (Socket_Connect(client, &server.addr) == ERROR_NONE &&
		Socket_Shutdown(client, SOCKSHUTDOWN_SEND) == ERROR_NONE)
	{	// our shutdown makes the echo server thread see EOF, echo nothing, and close:
		// so, in turn, our own recv() should cleanly observe EOF (a `0` return)
		received = Socket_Recv(client, buffer, sizeof(buffer), SOCKMSG_NONE);
	}
	Socket_Close(client);
	tcp_echo_server_stop(&server);
	return (received);
}

//! SCENARIO: sends a datagram between two loopback UDP sockets, returns the received payload
static
t_char*	scenario_udp_roundtrip(t_char const* message, t_bool check_from_addr)
{
	s_sockaddr	local = SockAddr_LocalHost(SOCKAF_IPV4, PORT_ANY);
	s_sockaddr	receiver_addr = SOCKADDR_NULL;
	s_sockaddr	from = SOCKADDR_NULL;
	t_char		buffer[SCENARIO_BUFFER] = {0};
	t_socket	receiver;
	t_socket	sender;
	t_sintmax	transferred;
	t_size		length = String_Length(message);

	receiver = Socket_New(SOCKAF_IPV4, SOCKTYPE_DGRAM, SOCKPROTO_UDP);
	sender   = Socket_New(SOCKAF_IPV4, SOCKTYPE_DGRAM, SOCKPROTO_UDP);
	if (receiver == SOCKET_INVALID || sender == SOCKET_INVALID)
		return (NULL);
	if (Socket_Bind(receiver, &local) != ERROR_NONE ||
		Socket_GetAddress(&receiver_addr, receiver) != ERROR_NONE)
	{
		Socket_Close(receiver);
		Socket_Close(sender);
		return (NULL);
	}
	transferred = Socket_SendTo(sender, message, length, SOCKMSG_NONE, &receiver_addr);
	if (transferred == (t_sintmax)length)
		transferred = Socket_RecvFrom(receiver, buffer, SCENARIO_BUFFER, SOCKMSG_NONE, &from);
	Socket_Close(receiver);
	Socket_Close(sender);
	if (transferred != (t_sintmax)length)
		return (NULL);
	if (check_from_addr && !(from.family == SOCKAF_IPV4 && from.ip.ipv4[0] == 127 && from.port != 0))
		return (NULL);
	return (String_Duplicate(buffer));
}



/*============================================================================*\
||                              Testing Functions                             ||
\*============================================================================*/



#ifndef c_sockaddrparse
void test_sockaddrparse(void)	{}
#warning "sockaddrparse() test suite function defined, but the function isn't defined."
#else
void	print_test_sockaddrparse(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str,
		t_port port)
{
	TEST_INIT(str)
	TEST_PERFORM_(result, scenario_sockaddr_roundtrip, str, port)
	test.expect = expecting;
	TEST_PRINT(str,	sockaddrparse, "str=\"%s\", port=%u", str, (unsigned)port)
	TEST_FREE()
}
void	test_sockaddrparse(void)
{
/*	| TEST FUNCTION          | TEST NAME                        |TESTFLAG| EXPECTING             | TEST ARGS			*/
	print_test_sockaddrparse("sockaddrparse (ipv4 loopback)     ",	FALSE,        "127.0.0.1:80", "127.0.0.1",       80);
	print_test_sockaddrparse("sockaddrparse (ipv4 any, no port) ",	FALSE,            "0.0.0.0" , "0.0.0.0",          0);
	print_test_sockaddrparse("sockaddrparse (ipv4 broadcast)    ",	FALSE, "255.255.255.255:65535", "255.255.255.255", 65535);
	print_test_sockaddrparse("sockaddrparse (ipv4 private)      ",	FALSE,   "192.168.1.42:8080", "192.168.1.42",   8080);
	print_test_sockaddrparse("sockaddrparse (ipv6 loopback)     ",	FALSE,           "[::1]:443", "::1",             443);
	print_test_sockaddrparse("sockaddrparse (ipv6 any, no port) ",	FALSE,                 "::", "::",                0);
	print_test_sockaddrparse("sockaddrparse (bad: out of range) ",	FALSE,                  NULL, "999.999.999.999",  80);
	print_test_sockaddrparse("sockaddrparse (bad: not an ip)    ",	FALSE,                  NULL, "not an ip",        80);
	print_test_sockaddrparse("sockaddrparse (bad: empty string) ",	FALSE,                  NULL, "",                 80);
	print_test_sockaddrparse("sockaddrparse (bad: half an ipv4) ",	FALSE,                  NULL, "127.0",            80);
}
#endif



#ifndef c_sockaddrtostr
void test_sockaddrtostr(void)	{}
#warning "sockaddrtostr() test suite function defined, but the function isn't defined."
#else
void	print_test_sockaddrtostr(char const* test_name, t_testflags flags,
		char const* expecting,
		s_sockaddr const* addr)
{
	TEST_INIT(str)
	TEST_PERFORM(	sockaddrtostr, addr)
	TEST_PRINT(str,	sockaddrtostr, "addr={ .family=%i, .port=%u }", (addr ? (int)addr->family : -1), (addr ? (unsigned)addr->port : 0))
	TEST_FREE()
}
void	test_sockaddrtostr(void)
{
	s_sockaddr localhost_http = SockAddr_LocalHost(SOCKAF_IPV4, 80);
	s_sockaddr any_https      = SockAddr_Any(SOCKAF_IPV4, 443);
	s_sockaddr ipv6_loopback  = sockaddr_ipv6_loopback(8080);
	s_sockaddr null_addr      = SOCKADDR_NULL;
/*	| TEST FUNCTION          | TEST NAME                        |TESTFLAG| EXPECTING             | TEST ARGS			*/
	print_test_sockaddrtostr("sockaddrtostr (ipv4 loopback)     ",	FALSE,        "127.0.0.1:80", &localhost_http);
	print_test_sockaddrtostr("sockaddrtostr (ipv4 any)          ",	FALSE,         "0.0.0.0:443", &any_https);
	print_test_sockaddrtostr("sockaddrtostr (ipv6 loopback)     ",	FALSE,          "[::1]:8080", &ipv6_loopback);
	print_test_sockaddrtostr("sockaddrtostr (unspecified family)",	FALSE,                  NULL, &null_addr);
	if (g_test.config.test_nullptrs)
	print_test_sockaddrtostr("sockaddrtostr (null address)      ",	FALSE,                  NULL, NULL);
}
#endif



#ifndef c_sockaddrequ
void test_sockaddrequals(void)	{}
#warning "sockaddrequals() test suite function defined, but the function isn't defined."
#else
void	print_test_sockaddrequals(char const* test_name, t_testflags flags,
		t_bool expecting,
		s_sockaddr const* addr1,
		s_sockaddr const* addr2)
{
	TEST_INIT(bool)
	TEST_PERFORM(	sockaddrequ, addr1, addr2)
	TEST_PRINT(bool,sockaddrequ, "addr1={ .family=%i, .port=%u }, addr2={ .family=%i, .port=%u }",
		(addr1 ? (int)addr1->family : -1), (addr1 ? (unsigned)addr1->port : 0),
		(addr2 ? (int)addr2->family : -1), (addr2 ? (unsigned)addr2->port : 0))
}
void	test_sockaddrequals(void)
{
	s_sockaddr localhost_80   = SockAddr_LocalHost(SOCKAF_IPV4, 80);
	s_sockaddr localhost_80_b = SockAddr_LocalHost(SOCKAF_IPV4, 80);
	s_sockaddr localhost_81   = SockAddr_LocalHost(SOCKAF_IPV4, 81);
	s_sockaddr any_80         = SockAddr_Any(SOCKAF_IPV4, 80);
	s_sockaddr ipv6_80        = sockaddr_ipv6_loopback(80);
	s_sockaddr ipv6_80_b      = sockaddr_ipv6_loopback(80);
/*	| TEST FUNCTION           | TEST NAME                        |TESTFLAG| EXPECTING | TEST ARGS			*/
	print_test_sockaddrequals("sockaddrequals (same ipv4)        ",	FALSE,       TRUE, &localhost_80, &localhost_80_b);
	print_test_sockaddrequals("sockaddrequals (same struct)      ",	FALSE,       TRUE, &localhost_80, &localhost_80);
	print_test_sockaddrequals("sockaddrequals (same ipv6)        ",	FALSE,       TRUE, &ipv6_80, &ipv6_80_b);
	print_test_sockaddrequals("sockaddrequals (different port)   ",	FALSE,      FALSE, &localhost_80, &localhost_81);
	print_test_sockaddrequals("sockaddrequals (different ip)     ",	FALSE,      FALSE, &localhost_80, &any_80);
	print_test_sockaddrequals("sockaddrequals (different family) ",	FALSE,      FALSE, &localhost_80, &ipv6_80);
}
#endif



//! Checks whether the running system supports creating IPv6 sockets at all
//! (containers and some CI runners are IPv4-only: IPv6-dependent tests are skipped there)
static
t_bool	test_ipv6_available(void)
{
	t_socket	sock = Socket_New(SOCKAF_IPV6, SOCKTYPE_STREAM, SOCKPROTO_TCP);

	if (sock == SOCKET_INVALID)
		return (FALSE);
	Socket_Close(sock);
	return (TRUE);
}

//! SCENARIO: creates (and closes) a socket, checking whether creation succeeds
static
t_bool	scenario_socket_new(e_sockaf family, e_socktype type, e_sockproto protocol)
{
	t_socket	sock = Socket_New(family, type, protocol);

	if (sock == SOCKET_INVALID)
		return (FALSE);
	Socket_Close(sock);
	return (TRUE);
}

#ifndef c_socknew
void test_socketnew(void)	{}
#warning "socketnew() test suite function defined, but the function isn't defined."
#else
void	print_test_socketnew(char const* test_name, t_testflags flags,
		t_bool expecting, // whether Socket_New() is expected to give a valid socket
		e_sockaf family,
		e_socktype type,
		e_sockproto protocol)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_socket_new, family, type, protocol)
	test.expect = expecting;
	TEST_PRINT(bool,socknew, "family=%i, type=%i, protocol=%i", (int)family, (int)type, (int)protocol)
}
void	test_socketnew(void)
{
/*	| TEST FUNCTION       | TEST NAME                     |TESTFLAG| EXPECTING | TEST ARGS			*/
	print_test_socketnew("socknew (tcp/ipv4)             ",	FALSE,       TRUE, SOCKAF_IPV4, SOCKTYPE_STREAM, SOCKPROTO_TCP);
	print_test_socketnew("socknew (udp/ipv4)             ",	FALSE,       TRUE, SOCKAF_IPV4, SOCKTYPE_DGRAM,  SOCKPROTO_UDP);
	if (test_ipv6_available())
	print_test_socketnew("socknew (tcp/ipv6)             ",	FALSE,       TRUE, SOCKAF_IPV6, SOCKTYPE_STREAM, SOCKPROTO_TCP);
	else printf("socknew (tcp/ipv6)              | (skipped: this system does not support IPv6 sockets)\n");
	print_test_socketnew("socknew (default protocol)     ",	FALSE,       TRUE, SOCKAF_IPV4, SOCKTYPE_STREAM, SOCKPROTO_DEFAULT);
	print_test_socketnew("socknew (bad: tcp over dgram)  ",	FALSE,      FALSE, SOCKAF_IPV4, SOCKTYPE_DGRAM,  SOCKPROTO_TCP);
}
#endif



void	print_test_socketscenario_bool(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_bool (*scenario)(void),
		char const* description)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario)
	test.expect = expecting;
	TEST_PRINT(bool,sockscenario, "%s", description)
}

//! Tests for Socket_SetOption_Bool()/Socket_GetOption_Bool()
void	print_test_socketoption(char const* test_name, t_testflags flags,
		t_bool expecting,
		e_sockopt option,
		t_bool value)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_option_roundtrip, option, value)
	test.expect = expecting;
	TEST_PRINT(bool,sockgetopt, "option=%i, value=%s", (int)option, (value ? "TRUE" : "FALSE"))
}
void	test_socketoption(void)
{
/*	| TEST FUNCTION          | TEST NAME                          |TESTFLAG| EXPECTING | TEST ARGS			*/
	print_test_socketoption("sockopt roundtrip (REUSEADDR on)    ",	FALSE,       TRUE, SOCKOPT_REUSEADDR, TRUE);
	print_test_socketoption("sockopt roundtrip (REUSEADDR off)   ",	FALSE,       TRUE, SOCKOPT_REUSEADDR, FALSE);
	print_test_socketoption("sockopt roundtrip (KEEPALIVE on)    ",	FALSE,       TRUE, SOCKOPT_KEEPALIVE, TRUE);
	print_test_socketoption("sockopt roundtrip (NODELAY on)      ",	FALSE,       TRUE, SOCKOPT_NODELAY,   TRUE);
}

//! Tests for the various stateful socket scenarios (bind/getaddress/getpeeraddress/shutdown)
void	test_socketscenarios(void)
{
	print_test_socketscenario_bool(
		"sockbind + sockgetaddr (loopback ephemeral)",	FALSE,
		TRUE, scenario_bind_getaddress, "bind to 127.0.0.1:PORT_ANY, then read back the assigned address");
	print_test_socketscenario_bool(
		"sockconnect + sockgetpeer                  ",	FALSE,
		TRUE, scenario_getpeeraddress, "connect to a loopback server, then check the peer address matches");
}



#ifndef c_sockrecv
void test_socketsendrecv(void)	{}
#warning "socketsendrecv() test suite function defined, but the function isn't defined."
#else
void	print_test_socketsendrecv(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* message)
{
	TEST_INIT(str)
	TEST_PERFORM_(result, scenario_tcp_echo, message)
	test.expect = expecting;
	TEST_PRINT(str,	sockrecv, "message=\"%s\" (over loopback TCP echo)", message)
	TEST_FREE()
}
void	print_test_socketshutdown(char const* test_name, t_testflags flags,
		t_sintmax expecting)
{
	TEST_INIT(sintmax)
	TEST_PERFORM_(result, scenario_shutdown_eof)
	test.expect = expecting;
	TEST_PRINT(sintmax,	sockrecv, "(recv() return value, after peer shutdown)")
}
void	test_socketsendrecv(void)
{
/*	| TEST FUNCTION             | TEST NAME                     |TESTFLAG| EXPECTING        | TEST ARGS			*/
	print_test_socketsendrecv("socksend/sockrecv (tcp echo)     ",	FALSE, "Hello, Socket!",  "Hello, Socket!");
	print_test_socketsendrecv("socksend/sockrecv (single char)  ",	FALSE,              "?",  "?");
	print_test_socketsendrecv("socksend/sockrecv (with spaces)  ",	FALSE, "  padded  text ", "  padded  text ");
	print_test_socketshutdown("sockrecv (eof after shutdown)    ",	FALSE, 0);
}
#endif



#ifndef c_sockrecvfrom
void test_socketudp(void)	{}
#warning "socketudp() test suite function defined, but the function isn't defined."
#else
void	print_test_socketudp(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* message,
		t_bool check_from_addr)
{
	TEST_INIT(str)
	TEST_PERFORM_(result, scenario_udp_roundtrip, message, check_from_addr)
	test.expect = expecting;
	TEST_PRINT(str,	sockrecvfrom, "message=\"%s\" (over loopback UDP), check_from=%s",
		message, (check_from_addr ? "TRUE" : "FALSE"))
	TEST_FREE()
}
void	test_socketudp(void)
{
/*	| TEST FUNCTION        | TEST NAME                          |TESTFLAG| EXPECTING       | TEST ARGS			*/
	print_test_socketudp("socksendto/sockrecvfrom (datagram)    ",	FALSE,  "ping datagram", "ping datagram", FALSE);
	print_test_socketudp("sockrecvfrom (fills sender address)   ",	FALSE,      "with addr", "with addr",     TRUE);
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/



int		testsuite_sys_socket(void)
{
	print_suite_title("libccc/sys/socket");

	if (Socket_Init() != ERROR_NONE)
		return (ERROR);

	test_sockaddrparse();
	test_sockaddrtostr();
	test_sockaddrequals();

	test_socketnew();
	test_socketoption();
	test_socketscenarios();
	test_socketsendrecv();
	test_socketudp();

	Socket_Exit();
	return (OK);
}
