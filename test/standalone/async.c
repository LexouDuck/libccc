
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include "libccc.h"
#include "libccc/sys/thread.h"
#include "libccc/sys/async.h"

// === 1) timers: one-shot ordering + repeat ===================================

typedef struct test1 { int order[8]; int count; int repeats; } t1;

static void	t1_first(s_async_timer* timer)
{ t1* ctx = timer->base.data; ctx->order[ctx->count++] = 1; }
static void	t1_second(s_async_timer* timer)
{ t1* ctx = timer->base.data; ctx->order[ctx->count++] = 2; }
static void	t1_third(s_async_timer* timer)
{ t1* ctx = timer->base.data; ctx->order[ctx->count++] = 3; }

static void	t1_repeater(s_async_timer* timer)
{
	t1* ctx = timer->base.data;
	ctx->repeats += 1;
	if (ctx->repeats == 3)
		AsyncTimer_Stop(timer); // stop the repeating timer from within its own callback
}

static void	test_timers(void)
{
	s_asyncloop*	loop = AsyncLoop_New();
	s_async_timer	timer1, timer2, timer3, repeater;
	t1				ctx = {0};
	t_asynctime		start, elapsed;

	assert(loop != NULL);
	// start in shuffled order, with deadlines requiring re-ordering
	assert(AsyncTimer_Init(loop, &timer2) == ERROR_NONE); timer2.base.data = &ctx;
	assert(AsyncTimer_Init(loop, &timer3) == ERROR_NONE); timer3.base.data = &ctx;
	assert(AsyncTimer_Init(loop, &timer1) == ERROR_NONE); timer1.base.data = &ctx;
	assert(AsyncTimer_Init(loop, &repeater) == ERROR_NONE); repeater.base.data = &ctx;
	assert(AsyncTimer_Start(&timer2, t1_second, 40, 0) == ERROR_NONE);
	assert(AsyncTimer_Start(&timer3, t1_third,  60, 0) == ERROR_NONE);
	assert(AsyncTimer_Start(&timer1, t1_first,  20, 0) == ERROR_NONE);
	assert(AsyncTimer_Start(&repeater, t1_repeater, 10, 15) == ERROR_NONE);
	assert(AsyncLoop_IsAlive(loop) == TRUE);
	start = AsyncLoop_Now(loop);
	assert(AsyncLoop_Run(loop, ASYNCRUN_DEFAULT) == FALSE); // runs until all timers are done
	elapsed = AsyncLoop_Now(loop) - start;
	assert(ctx.count == 3);
	assert(ctx.order[0] == 1 && ctx.order[1] == 2 && ctx.order[2] == 3); // fired in deadline order
	assert(ctx.repeats == 3); // the repeating timer fired exactly 3 times
	assert(elapsed >= 60); // the loop ran for at least as long as the largest deadline
	assert(AsyncLoop_IsAlive(loop) == FALSE);
	assert(AsyncLoop_Delete(&loop) == ERROR_NONE && loop == NULL);
	printf("timers (one-shot ordering, repeat, stop-from-callback): OK\n");
}

// === 2) idle handles + AsyncLoop_Stop ========================================

static void	t2_idle_cb(s_async_idle* idle)
{
	int* count = idle->base.data;
	*count += 1;
	if (*count == 5)
		AsyncLoop_Stop(idle->base.loop); // idle handles keep the loop alive: stop it manually
}

static void	test_idle(void)
{
	s_asyncloop*	loop = AsyncLoop_New();
	s_async_idle	idle;
	int				count = 0;

	assert(loop != NULL);
	assert(AsyncIdle_Init(loop, &idle) == ERROR_NONE);
	idle.base.data = &count;
	assert(AsyncIdle_Start(&idle, t2_idle_cb) == ERROR_NONE);
	assert(AsyncHandle_IsActive((s_asynchandle*)&idle) == TRUE);
	assert(AsyncLoop_Run(loop, ASYNCRUN_DEFAULT) == TRUE); // TRUE: the idle handle is still active
	assert(count == 5); // ran exactly once per iteration, until AsyncLoop_Stop
	assert(AsyncIdle_Stop(&idle) == ERROR_NONE);
	assert(AsyncHandle_IsActive((s_asynchandle*)&idle) == FALSE);
	assert(AsyncLoop_Delete(&loop) == ERROR_NONE);
	printf("idle handles + AsyncLoop_Stop: OK\n");
}

// === 3) cross-thread event send (wakes a blocked loop) =======================

