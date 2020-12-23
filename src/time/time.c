
/*
**	Functions used from <time.h>:
**	-	time_t	time(time_t* t);
**	-	time_t	timegm(struct tm* tm);		-> alias:_mkgmtime()
**	-	time_t	timelocal(struct tm* tm);	-> alias: mktime()
**	-	struct tm*	gmtime(const time_t* timep);
**	-	struct tm*	localtime(const time_t* timep);
*/
#include <time.h>

#include "libft_time.h"
#include "libft_memory.h"



t_time		Time_Now(void)
{
	t_time result;
	if (time(&result) < 0)
		return (TIME_NULL);
	return (result);
}

t_time		Time_SetTimezone(t_time value, e_timezone old, e_timezone new)
{
	// TODO implement
	return (value);
}



s_date		Time_To_Date_UTC(t_time const value)
{
	s_date result;
 	struct tm* tm;

 	tm = gmtime(&value);
	result = STDC_To_Date(tm);
 	Memory_Delete((void*)&tm);
	return (result);
}

s_date		Time_To_Date_LocalTime(t_time const value)
{
	s_date result;
 	struct tm* tm;

 	tm = localtime(&value);
	result = STDC_To_Date(tm);
 	Memory_Delete((void*)&tm);
	return (result);
}

s_date		Time_To_Date_Timezone(t_time const value, e_timezone timezone)
{
	s_date result;
	t_time tmp = Time_SetTimezone(value, TIMEZONE_UTC, timezone);

	// TODO implement
	return (result);
}



t_time		Date_To_Time_UTC(s_date const* value)
{
	struct tm	date;

	date = Date_To_STDC(value);
#ifdef timegm
	return (timegm(&date));
#else
	return (_mkgmtime(&date));
#endif
}

t_time		Date_To_Time_LocalTime(s_date const* value)
{
	struct tm	date;

	date = Date_To_STDC(value);
#ifdef timelocal
	return (timelocal(&date));
#else
	return (mktime(&date));
#endif
}

t_time		Date_To_Time_Timezone(s_date const* value, e_timezone timezone)
{
	t_time result = 0;

	// TODO implement
	return (Time_SetTimezone(result, TIMEZONE_UTC, timezone));
}



inline struct tm	Date_To_STDC(s_date const* value)
{
 	struct tm	result;

	result.tm_sec   = value->sec;
	result.tm_min   = value->min;
	result.tm_hour  = value->hour;
	result.tm_mday  = value->day_week;
	result.tm_mon   = value->day_month;
	result.tm_year  = value->day_year;
	result.tm_wday  = value->month;
	result.tm_yday  = value->year;
	result.tm_isdst = value->is_dst;
	return (result);
}

inline s_date		STDC_To_Date(struct tm const* value)
{
	s_date result;

	result.sec       = value->tm_sec;
	result.min       = value->tm_min;
	result.hour      = value->tm_hour;
	result.day_week  = value->tm_mday;
	result.day_month = value->tm_mon;
	result.day_year  = value->tm_year;
	result.month     = value->tm_wday;
	result.year      = value->tm_yday;
	result.is_dst    = value->tm_isdst;
	return (result);
}



struct timespec	Timespec_To_STDC(s_timespec const* value)
{
	return ((struct timespec)
	{
		.tv_sec = value->sec,
		.tv_nsec = value->nanosec,
	});
}

s_timespec		STDC_To_Timespec(struct timespec const* value)
{
	return ((s_timespec)
	{
		.sec = value->tv_sec,
		.nanosec = value->tv_nsec,
	});
}
