
#include "libccc/sys/time.h"

#ifndef __NOSTD__
	#include <time.h>
#else
	time_t	timegm(struct tm* tm);
	time_t	_mkgmtime(struct tm* tm);
	#define mkgmtime	_mkgmtime
	time_t	timelocal(struct tm* tm);
	time_t	mktime(struct tm* tm);
	#define _mktime		mktime
	time_t	time(time_t* t);
#endif

#include "libccc/memory.h"
#include "libccc/string.h"

#include LIBCONFIG_HANDLE_INCLUDE



#define TM_YEAR_BASE	1900



s_date		Date_Now(void)
{
	t_time result;
	if (time(&result) == (t_time)-1)
		return (DATE_NULL);
	return (Time_ToDate_UTC(result));
}



t_time		Date_ToTime_UTC(s_date const* value)
{
	struct tm	tm;

	tm = Date_ToSTDC(value);
#ifdef _WIN32
	return (_mkgmtime(&tm));
#else
	return (timegm(&tm));
#endif
}

t_time		Date_ToTime_LocalTime(s_date const* value)
{
	struct tm	tm;

	tm = Date_ToSTDC(value);
#ifdef _WIN32
	return (mktime(&tm));
#else
	return (timelocal(&tm));
#endif
}



inline
struct tm	Date_ToSTDC(s_date const* value)
{
	return ((struct tm)
	{
		.tm_sec 	= value->sec,
		.tm_min 	= value->min,
		.tm_hour 	= value->hour,
		.tm_wday 	= value->day_week,
		.tm_mday 	= value->day_month,
		.tm_yday 	= value->day_year,
		.tm_mon 	= value->month,
		.tm_year 	= value->year - TM_YEAR_BASE,
		.tm_isdst 	= value->is_dst,
#ifdef TM_GMTOFF
		.tm_gmtoff	= value->timezone;
#endif
	});
}

inline
s_date		Date_FromSTDC(struct tm const* value)
{
	return ((s_date)
	{
		.sec		= value->tm_sec,
		.min		= value->tm_min,
		.hour		= value->tm_hour,
		.day_week	= value->tm_wday,
		.day_month	= value->tm_mday,
		.day_year	= value->tm_yday,
		.month		= value->tm_mon,
		.year		= value->tm_year + TM_YEAR_BASE,
		.is_dst		= value->tm_isdst,
		.offset		=
#ifdef TM_GMTOFF
			value->tm_gmtoff,
#else
			0
#endif
	});
}
