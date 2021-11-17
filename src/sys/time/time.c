
#include "libccc/memory.h"
#include "libccc/sys/time.h"

#ifndef __NOSTD__
	#define __STDC_WANT_LIB_EXT1__	1
	#include <time.h>
#else
	extern long	timezone;
	time_t	time(time_t* t);

	struct tm*	gmtime(time_t const* timer);						// (since C89)
	struct tm*	gmtime_s(struct tm* buf, time_t const* timer);		// (since C11)
	struct tm*	gmtime_r(time_t const* timer, struct tm* buf);		// (since C23)

	struct tm*	localtime(time_t const* timer);						// (since C89)
	struct tm*	localtime_s(struct tm* buf, time_t const* timer);	// (since C11)
	struct tm*	localtime_r(time_t const* timer, struct tm* buf);	// (since C23)
#endif

#include LIBCONFIG_ERROR_INCLUDE



t_time		Time_Now(void)
{
	t_time result = 0;

	if (time(&result) == (t_time)ERROR)
		return (TIME_NULL);
	return (result);
}



s_date		Time_ToDate_UTC(t_time const value)
{
	s_date result;
	struct tm tm;

	Memory_Clear(&tm, sizeof(struct tm));
#ifdef _WIN32
	gmtime_s(&tm, &value);	// gmtime_s() is thread-safe, unlike gmtime()
#else
	gmtime_r(&value, &tm);	// gmtime_r() is thread-safe, unlike gmtime()
#endif
	result = Date_FromSTDC(&tm);
	return (result);
}

s_date		Time_ToDate_LocalTime(t_time const value)
{
	s_date result;
	struct tm tm;

	Memory_Clear(&tm, sizeof(struct tm));
#ifdef _WIN32
	localtime_s(&tm, &value);	// localtime_s() is thread-safe, unlike localtime()
#else
	localtime_r(&value, &tm);	// localtime_r() is thread-safe, unlike localtime()
#endif
	result = Date_FromSTDC(&tm);
	if (result.offset == 0)
		result.offset = -timezone;
	return (result);
}



inline struct timespec	Timespec_ToSTDC(s_nanotime const* value)
{
	return ((struct timespec)
	{
		.tv_sec = value->sec,
		.tv_nsec = value->nanosec,
	});
}

inline s_nanotime		Timespec_FromSTDC(struct timespec const* value)
{
	return ((s_nanotime)
	{
		.sec = value->tv_sec,
		.nanosec = value->tv_nsec,
	});
}
