
#include "libccc/sys/time.h"

#ifndef __NOSTD__
	#include <time.h>
#else
	size_t	strftime(t_char* s, size_t max, const t_char* format, const struct tm *tm);
#endif

#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



#define MAX_BUFFER_SIZE		((t_size)1024)



t_char*		Date_ToString(s_date const* date, t_char const* format)
{
	struct tm tm;
	t_char*	result = NULL;
	t_size	size = 0;
	t_size	wrote = 0;
	t_uint	leapsec;

	if CCCERROR((!Date_IsValid(date)), ERROR_INVALIDARGS,
		"date given is not a valid calendar date/time")
		return (NULL);
	tm = Date_ToSTDC(date);
	leapsec = (tm.tm_sec >= TIME_MAX_SECONDS) ? (tm.tm_sec - (TIME_MAX_SECONDS - 1)) : 0;
	tm.tm_sec -= leapsec;
	do
	{
		String_Delete(&result);
		if (size == 0)
			size = String_Length(format) + 1;
		else size *= 2;
		result = String_New(size);
		if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
			return (NULL);
		wrote = strftime(result, size - 1, format, &tm);
	}
	while (wrote == 0 && size < MAX_BUFFER_SIZE);
	if CCCERROR((size >= MAX_BUFFER_SIZE), ERROR_INVALIDARGS, 
		"could not write date to string, size (" SF_SIZE ") is too large, should be under " SF_SIZE,
		size, MAX_BUFFER_SIZE)
		return (NULL);
	result[wrote] = '\0';
/*	// TODO fix this bad heuristic correction (waiting for ISO to get their story straight concerning leap seconds)
	if (leapsec) 
	{
		t_char target[4] = { '%','S','\0','\0' };
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



t_size		Date_ToString_N(t_char* dest, t_size max, s_date const* date, t_char const* format)
{
	struct tm tm;

	tm = Date_ToSTDC(date);
	return (strftime(dest, max, format, &tm));
}



_INLINE()
t_char*		Date_ToString_Unix(s_date const* date)
{
	return (Date_ToString(date, SF_DATE_UNIX " " SF_TIME_UNIX));
}

t_char*		DateNow_ToString_Unix(void)
{
	s_date date = Date_Now();
	return (Date_ToString_Unix(&date));
}
