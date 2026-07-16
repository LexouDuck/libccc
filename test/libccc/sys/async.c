
#if !defined(_WIN32)
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE	200809L
	#endif
	#include <unistd.h>	// (only used by the poll handle scenario test, which needs `pipe()`)
#endif

#include "libccc.h"
#include "libccc/bool.h"
#include "libccc/sys/thread.h"
#include "libccc/sys/async.h"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                              Scenario Functions                            ||
\*============================================================================*/

/*
**	The async API functions cannot be tested in isolation with simple
**	input/expected-output comparisons: instead, each test below runs a small
**	event-loop "scenario" function, whose final observable result is
**	deterministic, and is compared against the expected value, using the
**	usual test suite machinery.
*/



//! shared by the timer-ordering scenario: each timer callback appends its digit to the result
typedef struct asynctest_order
{
	t_u64	result;
	t_uint	repeats;
}	s_asynctest_order;

static void	asynctest_timer_1(s_async_timer* timer)
{ s_asynctest_order* ctx = timer->base.data; ctx->result = ctx->result * 10 + 1; }
static void	asynctest_timer_2(s_async_timer* timer)
{ s_asynctest_order* ctx = timer->base.data; ctx->result = ctx->result * 10 + 2; }
static void	asynctest_timer_3(s_async_timer* timer)
{ s_asynctest_order* ctx = timer->base.data; ctx->result = ctx->result * 10 + 3; }

//! AsyncTimer_Start(): one-shot timers fire in order of their deadlines (regardless of start order)
static t_u64	scenario_async_timer_order(void)
{
	s_asyncloop*		loop = AsyncLoop_New();
	s_async_timer		timer1;
	s_async_timer		timer2;
	s_async_timer		timer3;
	s_asynctest_order	ctx = {0};

	if (loop == NULL)
		return (0);
	if (AsyncTimer_Init(loop, &timer2) != ERROR_NONE ||
		AsyncTimer_Init(loop, &timer3) != ERROR_NONE ||
		AsyncTimer_Init(loop, &timer1) != ERROR_NONE)
		return (0);
	timer1.base.data = &ctx;
	timer2.base.data = &ctx;
	timer3.base.data = &ctx;
	// started in shuffled order: the deadlines are what determines the callback order
	if (AsyncTimer_Start(&timer2, asynctest_timer_2, 40, 0) != ERROR_NONE ||
		AsyncTimer_Start(&timer3, asynctest_timer_3, 60, 0) != ERROR_NONE ||
		AsyncTimer_Start(&timer1, asynctest_timer_1, 20, 0) != ERROR_NONE)
		return (0);
	AsyncLoop_Run(loop, ASYNCRUN_DEFAULT); // runs until all one-shot timers have fired
	AsyncLoop_Delete(&loop);
	return (ctx.result); // expected: 123
}



static void	asynctest_timer_repeat(s_async_timer* timer)
{
	s_asynctest_order*	ctx = timer->base.data;

	ctx->repeats += 1;
	if (ctx->repeats == 3)
		AsyncTimer_Stop(timer); // a repeating timer can stop itself from within its own callback
}

//! AsyncTimer_Start() with `repeat`: the timer re-fires at its repeat interval, until stopped
static t_u64	scenario_async_timer_repeat(void)
{
	s_asyncloop*		loop = AsyncLoop_New();
	s_async_timer		repeater;
	s_asynctest_order	ctx = {0};

	if (loop == NULL)
		return (0);
	if (AsyncTimer_Init(loop, &repeater) != ERROR_NONE)
		return (0);
	repeater.base.data = &ctx;
	if (AsyncTimer_Start(&repeater, asynctest_timer_repeat, 10, 15) != ERROR_NONE)
		return (0);
	AsyncLoop_Run(loop, ASYNCRUN_DEFAULT);
	AsyncLoop_Delete(&loop);
	return (ctx.repeats); // expected: 3
}



static void	asynctest_idle(s_async_idle* idle)
{
	t_u64*	count = idle->base.data;

	*count += 1;
	if (*count == 5)
		AsyncLoop_Stop(idle->base.loop); // idle handles keep the loop alive forever: stop it manually
}

//! AsyncIdle_Start()/AsyncLoop_Stop(): the idle callback runs exactly once per loop iteration
static t_u64	scenario_async_idle(void)
{
	s_asyncloop*	loop = AsyncLoop_New();
	s_async_idle	idle;
	t_u64			count = 0;

	if (loop == NULL)
		return (0);
	if (AsyncIdle_Init(loop, &idle) != ERROR_NONE)
		return (0);
	idle.base.data = &count;
	if (AsyncIdle_Start(&idle, asynctest_idle) != ERROR_NONE)
		return (0);
	AsyncLoop_Run(loop, ASYNCRUN_DEFAULT); // stopped by the idle callback, after 5 iterations
	AsyncLoop_Delete(&loop);
	return (count); // expected: 5
}



