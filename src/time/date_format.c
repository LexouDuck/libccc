
/*
**	Functions used from <time.h>:
**	-	size_t	strftime(char *s, size_t max, const char *format, const struct tm *tm);
*/
#include <time.h>

#include "libccc/sys/time.h"
#include "libccc/string.h"



char*	Date_String_Format(s_date const* date, char const* format)
{
	struct tm tm;
	char*	result;
	t_size	size;
	t_size	r;

	tm = Date_To_STDC(date);
	size = String_Length(format) + 1;
	result = String_New(size);
	if (result == NULL)
		return (NULL);
	r = strftime(result, size, format, &tm);
	while (r == 0)
	{
		String_Delete(&result);
		size *= 2;
		result = String_New(size);
		if (result == NULL)
			return (NULL);
		r = strftime(result, size - 1, format, &tm);
	}
	result[r] = '\0';
	return (result);
}



t_size	Date_String_Format_N(char* dest, t_size max, s_date const* date, char const* format)
{
	struct tm tm;

	tm = Date_To_STDC(date);
	return (strftime(dest, max, format, &tm));
}
