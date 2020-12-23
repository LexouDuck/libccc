
/*
**	Functions used from <time.h>:
**	-	time_t	time(time_t* t);
**	-	time_t	timegm(struct tm* tm);		-> alias:_mkgmtime()
**	-	time_t	timelocal(struct tm* tm);	-> alias: mktime()
**	-	size_t	strftime(char *s, size_t max, const char *format, const struct tm *tm);
*/
#include <time.h>

#include "libft_time.h"
#include "libft_memory.h"
#include "libft_string.h"



t_time		Date_Now(void)
{
	t_time result;
	if (time(&result) < 0)
		return (TIME_NULL);
	return (result);
}



t_time		Date_To_Time_UTC(s_date const* value)
{
	struct tm	date;

	date = Date_To_STDC(value);
#ifdef _WIN32
	return (_mkgmtime(&date));
#else
	return (timegm(&date));
#endif
}

t_time		Date_To_Time_LocalTime(s_date const* value)
{
	struct tm	date;

	date = Date_To_STDC(value);
#ifdef _WIN32
	return (mktime(&date));
#else
	return (timelocal(&date));
#endif
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