//! shared by the cross-thread event scenario
typedef struct asynctest_event
{
	s_async_event	event;	//!< (first member: this struct can be cast to/from `s_async_event*`, libuv-style)
	t_u64			fired;
}	s_asynctest_event;

static void	asynctest_event_callback(s_async_event* event)
{
	s_asynctest_event*	ctx = (s_asynctest_event*)event;

	ctx->fired += 1;
	AsyncEvent_Stop(event); // deactivate: lets the loop terminate
}

static void*	asynctest_event_sender(void* arg)
{
	s_asynctest_event*	ctx = arg;

	Thread_Sleep((s_nanotime){ .sec=0, .nanosec=50 * 1000 * 1000 }); // 50ms: the loop will be blocked, polling for I/O
	AsyncEvent_Send(&ctx->event); // thread-safe wakeup
	AsyncEvent_Send(&ctx->event); // sent twice: must coalesce into a single callback invocation
	return (NULL);
}

//! AsyncEvent_Send(): wakes up a blocked event loop from another thread, and coalesces multiple sends
static t_u64	scenario_async_event(void)
{
	s_asyncloop*		loop = AsyncLoop_New();
	s_asynctest_event	ctx = {0};
	t_thread			sender;

	if (loop == NULL)
		return (0);
	if (AsyncEvent_Init(loop, &ctx.event, asynctest_event_callback) != ERROR_NONE)
		return (0);
	if (Thread_New(&sender, asynctest_event_sender, &ctx) != ERROR_NONE)
		return (0);
	AsyncLoop_Run(loop, ASYNCRUN_DEFAULT); // blocks (there are no timers!) until woken up by the sender thread
	Thread_Join(sender, NULL);
	AsyncLoop_Delete(&loop);
	return (ctx.fired); // expected: 1 (coalesced, despite two sends)
}



#if !defined(_WIN32) // (poll handles are not yet supported by the Windows event loop backend)

//! shared by the fd-polling scenario
typedef struct asynctest_poll
{
	t_fd			pipefd[2];
	s_async_poll	poll;
	s_async_timer	writer;
	t_u64			bytes_read;
}	s_asynctest_poll;

static void	asynctest_poll_writer(s_async_timer* timer)
{
	s_asynctest_poll*	ctx = timer->base.data;
	t_size				written;

	written = (t_size)write(ctx->pipefd[1], "hello", 5);
	(void)written;
}

static void	asynctest_poll_callback(s_async_poll* poll, t_asyncpoll_events events)
{
	s_asynctest_poll*	ctx = poll->base.data;
	char				buffer[64];

	if (events & ASYNCPOLL_READABLE)
		ctx->bytes_read += (t_u64)read(ctx->pipefd[0], buffer, sizeof(buffer));
	AsyncPoll_Stop(poll);
}

//! AsyncPoll_Start(): the poll callback fires when the watched file descriptor becomes readable
static t_u64	scenario_async_poll(void)
{
	s_asyncloop*		loop = AsyncLoop_New();
	s_asynctest_poll	ctx = {0};

	if (loop == NULL)
		return (0);
	if (pipe(ctx.pipefd) != 0)
		return (0);
	if (AsyncPoll_Init(loop, &ctx.poll, ctx.pipefd[0]) != ERROR_NONE)
		return (0);
	ctx.poll.base.data = &ctx;
	if (AsyncPoll_Start(&ctx.poll, ASYNCPOLL_READABLE, asynctest_poll_callback) != ERROR_NONE)
		return (0);
	if (AsyncTimer_Init(loop, &ctx.writer) != ERROR_NONE)
		return (0);
	ctx.writer.base.data = &ctx;
	if (AsyncTimer_Start(&ctx.writer, asynctest_poll_writer, 30, 0) != ERROR_NONE) // the pipe becomes readable after 30ms
		return (0);
	AsyncLoop_Run(loop, ASYNCRUN_DEFAULT);
	close(ctx.pipefd[0]);
	close(ctx.pipefd[1]);
	AsyncLoop_Delete(&loop);
	return (ctx.bytes_read); // expected: 5
}

#endif



#define ASYNCTEST_WORK_AMOUNT	16

//! shared by the thread pool scenario
typedef struct asynctest_work_item
{
	s_async_work	work;	//!< (first member: this struct can be cast to/from `s_async_work*`, libuv-style)
	t_u64			input;
	t_u64			output;
	t_thread		worker;
}	s_asynctest_work_item;

