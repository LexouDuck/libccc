
#include "libccc/sys/time.h"



t_bool	Date_IsLeapYear(t_s32 year)
{
	if (year % 4 != 0) return (FALSE);
	else if (year % 100 != 0) return (TRUE);
	else if (year % 400 != 0) return (FALSE);
	else return (TRUE);
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



t_uint	Date_DayOfTheWeek(s_date* date)
{
	t_time t = Date_ToTime(date);
	t_s64 days_since_epoch = (t / (TIME_MAX_SECONDS * TIME_MAX_MINUTES * TIME_MAX_HOURS));
	return ((days_since_epoch + 4) % ENUMLENGTH_WEEKDAY); // 1 Jan 1970 was a Thursday, we add 4 so Sunday is day 0
}
