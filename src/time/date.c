
/*
**	Functions used from <time.h>:
**	-	time_t	time(time_t* t);
**	-	time_t	timegm(struct tm* tm);		-> alias:_mkgmtime()
**	-	time_t	timelocal(struct tm* tm);	-> alias: mktime()
**	-	size_t	strftime(char *s, size_t max, const char *format, const struct tm *tm);
*/
#include <time.h>

#include "libccc_time.h"
#include "libccc_memory.h"
#include "libccc_string.h"



s_date		Date_Now(void)
{
	t_time result;
	if (time(&result) == (t_time)-1)
		return (DATE_NULL);
	return (Time_To_Date_UTC(result));
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
	return ((struct tm)
	{
		.tm_sec   = value->sec,
		.tm_min   = value->min,
		.tm_hour  = value->hour,
		.tm_wday  = value->day_week,
		.tm_mday  = value->day_month,
		.tm_yday  = value->day_year,
		.tm_mon   = value->month,
		.tm_year  = value->year,
		.tm_isdst = value->is_dst,
	});
}

inline s_date		STDC_To_Date(struct tm const* value)
{
	return ((s_date)
	{
		.sec       = value->tm_sec,
		.min       = value->tm_min,
		.hour      = value->tm_hour,
		.day_week  = value->tm_wday,
		.day_month = value->tm_mday,
		.day_year  = value->tm_yday,
		.month     = value->tm_mon,
		.year      = value->tm_year,
		.is_dst    = value->tm_isdst,
	});
}