typedef struct asynctest_work
{
	s_asynctest_work_item	items[ASYNCTEST_WORK_AMOUNT];
	t_u64					correct;
	t_thread				loop_thread;
}	s_asynctest_work;

static void	asynctest_work_callback(s_async_work* work) // runs on a worker pool thread
{
	s_asynctest_work_item*	item = (s_asynctest_work_item*)work;

	item->worker = Thread_Self();
	item->output = item->input * item->input;
	Thread_Sleep((s_nanotime){ .sec=0, .nanosec=5 * 1000 * 1000 }); // simulate 5ms of blocking work
}

static void	asynctest_work_done(s_async_work* work) // runs back on the event loop thread
{
	s_asynctest_work_item*	item = (s_asynctest_work_item*)work;
	s_asynctest_work*		ctx = work->base.data;

	if (item->output == item->input * item->input &&
		Thread_Equals(Thread_Self(), ctx->loop_thread) == TRUE && // the `done` callback runs on the loop thread
		Thread_Equals(item->worker, ctx->loop_thread) == FALSE)   // the `work` callback ran on a pool thread
		ctx->correct += 1;
}

//! AsyncWork_Submit(): work runs on pool threads, completion callbacks run back on the loop thread
static t_u64	scenario_async_work(void)
{
	s_asyncloop*		loop = AsyncLoop_New();
	static s_asynctest_work	ctx;

	if (loop == NULL)
		return (0);
	ctx = (s_asynctest_work){0};
	ctx.loop_thread = Thread_Self();
	for (t_uint i = 0; i < ASYNCTEST_WORK_AMOUNT; ++i)
	{
		ctx.items[i].input = i;
		ctx.items[i].work.base.data = &ctx;
		if (AsyncWork_Submit(loop, &ctx.items[i].work, asynctest_work_callback, asynctest_work_done) != ERROR_NONE)
			return (0);
	}
	if (AsyncLoop_IsAlive(loop) != TRUE) // pending work keeps the loop alive
		return (0);
	AsyncLoop_Run(loop, ASYNCRUN_DEFAULT); // runs until all submitted work has completed
	AsyncLoop_Delete(&loop);
	return (ctx.correct); // expected: ASYNCTEST_WORK_AMOUNT
}



static void	asynctest_count_fire(s_async_timer* timer)
{
	t_u64*	fired = timer->base.data;

	*fired += 1;
}

//! AsyncLoop_Run() modes: NOWAIT never blocks, ONCE blocks until the next due callback
static t_bool	scenario_async_runmodes(void)
{
	s_asyncloop*	loop = AsyncLoop_New();
	s_async_timer	timer;
	t_u64			fired = 0;
	t_bool			result = TRUE;

	if (loop == NULL)
		return (FALSE);
	if (AsyncTimer_Init(loop, &timer) != ERROR_NONE)
		return (FALSE);
	timer.base.data = &fired;
	if (AsyncTimer_Start(&timer, asynctest_count_fire, 20, 0) != ERROR_NONE)
		return (FALSE);
	result = result && (AsyncLoop_Run(loop, ASYNCRUN_NOWAIT) == TRUE); // NOWAIT: does not block; the timer is not yet due
	result = result && (fired == 0);
	result = result && (AsyncLoop_Run(loop, ASYNCRUN_ONCE) == FALSE); // ONCE: blocks (polling) until the timer is due, then fires it
	result = result && (fired == 1);
	AsyncLoop_Delete(&loop);
	return (result);
}



//! AsyncLoop_Now()/AsyncLoop_UpdateTime(): the loop's cached monotonic clock only moves forward
static t_bool	scenario_async_time(void)
{
	s_asyncloop*	loop = AsyncLoop_New();
	t_asynctime		before;
	t_bool			result = TRUE;

	if (loop == NULL)
		return (FALSE);
	before = AsyncLoop_Now(loop);
	Thread_Sleep((s_nanotime){ .sec=0, .nanosec=20 * 1000 * 1000 }); // 20ms
	result = result && (AsyncLoop_Now(loop) == before); // the cached time does not change on its own
	result = result && (AsyncLoop_UpdateTime(loop) == ERROR_NONE);
	result = result && (AsyncLoop_Now(loop) >= before + 20); // once updated, at least 20ms have passed
	AsyncLoop_Delete(&loop);
	return (result);
}



