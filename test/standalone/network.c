
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE	200809L	// needed to expose clock_gettime() and pthread types, in strict ISO C mode
#endif

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/sys/socket.h"
#include "libccc/sys/network.h"
#include "libccc/sys/thread.h"
#include "libccc/sys/async.h"

//! Returns a monotonic timestamp, in milliseconds (for measuring elapsed durations)
static t_s64	now_ms(void)
{
	struct timespec	ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((t_s64)ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

// === 1) TCP_Serve_Concurrent: N simultaneous slow clients ====================

#define T1_CLIENTS	4
#define T1_DELAY_MS	150

typedef struct test1
{
	t_mutex	mutex;
	int		handled;	// how many connections the server has fully handled
	t_port	port;
}	t1;

//! each handler sleeps, to prove that connections are handled concurrently
static t_bool	t1_handler(t_socket client, s_sockaddr const* addr, void* context)
{
	t1*		ctx = (t1*)context;
	char	buffer[16] = {0};
	t_bool	keep_running;
	(void)addr;

	Socket_Recv_All(client, buffer, 4);
	Thread_Sleep((s_nanotime){ .sec = 0, .nanosec = T1_DELAY_MS * 1000000 }); // simulate slow work
	Socket_Send_All(client, "pong", 4);
	Mutex_Lock(&ctx->mutex);
	ctx->handled += 1;
	Mutex_Unlock(&ctx->mutex);
	keep_running = (strncmp(buffer, "quit", 4) != 0);
	return (keep_running);
}

static void*	t1_client(void* arg)
{
	t1*			ctx = (t1*)arg;
	t_socket	sock = TCP_Connect("localhost", ctx->port);
	char		reply[8] = {0};

	assert(sock != SOCKET_INVALID);
	assert(Socket_Send_All(sock, "ping", 4) == ERROR_NONE);
	assert(Socket_Recv_All(sock, reply, 4) == 4);
	assert(strncmp(reply, "pong", 4) == 0);
	Socket_Close(sock);
	return (NULL);
}

static void*	t1_server(void* arg)
{
	t1*	ctx = (t1*)arg;
	s_sockaddr	addr = SockAddr_LocalHost(SOCKAF_IPV4, ctx->port);
	t_socket	listener = TCP_Listen(&addr, 8);

	assert(listener != SOCKET_INVALID);
	assert(TCP_Serve_Concurrent(listener, t1_handler, ctx) == ERROR_NONE);
	Socket_Close(listener);
	return (NULL);
}

static void	test_serve_concurrent(void)
{
	t1			ctx = {0};
	t_thread	server;
	t_thread	clients[T1_CLIENTS];
	s_sockaddr	probe;
	t_socket	quit_sock;
	char		reply[8] = {0};
	t_s64		t_start;
	t_s64		elapsed_ms;
	int	i;

	assert(Mutex_Init(&ctx.mutex) == ERROR_NONE);
	// pick a free ephemeral port first, then release it for the server thread to use
	{
		s_sockaddr	any = SockAddr_LocalHost(SOCKAF_IPV4, PORT_ANY);
		t_socket	tmp = TCP_Listen(&any, 1);
		assert(tmp != SOCKET_INVALID);
		assert(Socket_GetAddress(&probe, tmp) == ERROR_NONE);
		ctx.port = probe.port;
		Socket_Close(tmp);
	}
	assert(Thread_New(&server, t1_server, &ctx) == ERROR_NONE);
	Thread_Sleep((s_nanotime){ .sec = 0, .nanosec = 50 * 1000000 }); // give the server a moment to start listening
	// launch every client at once: with one thread per connection,
	// the total time should be ~1x the handler delay, not ~Nx
	t_start = now_ms();
	for (i = 0; i < T1_CLIENTS; ++i)
		assert(Thread_New(&clients[i], t1_client, &ctx) == ERROR_NONE);
	for (i = 0; i < T1_CLIENTS; ++i)
		assert(Thread_Join(clients[i], NULL) == ERROR_NONE);
	elapsed_ms = now_ms() - t_start;
	assert(elapsed_ms < (T1_DELAY_MS * T1_CLIENTS)); // proves the handlers ran concurrently
	// send the final "quit" connection: its handler returns FALSE, stopping the server
	quit_sock = TCP_Connect("127.0.0.1", ctx.port);
	assert(quit_sock != SOCKET_INVALID);
	assert(Socket_Send_All(quit_sock, "quit", 4) == ERROR_NONE);
	assert(Socket_Recv_All(quit_sock, reply, 4) == 4);
	Socket_Close(quit_sock);
	assert(Thread_Join(server, NULL) == ERROR_NONE); // the accept loop stopped gracefully
	assert(ctx.handled == T1_CLIENTS + 1); // every connection was fully handled before returning
	Mutex_Delete(&ctx.mutex);
	printf("TCP_Serve_Concurrent (%i simultaneous clients in %lims, graceful stop): OK\n",
		T1_CLIENTS, (long)elapsed_ms);
}

// === 2) async TCP: event-driven echo server + clients, single thread =========

#define T2_CLIENTS	3

typedef struct test2
{
	s_asyncloop*		loop;
	s_async_tcp_server	server;
	s_async_tcp			clients[T2_CLIENTS];
	int					connected;
	int					replies;
	int					server_conns;
}	t2;

//! server-side per-connection context (allocated on accept)
typedef struct t2_conn
{
	s_async_tcp	tcp;
	t2*			ctx;
}	t2_conn;

static void	t2_server_on_read(s_async_tcp* conn, t_u8 const* buffer, t_sintmax length)
{
	t2_conn*	sc = (t2_conn*)conn;

	if (length <= 0)
	{	// the client closed its side: close and free the server-side connection
		sc->ctx->server_conns -= 1;
		if (sc->ctx->server_conns == 0)
			AsyncTCP_Server_Stop(&sc->ctx->server); // all clients served: stop listening
		AsyncTCP_Close(conn);
		Memory_Free(sc);
		return;
	}
	assert(AsyncTCP_Write(conn, buffer, (t_size)length) == ERROR_NONE); // echo it back
}

static void	t2_on_accept(s_async_tcp_server* server, t_socket client, s_sockaddr const* addr)
{
	t2*			ctx = (t2*)server->data;
	t2_conn*	sc = (t2_conn*)Memory_New(sizeof(t2_conn));

	assert(sc != NULL);
	assert(addr->family == SOCKAF_IPV4 && addr->ip.ipv4[0] == 127);
	sc->ctx = ctx;
	ctx->server_conns += 1;
	assert(AsyncTCP_Init(ctx->loop, &sc->tcp, client) == ERROR_NONE);
	sc->tcp.data = sc;
	assert(AsyncTCP_StartRead(&sc->tcp, t2_server_on_read) == ERROR_NONE);
}

static void	t2_client_on_read(s_async_tcp* conn, t_u8 const* buffer, t_sintmax length)
{
	t2*		ctx = (t2*)conn->data;
	char	expected[32];

	assert(length > 0);
	snprintf(expected, sizeof(expected), "hello from client %li", (long)(conn - ctx->clients) % 10);
	assert((t_size)length == strlen(expected));
	assert(memcmp(buffer, expected, (t_size)length) == 0);
	ctx->replies += 1;
	AsyncTCP_Close(conn); // done: closing makes the server side receive EOF
}

static void	t2_client_on_connect(s_async_tcp* conn, e_cccerror error)
{
	t2*		ctx = (t2*)conn->data;
	char	message[32];

	assert(error == ERROR_NONE);
	ctx->connected += 1;
	snprintf(message, sizeof(message), "hello from client %li", (long)(conn - ctx->clients) % 10);
	assert(AsyncTCP_Write(conn, message, strlen(message)) == ERROR_NONE);
	assert(AsyncTCP_StartRead(conn, t2_client_on_read) == ERROR_NONE);
}

static void	test_async_tcp(void)
{
	t2			ctx = {0};
	s_sockaddr	addr = SockAddr_LocalHost(SOCKAF_IPV4, PORT_ANY);
	s_sockaddr	bound;
	int	i;

	ctx.loop = AsyncLoop_New();
	assert(ctx.loop != NULL);
	assert(AsyncTCP_Listen(ctx.loop, &ctx.server, &addr, 8, t2_on_accept) == ERROR_NONE);
	ctx.server.data = &ctx;
	assert(Socket_GetAddress(&bound, ctx.server.socket) == ERROR_NONE);
	for (i = 0; i < T2_CLIENTS; ++i)
	{
		s_sockaddr	target = SockAddr_LocalHost(SOCKAF_IPV4, bound.port);
		assert(AsyncTCP_Connect(ctx.loop, &ctx.clients[i], &target, t2_client_on_connect) == ERROR_NONE);
		ctx.clients[i].data = &ctx;
	}
	// a single AsyncLoop_Run() call drives the server AND all clients, on one thread
	assert(AsyncLoop_Run(ctx.loop, ASYNCRUN_DEFAULT) == FALSE);
	assert(ctx.connected == T2_CLIENTS);
	assert(ctx.replies == T2_CLIENTS);
	assert(ctx.server_conns == 0);
	assert(AsyncLoop_Delete(&ctx.loop) == ERROR_NONE);
	printf("async TCP (event-driven echo server + %i clients on one loop): OK\n", T2_CLIENTS);
}

// === 3) async TCP: write backpressure (large buffered write) =================

#define T3_TOTAL_BYTES	(4 * 1024 * 1024) // large enough to overflow the socket send buffer

typedef struct test3
{
	s_asyncloop*		loop;
	s_async_tcp_server	server;
	s_async_tcp			client;
	s_async_tcp			server_conn;
	t_size				received;
	t_bool				got_ok;
}	t3;

static void	t3_server_on_read(s_async_tcp* conn, t_u8 const* buffer, t_sintmax length)
{
	t3*	ctx = (t3*)conn->data;
	(void)buffer;

	if (length <= 0)
	{
		AsyncTCP_Close(conn);
		return;
	}
	ctx->received += (t_size)length;
	if (ctx->received == T3_TOTAL_BYTES)
	{	// everything arrived intact: acknowledge, and stop the server
		assert(AsyncTCP_Write(conn, "OK", 2) == ERROR_NONE);
		AsyncTCP_Server_Stop(&ctx->server);
	}
}

static void	t3_on_accept(s_async_tcp_server* server, t_socket client, s_sockaddr const* addr)
{
	t3*	ctx = (t3*)server->data;
	(void)addr;

	assert(AsyncTCP_Init(ctx->loop, &ctx->server_conn, client) == ERROR_NONE);
	ctx->server_conn.data = ctx;
	assert(AsyncTCP_StartRead(&ctx->server_conn, t3_server_on_read) == ERROR_NONE);
}

static void	t3_client_on_read(s_async_tcp* conn, t_u8 const* buffer, t_sintmax length)
{
	t3*	ctx = (t3*)conn->data;

	if (length <= 0)
	{
		AsyncTCP_Close(conn);
		return;
	}
	assert(length == 2 && memcmp(buffer, "OK", 2) == 0);
	ctx->got_ok = TRUE;
	AsyncTCP_Close(conn); // makes the server-side connection receive EOF
}

static void	t3_client_on_connect(s_async_tcp* conn, e_cccerror error)
{
	t_u8*	blob;
	t_size	i;

	assert(error == ERROR_NONE);
	blob = (t_u8*)Memory_New(T3_TOTAL_BYTES);
	assert(blob != NULL);
	for (i = 0; i < T3_TOTAL_BYTES; ++i)
		blob[i] = (t_u8)(i * 2654435761u >> 24); // filler pattern
	// this single write vastly exceeds the socket send buffer: the remainder
	// gets queued internally, and flushed by the loop as the socket drains
	assert(AsyncTCP_Write(conn, blob, T3_TOTAL_BYTES) == ERROR_NONE);
	Memory_Free(blob); // safe immediately: AsyncTCP_Write copies what it queues
	assert(AsyncTCP_StartRead(conn, t3_client_on_read) == ERROR_NONE);
}

static void	test_async_tcp_backpressure(void)
{
	t3			ctx = {0};
	s_sockaddr	addr = SockAddr_LocalHost(SOCKAF_IPV4, PORT_ANY);
	s_sockaddr	bound;
	s_sockaddr	target;

	ctx.loop = AsyncLoop_New();
	assert(ctx.loop != NULL);
	assert(AsyncTCP_Listen(ctx.loop, &ctx.server, &addr, 1, t3_on_accept) == ERROR_NONE);
	ctx.server.data = &ctx;
	assert(Socket_GetAddress(&bound, ctx.server.socket) == ERROR_NONE);
	target = SockAddr_LocalHost(SOCKAF_IPV4, bound.port);
	assert(AsyncTCP_Connect(ctx.loop, &ctx.client, &target, t3_client_on_connect) == ERROR_NONE);
	ctx.client.data = &ctx;
	assert(AsyncLoop_Run(ctx.loop, ASYNCRUN_DEFAULT) == FALSE);
	assert(ctx.received == T3_TOTAL_BYTES); // every byte made it through the write queue
	assert(ctx.got_ok == TRUE);
	assert(AsyncLoop_Delete(&ctx.loop) == ERROR_NONE);
	printf("async TCP write backpressure (%i MB through the write queue): OK\n",
		T3_TOTAL_BYTES / (1024 * 1024));
}

// === 4) async UDP: event-driven ping-pong ====================================

typedef struct test4
{
	s_async_udp	peer1;
	s_async_udp	peer2;
	s_sockaddr	addr1;
	s_sockaddr	addr2;
	int			pings;
	int			pongs;
}	t4;

#define T4_ROUNDS	3

static void	t4_peer2_on_recv(s_async_udp* udp, t_u8 const* buffer, t_size length, s_sockaddr const* from)
{
	t4*	ctx = (t4*)udp->data;

	assert(length == 4 && memcmp(buffer, "ping", 4) == 0);
	assert(from->family == SOCKAF_IPV4 && from->ip.ipv4[0] == 127);
	ctx->pings += 1;
	assert(Socket_SendTo(udp->socket, "pong", 4, SOCKMSG_NONE, from) == 4); // reply to the sender
}

static void	t4_peer1_on_recv(s_async_udp* udp, t_u8 const* buffer, t_size length, s_sockaddr const* from)
{
	t4*	ctx = (t4*)udp->data;
	(void)from;

	assert(length == 4 && memcmp(buffer, "pong", 4) == 0);
	ctx->pongs += 1;
	if (ctx->pongs < T4_ROUNDS)
		assert(Socket_SendTo(udp->socket, "ping", 4, SOCKMSG_NONE, &ctx->addr2) == 4);
	else
	{	// closing both handles leaves the loop with nothing to do: it exits
		AsyncUDP_Close(&ctx->peer1);
		AsyncUDP_Close(&ctx->peer2);
	}
}

static void	test_async_udp(void)
{
	s_asyncloop*	loop = AsyncLoop_New();
	s_sockaddr	any = SockAddr_LocalHost(SOCKAF_IPV4, PORT_ANY);
	t4	ctx = {0};

	assert(loop != NULL);
	assert(AsyncUDP_Init(loop, &ctx.peer1, UDP_New(&any)) == ERROR_NONE);
	assert(AsyncUDP_Init(loop, &ctx.peer2, UDP_New(&any)) == ERROR_NONE);
	ctx.peer1.data = &ctx;
	ctx.peer2.data = &ctx;
	assert(Socket_GetAddress(&ctx.addr1, ctx.peer1.socket) == ERROR_NONE);
	assert(Socket_GetAddress(&ctx.addr2, ctx.peer2.socket) == ERROR_NONE);
	assert(AsyncUDP_StartRecv(&ctx.peer1, t4_peer1_on_recv) == ERROR_NONE);
	assert(AsyncUDP_StartRecv(&ctx.peer2, t4_peer2_on_recv) == ERROR_NONE);
	assert(Socket_SendTo(ctx.peer1.socket, "ping", 4, SOCKMSG_NONE, &ctx.addr2) == 4); // kick off the exchange
	assert(AsyncLoop_Run(loop, ASYNCRUN_DEFAULT) == FALSE);
	assert(ctx.pings == T4_ROUNDS && ctx.pongs == T4_ROUNDS);
	assert(AsyncLoop_Delete(&loop) == ERROR_NONE);
	printf("async UDP (event-driven ping-pong, %i rounds): OK\n", T4_ROUNDS);
}

// === 5) async DNS resolution, on the loop's thread pool ======================

typedef struct test5
{
	int			callbacks;
	t_bool		found_loopback;
	t_bool		bad_host_failed;
}	t5;

static void	t5_on_resolved(s_async_resolve* resolve, e_cccerror error, s_sockaddr const* addresses, t_uint amount)
{
	t5*	ctx = (t5*)resolve->data;
	t_uint	i;

	ctx->callbacks += 1;
	assert(error == ERROR_NONE && addresses != NULL && amount >= 1);
	for (i = 0; i < amount; ++i)
	{
		assert(addresses[i].port == 4242);
		if ((addresses[i].family == SOCKAF_IPV4 && addresses[i].ip.ipv4[0] == 127) ||
			(addresses[i].family == SOCKAF_IPV6 && addresses[i].ip.ipv6[15] == 1))
			ctx->found_loopback = TRUE;
	}
}

static void	t5_on_failed(s_async_resolve* resolve, e_cccerror error, s_sockaddr const* addresses, t_uint amount)
{
	t5*	ctx = (t5*)resolve->data;

	ctx->callbacks += 1;
	assert(error != ERROR_NONE && addresses == NULL && amount == 0);
	ctx->bad_host_failed = TRUE;
}

static void	test_async_resolve(void)
{
	s_asyncloop*	loop = AsyncLoop_New();
	s_async_resolve	ok_request;
	s_async_resolve	bad_request;
	t5	ctx = {0};

	assert(loop != NULL);
	assert(Network_Resolve_Async(loop, &ok_request, "localhost", 4242, t5_on_resolved) == ERROR_NONE);
	ok_request.data = &ctx;
	assert(Network_Resolve_Async(loop, &bad_request, "no.such.host.invalid", 4242, t5_on_failed) == ERROR_NONE);
	bad_request.data = &ctx;
	// both DNS lookups run on the loop's worker pool; callbacks land on the loop thread
	assert(AsyncLoop_Run(loop, ASYNCRUN_DEFAULT) == FALSE);
	assert(ctx.callbacks == 2);
	assert(ctx.found_loopback == TRUE);
	assert(ctx.bad_host_failed == TRUE);
	assert(AsyncLoop_Delete(&loop) == ERROR_NONE);
	printf("async DNS resolution (thread pool getaddrinfo, success + failure): OK\n");
}

// =============================================================================

int	main(void)
{
	assert(Socket_Init() == ERROR_NONE);
	test_serve_concurrent();
	test_async_tcp();
	test_async_tcp_backpressure();
	test_async_udp();
	test_async_resolve();
	assert(Socket_Exit() == ERROR_NONE);
	printf("\nAll network tests passed!\n");
	return (0);
}
