
#ifndef __NOSTD__
	#include <time.h>
#else
	time_t	time(time_t* t);
	struct tm*	gmtime(const time_t* timep);
	struct tm*	localtime(const time_t* timep);
#endif

#include "libccc/sys/time.h"



t_time		Time_Now(void)
{
	t_time result = 0;

	if (time(&result) == (t_time)ERROR)
		return (TIME_NULL);
	return (result);
}



s_date		Time_ToDate_UTC(t_time const value)
{
	s_date result = DATE_NULL;
 	struct tm* tm;

 	tm = gmtime(&value);
 	if (tm == NULL)
 		return (result);
	result = Date_FromSTDC(tm);
	return (result);
}

s_date		Time_ToDate_LocalTime(t_time const value)
{
	s_date result = DATE_NULL;
 	struct tm* tm;

 	tm = localtime(&value);
 	if (tm == NULL)
 		return (result);
	result = Date_FromSTDC(tm);
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
