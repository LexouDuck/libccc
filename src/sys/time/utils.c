
#include "libccc/sys/time.h"



t_bool	Date_IsValid(s_date const* date)
{
	if (date->sec >= (Date_HasLeapSecond(date->month, date->year) ? TIME_MAX_SECONDS_LEAP : TIME_MAX_SECONDS))
		return (FALSE);
	if (date->min >= TIME_MAX_MINUTES)
		return (FALSE);
	if (date->hour >= TIME_MAX_HOURS)
		return (FALSE);
	if (date->day_month < 1)
		return (FALSE);
	if (date->day_month > Date_DaysInMonth(date->month, date->year))
		return (FALSE);
	if (date->day_year < 0)
		return (FALSE);
	if (date->day_year >= (Date_IsLeapYear(date->year) ? TIME_MAX_DAYS_YEAR_LEAP : TIME_MAX_DAYS_YEAR))
		return (FALSE);
	if (date->day_week < 0)
		return (FALSE);
	if (date->day_week >= ENUMLENGTH_WEEKDAY)
		return (FALSE);
	if (date->month < 0)
		return (FALSE);
	if (date->month >= ENUMLENGTH_MONTH)
		return (FALSE);
	return (TRUE);
}



void	Date_MakeValid(s_date* date)
{
	t_s64 tmp;

	tmp = (Date_HasLeapSecond(date->month, date->year) ? TIME_MAX_SECONDS_LEAP : TIME_MAX_SECONDS);
	if (date->sec >= tmp)
		date->sec = (tmp - 1);
	tmp = TIME_MAX_MINUTES;
	if (date->min >= tmp)
		date->min = (tmp - 1);
	tmp = TIME_MAX_HOURS;
	if (date->hour >= tmp)
		date->hour = (tmp - 1);
	tmp = Date_DaysInMonth(date->month, date->year);
	if (date->day_month > tmp)
		date->day_month = (tmp - 1);
	if (date->day_month < 1)
		date->day_month = 1;
	tmp = (Date_IsLeapYear(date->year) ? TIME_MAX_DAYS_YEAR_LEAP : TIME_MAX_DAYS_YEAR);
	if (date->day_year >= tmp)
		date->day_year = (tmp - 1);
	if (date->day_year < 0)
		date->day_year = 0;
	tmp = ENUMLENGTH_WEEKDAY;
	if (date->day_week >= tmp)
		date->day_week = (tmp - 1);
	if (date->day_week < 0)
		date->day_week = 0;
	tmp = ENUMLENGTH_MONTH;
	if (date->month >= tmp)
		date->month = (tmp - 1);
	if (date->month < 0)
		date->month = 0;
}



t_uint	Date_DaysInMonth(e_month month, t_s32 year)
{
	if (month == MONTH_FEBRUARY)
		return (Date_IsLeapYear(year) ? 29 : 28);
	else if (month <= 6)
		return (month % 2 == 0 ? 31 : 30);
	else
		return (month % 2 == 1 ? 31 : 30);
}



e_weekday	Date_DayOfTheWeek(s_date* date)
{
// algorithm courtesy of Tomohiko Sakamoto
    static char const t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    t_s32 y = date->year;
    if (date->month < MONTH_MARCH)
    {
        y -= 1;
    }
    return ((y + y/4 - y/100 + y/400 + t[date->month] + date->day_month) % ENUMLENGTH_WEEKDAY);
/*
// simple epoch-based algorithm
	t_time t = Date_ToTime(date);
	t_s64 days_since_epoch = (t / (TIME_MAX_SECONDS * TIME_MAX_MINUTES * TIME_MAX_HOURS));
	return ((days_since_epoch + 4) % ENUMLENGTH_WEEKDAY); // 1 Jan 1970 was a Thursday, we add 4 so Sunday is day 0
*/
}



t_bool	Date_IsLeapYear(t_s32 year)
{
	if (year % 4 != 0) return (FALSE);
	else if (year % 100 != 0) return (TRUE);
	else if (year % 400 != 0) return (FALSE);
	else return (TRUE);
}



t_bool	Date_HasLeapSecond(e_month month, t_s32 year)
{
	if (month != MONTH_JUNE &&
		month != MONTH_DECEMBER)
		return (FALSE);
	switch (year)
	{
		case 1972:	return (month == MONTH_JUNE ? TRUE	: TRUE	);
		case 1973:	return (month == MONTH_JUNE ? FALSE	: TRUE	);
		case 1974:	return (month == MONTH_JUNE ? FALSE	: TRUE	);
		case 1975:	return (month == MONTH_JUNE ? FALSE	: TRUE	);
		case 1976:	return (month == MONTH_JUNE ? FALSE	: TRUE	);
		case 1977:	return (month == MONTH_JUNE ? FALSE	: TRUE	);
		case 1978:	return (month == MONTH_JUNE ? FALSE	: TRUE	);
		case 1979:	return (month == MONTH_JUNE ? FALSE	: TRUE	);
		case 1980:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 1981:	return (month == MONTH_JUNE ? TRUE	: FALSE	);
		case 1982:	return (month == MONTH_JUNE ? TRUE	: FALSE	);
		case 1983:	return (month == MONTH_JUNE ? TRUE	: FALSE	);
		case 1984:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 1985:	return (month == MONTH_JUNE ? TRUE	: FALSE	);
		case 1986:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 1987:	return (month == MONTH_JUNE ? FALSE	: TRUE	);
		case 1988:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 1989:	return (month == MONTH_JUNE ? FALSE	: TRUE	);
		case 1990:	return (month == MONTH_JUNE ? FALSE	: TRUE	);
		case 1991:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 1992:	return (month == MONTH_JUNE ? TRUE	: FALSE	);
		case 1993:	return (month == MONTH_JUNE ? TRUE	: FALSE	);
		case 1994:	return (month == MONTH_JUNE ? TRUE	: FALSE	);
		case 1995:	return (month == MONTH_JUNE ? FALSE	: TRUE	);
		case 1996:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 1997:	return (month == MONTH_JUNE ? TRUE	: FALSE	);
		case 1998:	return (month == MONTH_JUNE ? FALSE	: TRUE	);
		case 1999:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 2000:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 2001:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 2002:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 2003:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 2004:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 2005:	return (month == MONTH_JUNE ? FALSE	: TRUE	);
		case 2006:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 2007:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 2008:	return (month == MONTH_JUNE ? FALSE	: TRUE	);
		case 2009:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 2010:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 2011:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 2012:	return (month == MONTH_JUNE ? TRUE	: FALSE	);
		case 2013:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 2014:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 2015:	return (month == MONTH_JUNE ? TRUE	: FALSE	);
		case 2016:	return (month == MONTH_JUNE ? FALSE	: TRUE	);
		case 2017:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 2018:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 2019:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
		case 2020:	return (month == MONTH_JUNE ? FALSE	: FALSE	);
//		case 2021:	return (month == MONTH_JUNE ? FALSE	: TBA	);
		default: return (FALSE);
	}
}