typedef struct t3 { s_async_event event; int fired; t_asynctime sent_at; } t3;

static void	t3_event_cb(s_async_event* event)
{
	t3* ctx = (t3*)event; // (the event is the first member of t3: struct-embedding, libuv style)
	ctx->fired += 1;
	AsyncEvent_Stop(event); // deactivate: lets the loop terminate
}

static void*	t3_sender_thread(void* arg)
{
	t3* ctx = arg;
	Thread_Sleep((s_nanotime){ .sec=0, .nanosec=50 * 1000 * 1000 }); // 50ms: the loop will be blocked, polling
	AsyncEvent_Send(&ctx->event); // thread-safe wakeup
	AsyncEvent_Send(&ctx->event); // sent twice: must coalesce into a single callback invocation
	return (NULL);
}

static void	test_event(void)
{
	s_asyncloop*	loop = AsyncLoop_New();
	t3				ctx = {0};
	t_thread		sender;

	assert(loop != NULL);
	assert(AsyncEvent_Init(loop, &ctx.event, t3_event_cb) == ERROR_NONE);
	assert(AsyncHandle_IsActive((s_asynchandle*)&ctx.event) == TRUE); // active from init (like uv_async_t)
	assert(Thread_New(&sender, t3_sender_thread, &ctx) == ERROR_NONE);
	assert(AsyncLoop_Run(loop, ASYNCRUN_DEFAULT) == FALSE); // blocks (no timers!) until woken by the other thread
	assert(ctx.fired == 1); // coalesced: fired exactly once despite two sends
	assert(Thread_Join(sender, NULL) == ERROR_NONE);
	assert(AsyncLoop_Delete(&loop) == ERROR_NONE);
	printf("cross-thread event send (blocked-loop wakeup + coalescing): OK\n");
}

// === 4) poll handle on a pipe ================================================

typedef struct t4 { t_fd pipefd[2]; s_async_poll poll; s_async_timer writer; int reads; char received[64]; } t4;

static void	t4_writer_cb(s_async_timer* timer)
{
	t4* ctx = timer->base.data;
	assert(write(ctx->pipefd[1], "hello", 5) == 5);
}

static void	t4_poll_cb(s_async_poll* poll, t_asyncpoll_events events)
{
	t4* ctx = poll->base.data;
	assert(events & ASYNCPOLL_READABLE);
	ctx->reads = (int)read(ctx->pipefd[0], ctx->received, sizeof(ctx->received));
	AsyncPoll_Stop(poll);
}

static void	test_poll(void)
{
	s_asyncloop*	loop = AsyncLoop_New();
	t4				ctx = {0};

	assert(loop != NULL);
	assert(pipe(ctx.pipefd) == 0);
	assert(AsyncPoll_Init(loop, &ctx.poll, ctx.pipefd[0]) == ERROR_NONE);
	ctx.poll.base.data = &ctx;
	assert(AsyncPoll_Start(&ctx.poll, ASYNCPOLL_READABLE, t4_poll_cb) == ERROR_NONE);
	assert(AsyncTimer_Init(loop, &ctx.writer) == ERROR_NONE);
	ctx.writer.base.data = &ctx;
	assert(AsyncTimer_Start(&ctx.writer, t4_writer_cb, 30, 0) == ERROR_NONE);
	assert(AsyncLoop_Run(loop, ASYNCRUN_DEFAULT) == FALSE);
	assert(ctx.reads == 5);
	assert(ctx.received[0] == 'h' && ctx.received[4] == 'o');
	close(ctx.pipefd[0]);
	close(ctx.pipefd[1]);
	assert(AsyncLoop_Delete(&loop) == ERROR_NONE);
	printf("poll handle (fd readability via pipe): OK\n");
}

// === 5) thread pool work =====================================================

#define N_WORK	16

typedef struct t5_item { s_async_work work; int input; int output; t_thread worker; t_bool done_ran; } t5_item;
typedef struct t5 { t5_item items[N_WORK]; int done_count; t_thread loop_thread; } t5;

static void	t5_work_cb(s_async_work* work) // runs on a pool thread
{
	t5_item* item = (t5_item*)work;
	item->worker = Thread_Self();
	item->output = item->input * item->input;
	Thread_Sleep((s_nanotime){ .sec=0, .nanosec=5 * 1000 * 1000 }); // simulate 5ms of blocking work
}

