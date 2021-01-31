
#include "libccc/sys/time.h"



inline t_time	Time_SetTimezone(t_time value, t_timezone old, t_timezone new)
{
	return (value + (new - old));
}



inline s_date	Date_SetTimezone(s_date const* value, t_timezone old, t_timezone new)
{
	t_time t;

	t = Date_To_Time(value);
	t = t + (new - old);
	return (Time_To_Date(t));
}
