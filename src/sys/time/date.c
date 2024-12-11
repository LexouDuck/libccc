
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

#include LIBCONFIG_ERROR_INCLUDE



#define TM_YEAR_BASE	1900



s_date		Date_Now(void)
{
	t_time result;
	if (time(&result) == (t_time)-1)
		return (DATE_NULL);
	return (Time_ToDate_UTC(result));
}



#if defined(_WIN32) || defined(__APPLE__) || defined(__ANDROID__)
#elif (_DEFAULT_SOURCE || _BSD_SOURCE || _SVID_SOURCE)
#else
int days_from_epoch(int y, int m, int d);
int days_from_epoch(int y, int m, int d)
{	// Algorithm: http://howardhinnant.github.io/date_algorithms.html
	y -= m <= 2;
	int era = y / 400;
	int yoe = y - era * 400; // [0, 399]
	int doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; // [0, 365]
	int doe = yoe * 365 + yoe / 4 - yoe / 100 + doy; // [0, 146096]
	return era * 146097 + doe - 719468;
}

time_t timegm(struct tm* t);
time_t timegm(struct tm* t)
{	// It does not modify broken-down time
	int year = t->tm_year + 1900;
	int month = t->tm_mon; // 0-11
	if (month > 11)
	{
		year += month / 12;
		month %= 12;
	}
	else if (month < 0)
	{
		int years_diff = (11 - month) / 12;
		year -= years_diff;
		month += 12 * years_diff;
	}
	int days_since_epoch = days_from_epoch(year, month + 1, t->tm_mday);
	return 60 * (60 * (24L * days_since_epoch + t->tm_hour) + t->tm_min) + t->tm_sec;
}
#endif

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
	return (mktime(&tm));
}



extern inline
struct tm	Date_ToSTDC(s_date const* value)
{
	return ((struct tm)
	{
		.tm_sec 	= value->sec,
		.tm_min 	= value->min,
		.tm_hour 	= value->hour,
		.tm_mday 	= value->day_month,
		.tm_mon 	= value->month,
		.tm_year 	= value->year - TM_YEAR_BASE,
		.tm_wday 	= value->day_week,
		.tm_yday 	= (int)value->day_year,
		.tm_isdst 	= value->is_dst,
#ifdef TM_GMTOFF
		.tm_gmtoff	= value->timezone;
#endif
	});
}

extern inline
s_date		Date_FromSTDC(struct tm const* value)
{
	return ((s_date)
	{
		.year		= (t_s32)value->tm_year + TM_YEAR_BASE,
		.month		= (e_month)value->tm_mon,
		.day_week	= (e_weekday)value->tm_wday,
		.day_month	= (t_u8)value->tm_mday,
		.day_year	= (t_u32)value->tm_yday,
		.hour		= (t_u8)value->tm_hour,
		.min		= (t_u8)value->tm_min,
		.sec		= (t_u8)value->tm_sec,
		.is_dst		= (t_bool)value->tm_isdst,
		.offset		= (t_timezone)
#ifdef TM_GMTOFF
			value->tm_gmtoff,
#else
			0
#endif
	});
}
