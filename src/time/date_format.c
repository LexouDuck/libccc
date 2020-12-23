
/*
**	Functions used from <time.h>:
**	-	time_t	time(time_t* t);
**	-	size_t	strftime(char *s, size_t max, const char *format, const struct tm *tm);
*/
#include <time.h>

#include "libft_time.h"
#include "libft_string.h"



char*	Date_String_Format(s_date const* date, char const* format)
{
	struct tm tm;
	char*	result;
	t_size	length;

	tm = Date_To_STDC(date);
	length = strftime(NULL, -1u, format, &tm);
	result = String_New(length);
	if (result == NULL)
		return (NULL);
	length = strftime(result, length, format, &tm);
	return (result);
}



t_size	Date_String_Format_N(char* dest, t_size n, s_date const* date, char const* format)
{
	struct tm tm;

	tm = Date_To_STDC(date);
	return (strftime(dest, n, format, &tm));
}