//! AsyncHandle_Stop()/AsyncHandle_Detach(): generic handle functions, and error handling for invalid arguments
static t_bool	scenario_async_handles_errors(void)
{
	s_asyncloop*	loop = AsyncLoop_New();
	s_async_timer	timer;
	s_async_idle	idle;
	t_u64			fired = 0;
	t_bool			result = TRUE;

	if (loop == NULL)
		return (FALSE);
	if (AsyncTimer_Init(loop, &timer) != ERROR_NONE ||
		AsyncIdle_Init(loop, &idle) != ERROR_NONE)
		return (FALSE);
	timer.base.data = &fired;
	result = result && (AsyncTimer_Start(&timer, asynctest_count_fire, 1000, 0) == ERROR_NONE);
	result = result && (AsyncHandle_IsActive((s_asynchandle*)&timer) == TRUE);
	result = result && (AsyncHandle_Stop((s_asynchandle*)&timer) == ERROR_NONE); // generic stop: dispatched according to handle type
	result = result && (AsyncHandle_IsActive((s_asynchandle*)&timer) == FALSE);
	result = result && (AsyncLoop_IsAlive(loop) == FALSE);
	result = result && (AsyncHandle_Detach((s_asynchandle*)&timer) == ERROR_NONE);
	result = result && (AsyncHandle_Detach((s_asynchandle*)&idle) == ERROR_NONE);
	// error handling (the error messages printed by these calls are expected):
	result = result && (AsyncHandle_Detach((s_asynchandle*)&timer) == ERROR_INVALIDARGS); // already detached
	result = result && (AsyncTimer_Start(&timer, asynctest_count_fire, 0, 0) == ERROR_INVALIDARGS); // detached: no longer initialized
	result = result && (AsyncLoop_Run(NULL, ASYNCRUN_DEFAULT) == FALSE);
	result = result && (AsyncLoop_Stop(NULL) == ERROR_NULLPOINTER);
	result = result && (AsyncLoop_Delete(NULL) == ERROR_NULLPOINTER);
	result = result && (AsyncTimer_Init(loop, NULL) == ERROR_NULLPOINTER);
	result = result && (AsyncTimer_Init(NULL, &timer) == ERROR_NULLPOINTER);
	result = result && (AsyncTimer_Start(&timer, NULL, 0, 0) != ERROR_NONE);
	result = result && (AsyncEvent_Send(NULL) == ERROR_NULLPOINTER);
	result = result && (AsyncWork_Submit(loop, NULL, asynctest_work_callback, NULL) == ERROR_NULLPOINTER);
	result = result && (AsyncLoop_Delete(&loop) == ERROR_NONE && loop == NULL);
	return (result);
}



/*============================================================================*\
||                              Testing Functions                             ||
\*============================================================================*/



#ifndef c_asyncnew
void test_async(void)	{}
#warning "async() test suite function defined, but the function isn't defined."
#else
static void	print_test_async_u64(char const* test_name, t_testflags flags,
		t_u64 expecting,
		t_u64 (*scenario)(void),
		char const* scenario_args)
{
	TEST_INIT(u64)
	TEST_PERFORM_(result, scenario)
	test.expect = expecting;
	TEST_PRINT(u64,	async_scenario, "%s", scenario_args)
}
static void	print_test_async_bool(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_bool (*scenario)(void),
		char const* scenario_args)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario)
	test.expect = expecting;
	TEST_PRINT(bool,async_scenario, "%s", scenario_args)
}
void	test_async(void)
{
/*	| TEST FUNCTION        | TEST NAME                          |TESTFLAG| EXPECTING             | TEST ARGS	*/
	print_test_async_u64 ("async timer (deadline ordering)",		FALSE,                    123, scenario_async_timer_order,   "timers: 20ms, 40ms, 60ms");
	print_test_async_u64 ("async timer (repeating)",				FALSE,                      3, scenario_async_timer_repeat,  "delay=10ms, repeat=15ms");
	print_test_async_u64 ("async idle (once per iteration)",		FALSE,                      5, scenario_async_idle,          "5 iterations");
	print_test_async_u64 ("async event (cross-thread send)",		FALSE,                      1, scenario_async_event,         "2 sends, coalesced");
#if !defined(_WIN32) // (poll handles are not yet supported by the Windows event loop backend)
	print_test_async_u64 ("async poll (pipe becomes readable)",		FALSE,                      5, scenario_async_poll,          "5 bytes written to pipe");
#endif
	print_test_async_u64 ("async work (thread pool)",				FALSE,   ASYNCTEST_WORK_AMOUNT, scenario_async_work,          "16 work items");
	print_test_async_bool("async run modes (NOWAIT/ONCE)",			FALSE,                   TRUE, scenario_async_runmodes,      "");
	print_test_async_bool("async loop time (cached clock)",			FALSE,                   TRUE, scenario_async_time,          "");
	print_test_async_bool("async handles (generic + errors)",		FALSE,                   TRUE, scenario_async_handles_errors,"NULL");
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/



int		testsuite_sys_async(void)
{
	print_suite_title("libccc/sys/async");

	test_async();

	return (OK);
}
