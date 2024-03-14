
#include <stdlib.h>
#include <time.h>

#include "test.h"
#include "test_timer.h"



#ifdef __MINGW32__
	#define TIMER_FORMATSTRING	"%I64d.%.09ld"
#else
	#define TIMER_FORMATSTRING	"%lld.%.09ld"
#endif

/*	Define a 10e9 macro we use for nanosecond modulo */
#define BILLION 1000000000L



/*
** ************************************************************************** *|
**                           Timer utility functions                          *|
** ************************************************************************** *|
*/

/*!	There are a couple of different cross-platform clock possibilities:
**	- CLOCK_REALTIME	System-wide real-time clock. This clock returns the number of seconds and nanoseconds since the Epoch.
**						This clock can be set via clock_settime but doing so requires appropriate privileges, because it's linked to the system time.
**	- CLOCK_MONOTONIC 			Represents monotonic time since some unspecified starting point. This clock cannot be set.
**	- CLOCK_PROCESS_CPUTIME_ID 	High-resolution per-process timer from the CPU.
**	- CLOCK_THREAD_CPUTIME_ID 	Thread-specific CPU-time clock. 
*/
void	timer_clock(s_time* result)
{
	if (clock_gettime(CLOCK_MONOTONIC, result) == -1)
	{
		perror("clock_gettime() returned -1");
		exit(EXIT_FAILURE);
	}
}



s_time	timer_getdiff(s_time start, s_time end)
{
	s_time result;
	
	result.tv_sec = end.tv_sec - start.tv_sec;
	result.tv_nsec = end.tv_nsec - start.tv_nsec;
	if (result.tv_nsec >= BILLION)
	{
		result.tv_nsec -= BILLION;
		result.tv_sec++;
	}
	return (result);
}



/* Returns negative if 'a' is lower than 'b', positive if 'b' > 'a' and 0 if equal. */
inline
t_s64	timer_compare(s_time a, s_time b)
{
	if (a.tv_sec == b.tv_sec)
		return (a.tv_nsec - b.tv_nsec);
	else
		return (a.tv_sec - b.tv_sec);
}



/* prints the result of a timer (and potentially a comparison with the secondary timer) */
void	print_timer_result(s_timer* t, t_s64 compare)
{
	char result1[64] = { 0 };
	char result2[64] = { 0 };

	if (!g_test.config.verbose || !g_test.config.show_speed)
		return;

	t->result_time = timer_getdiff(t->result_start, t->result_end);
	if (t->result_time.tv_nsec < 0 || t->result_time.tv_nsec < 0)
		sprintf((char*)&result1, "SIGNAL EMITTED");
	else sprintf((char*)&result1, TIMER_FORMATSTRING, (long long)t->result_time.tv_sec, t->result_time.tv_nsec);

	printf(" [libccc:");
	if (compare)
	{
		t->expect_time = timer_getdiff(t->expect_start, t->expect_end);
		if (t->expect_time.tv_nsec < 0 || t->expect_time.tv_nsec < 0)
			sprintf((char*)&result2, "SIGNAL EMITTED");
		else sprintf((char*)&result2, TIMER_FORMATSTRING, (long long)t->expect_time.tv_sec, t->expect_time.tv_nsec);

		if ((t->result_time.tv_sec >= 0 && t->result_time.tv_nsec >= 0) ||
			(t->expect_time.tv_sec >= 0 && t->expect_time.tv_nsec >= 0))
			compare = timer_compare(t->result_time, t->expect_time);
		else compare = 0;

		if (compare == 0)
			printf("%s, libc:", result1);
		else if (compare < 0)
			printf(ANSI_COLOR_FG_GREEN"%s"ANSI_RESET", libc:", result1);
		else
			printf(ANSI_COLOR_FG_RED"%s"ANSI_RESET", libc:", result1);

		printf("%s]", result2);
	}
	else printf("%s]", result1);
}
