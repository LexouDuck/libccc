
#ifndef __NOSTD__
	#include <time.h>
#else
	size_t	strftime(t_char* s, size_t max, const t_char* format, const struct tm *tm);
#endif

#include "libccc/sys/time.h"
#include "libccc/string.h"



#define MAX_BUFFER_SIZE		1024



t_char*	Date_ToString(s_date const* date, t_char const* format)
{
	struct tm tm;
	t_char*	result;
	t_size	size;
	t_size	wrote;
	t_uint	leapsec;

	if (!Date_IsValid(date))
		return (NULL);
	tm = Date_ToSTDC(date);
	size = String_Length(format) + 1;
	result = String_New(size);
	if (result == NULL)
		return (NULL);
	leapsec = (tm.tm_sec >= TIME_MAX_SECONDS) ? (tm.tm_sec - (TIME_MAX_SECONDS - 1)) : 0;
	tm.tm_sec -= leapsec;
	wrote = strftime(result, size - 1, format, &tm);
	while (wrote == 0 && size < MAX_BUFFER_SIZE)
	{
		String_Delete(&result);
		size *= 2;
		result = String_New(size);
		if (result == NULL)
			return (NULL);
		wrote = strftime(result, size - 1, format, &tm);
	}
	if (size >= MAX_BUFFER_SIZE)
		return (NULL);
	result[wrote] = '\0';
/*	// TODO fix this bad heuristic correction (waiting for ISO to get their story straight concerning leap seconds)
	if (leapsec) 
	{
		char target[4] = { '%','S','\0','\0' };
		t_char* secs = String_Find_String(format, target);
		if (secs)
		{
			target[0] = '5';
			target[1] = '9';
			target[2] = (secs[2] == '%' ? '\0' : secs[2]);
			secs = String_Find_String(result, target);
			if (secs)
			{
				secs[0] = '6';
				secs[1] = '0';
			}
		}
	}
*/
	return (result);
}



t_size	Date_ToString_N(t_char* dest, t_size max, s_date const* date, t_char const* format)
{
	struct tm tm;

	tm = Date_ToSTDC(date);
	return (strftime(dest, max, format, &tm));
}