static void	t5_done_cb(s_async_work* work) // runs on the loop thread
{
	t5_item*	item = (t5_item*)work;
	t5*			ctx = work->base.data;

	assert(Thread_Equals(Thread_Self(), ctx->loop_thread) == TRUE); // `done` runs on the loop thread
	assert(Thread_Equals(item->worker, ctx->loop_thread) == FALSE); // `work` ran on a pool thread
	item->done_ran = TRUE;
	ctx->done_count += 1;
}

static void	test_work(void)
{
	s_asyncloop*	loop = AsyncLoop_New();
	static t5		ctx = {0};

	assert(loop != NULL);
	ctx.loop_thread = Thread_Self();
	for (int i = 0; i < N_WORK; ++i)
	{
		ctx.items[i].input = i;
		ctx.items[i].work.base.data = &ctx;
		assert(AsyncWork_Submit(loop, &ctx.items[i].work, t5_work_cb, t5_done_cb) == ERROR_NONE);
	}
	assert(AsyncLoop_IsAlive(loop) == TRUE); // pending work keeps the loop alive
	assert(AsyncLoop_Run(loop, ASYNCRUN_DEFAULT) == FALSE); // runs until all work is done
	assert(ctx.done_count == N_WORK);
	for (int i = 0; i < N_WORK; ++i)
	{
		assert(ctx.items[i].done_ran == TRUE);
		assert(ctx.items[i].output == i * i);
	}
	assert(AsyncLoop_Delete(&loop) == ERROR_NONE);
	printf("thread pool work (%d items, done-callbacks on loop thread): OK\n", N_WORK);
}

// === 6) run modes: ONCE / NOWAIT =============================================

static void	t6_noop(s_async_timer* timer) { int* n = timer->base.data; *n += 1; }

static void	test_runmodes(void)
{
	s_asyncloop*	loop = AsyncLoop_New();
	s_async_timer	timer;
	int				fired = 0;

	assert(loop != NULL);
	assert(AsyncTimer_Init(loop, &timer) == ERROR_NONE);
	timer.base.data = &fired;
	assert(AsyncTimer_Start(&timer, t6_noop, 20, 0) == ERROR_NONE);
	// NOWAIT: does not block; the 20ms timer is not yet due
	assert(AsyncLoop_Run(loop, ASYNCRUN_NOWAIT) == TRUE);
	assert(fired == 0);
	// ONCE: blocks (in poll) until the timer is due, then fires it
	assert(AsyncLoop_Run(loop, ASYNCRUN_ONCE) == FALSE);
	assert(fired == 1);
	assert(AsyncLoop_Delete(&loop) == ERROR_NONE);
	printf("run modes (NOWAIT non-blocking, ONCE fires due timer): OK\n");
}

// === 7) generic handle functions + detach ====================================

static void	test_handles(void)
{
	s_asyncloop*	loop = AsyncLoop_New();
	s_async_timer	timer;
	s_async_idle	idle;

	assert(loop != NULL);
	assert(AsyncTimer_Init(loop, &timer) == ERROR_NONE);
	assert(AsyncTimer_Start(&timer, t6_noop, 1000, 0) == ERROR_NONE);
	assert(AsyncIdle_Init(loop, &idle) == ERROR_NONE);
	assert(AsyncHandle_Stop((s_asynchandle*)&timer) == ERROR_NONE); // generic stop, dispatched by kind
	assert(AsyncHandle_IsActive((s_asynchandle*)&timer) == FALSE);
	assert(AsyncLoop_IsAlive(loop) == FALSE);
	assert(AsyncHandle_Detach((s_asynchandle*)&timer) == ERROR_NONE);
	assert(AsyncHandle_Detach((s_asynchandle*)&idle) == ERROR_NONE);
	// error paths (messages printed to stderr are expected):
	assert(AsyncHandle_Detach((s_asynchandle*)&timer) == ERROR_INVALIDARGS); // already detached
	assert(AsyncTimer_Start(&timer, t6_noop, 0, 0) == ERROR_INVALIDARGS); // detached: no longer initialized
	assert(AsyncLoop_Run(NULL, ASYNCRUN_DEFAULT) == FALSE);
	assert(AsyncLoop_Delete(&loop) == ERROR_NONE);
	printf("generic handle stop/detach + error paths: OK\n");
}

int	main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	test_timers();
	test_idle();
	test_event();
	test_poll();
	test_work();
	test_runmodes();
	test_handles();
	printf("\nAll libccc/sys/async tests passed!\n");
	return (0);
}
