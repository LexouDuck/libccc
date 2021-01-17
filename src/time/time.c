
/*
**	Functions used from <time.h>:
**	-	time_t	time(time_t* t);
**	-	struct tm*	gmtime(const time_t* timep);
**	-	struct tm*	localtime(const time_t* timep);
*/
#include <time.h>

#include "libccc_time.h"



t_time		Time_Now(void)
{
	t_time result;
	if (time(&result) == (t_time)-1)
		return (TIME_NULL);
	return (result);
}



s_date		Time_To_Date_UTC(t_time const value)
{
	s_date result;
 	struct tm* tm;

 	tm = gmtime(&value);
	result = STDC_To_Date(tm);
	return (result);
}

s_date		Time_To_Date_LocalTime(t_time const value)
{
	s_date result;
 	struct tm* tm;

 	tm = localtime(&value);
	result = STDC_To_Date(tm);
	return (result);
}



inline struct timespec	Timespec_To_STDC(s_timespec const* value)
{
	return ((struct timespec)
	{
		.tv_sec = value->sec,
		.tv_nsec = value->nanosec,
	});
}

inline s_timespec		STDC_To_Timespec(struct timespec const* value)
{
	return ((s_timespec)
	{
		.sec = value->tv_sec,
		.nanosec = value->tv_nsec,
	});
}
