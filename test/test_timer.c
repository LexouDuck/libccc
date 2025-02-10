
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "test.h"
#include "test_timer.h"



#ifdef __MINGW32__
	#define TIMER_FORMATSTRING	"%I64d.%.09ld"
#else
	#define TIMER_FORMATSTRING	"%lld.%.09ld"
#endif

/*	Define a 10e9 macro we use for nanosecond modulo */
#define BILLION 1000000000L



/*============================================================================*\
||                           Timer utility functions                          ||
\*============================================================================*/

#if (defined(_WIN32) && !defined(__MINGW32__))
#include <windows.h>

#define CLOCK_REALTIME  0
#define CLOCK_MONOTONIC 1
typedef int clockid_t;

#define MS_PER_SEC      1000ULL     // MS = milliseconds
#define US_PER_MS       1000ULL     // US = microseconds
#define HNS_PER_US      10ULL       // HNS = hundred-nanoseconds (e.g., 1 hns = 100 ns)
#define NS_PER_US       1000ULL
#define HNS_PER_SEC     (MS_PER_SEC * US_PER_MS * HNS_PER_US)
#define NS_PER_HNS      (100ULL)    // NS = nanoseconds
#define NS_PER_SEC      (MS_PER_SEC * US_PER_MS * NS_PER_US)

int clock_gettime_monotonic(struct timespec *tv)
{
	static LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER ticks;

	if (!ticksPerSec.QuadPart)
	{
		QueryPerformanceFrequency(&ticksPerSec);
		if (!ticksPerSec.QuadPart)
		{
			errno = ENOTSUP;
			return -1;
		}
	}
	QueryPerformanceCounter(&ticks);
	tv->tv_sec = (long)(ticks.QuadPart / ticksPerSec.QuadPart);
	tv->tv_nsec = (long)(((ticks.QuadPart % ticksPerSec.QuadPart) * NS_PER_SEC) / ticksPerSec.QuadPart);
	return 0;
}
int clock_gettime_realtime(struct timespec *tv)
{
	FILETIME ft;
	ULARGE_INTEGER hnsTime;

	GetSystemTimePreciseAsFileTime(&ft);
	hnsTime.LowPart = ft.dwLowDateTime;
	hnsTime.HighPart = ft.dwHighDateTime;
	// To get POSIX Epoch as baseline, subtract the number of hns intervals from Jan 1, 1601 to Jan 1, 1970.
	hnsTime.QuadPart -= (11644473600ULL * HNS_PER_SEC);
	// modulus by hns intervals per second first, then convert to ns, as not to lose resolution
	tv->tv_nsec = (long)((hnsTime.QuadPart % HNS_PER_SEC) * NS_PER_HNS);
	tv->tv_sec = (long)(hnsTime.QuadPart / HNS_PER_SEC);

	return 0;
}
int clock_gettime(clockid_t type, struct timespec *tp)
{
	if (type == CLOCK_MONOTONIC)
	{
		return clock_gettime_monotonic(tp);
	}
	else if (type == CLOCK_REALTIME)
	{
		return clock_gettime_realtime(tp);
	}
	errno = ENOTSUP;
	return -1;
}
#endif

/*!	There are a couple of different cross-platform clock possibilities:
**	- CLOCK_REALTIME            System-wide real-time clock. This clock returns the number of seconds and nanoseconds since the Epoch.
**	                            This clock can be set via clock_settime but doing so requires appropriate privileges, because it's linked to the system time.
**	- CLOCK_MONOTONIC           Represents monotonic time since some unspecified starting point. This clock cannot be set.
**	- CLOCK_PROCESS_CPUTIME_ID  High-resolution per-process timer from the CPU.
**	- CLOCK_THREAD_CPUTIME_ID   Thread-specific CPU-time clock. 
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
int	timer_compare(s_time a, s_time b)
{
	if (a.tv_sec == b.tv_sec)
		return (a.tv_nsec - b.tv_nsec);
	else
		return (a.tv_sec - b.tv_sec);
}



/* prints the result of a timer (and potentially a comparison with the secondary timer) */
void	print_timer_result(s_timer* t, int compare)
{
	char result1[64] = { 0 };
	char result2[64] = { 0 };

	if (!g_test.config.verbose || !g_test.config.show_speed)
		return;

	t->result_time = timer_getdiff(t->result_start, t->result_end);
	if (t->result_time.tv_sec < 0 || t->result_time.tv_nsec < 0)
		sprintf((char*)&result1, "SIGNAL EMITTED");
	else sprintf((char*)&result1, TIMER_FORMATSTRING, (long long)t->result_time.tv_sec, t->result_time.tv_nsec);

	printf(" [libccc:");
	if (compare)
	{
		t->expect_time = timer_getdiff(t->expect_start, t->expect_end);
		if (t->expect_time.tv_sec < 0 || t->expect_time.tv_nsec < 0)
			sprintf((char*)&result2, "SIGNAL EMITTED");
		else sprintf((char*)&result2, TIMER_FORMATSTRING, (long long)t->expect_time.tv_sec, t->expect_time.tv_nsec);

		if ((t->result_time.tv_sec >= 0 && t->result_time.tv_nsec >= 0) ||
			(t->expect_time.tv_sec >= 0 && t->expect_time.tv_nsec >= 0))
			compare = timer_compare(t->result_time, t->expect_time);
		else compare = 0;

		double percent;
		const char* which;
		if (compare == 0)
		{
			printf("%s, stdlib:", result1);
			which = "same";
		}
		else if (compare < 0)
		{
			printf(ANSI_COLOR_FG_GREEN "%s" ANSI_RESET", stdlib:", result1);
			percent = (double)t->expect_time.tv_nsec / (double)t->result_time.tv_nsec;
			which = ANSI_COLOR_FG_GREEN "faster" ANSI_RESET;
		}
		else
		{
			printf(ANSI_COLOR_FG_RED "%s" ANSI_RESET", stdlib:", result1);
			percent = (double)t->result_time.tv_nsec / (double)t->expect_time.tv_nsec;
			which = ANSI_COLOR_FG_RED "slower" ANSI_RESET;
		}
		printf("%s] = %.2fx %s", result2, percent, which);
	}
	else printf("%s]", result1);
}
