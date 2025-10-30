
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_uint		StringArray_Count_Char(t_char const* const* strarr, t_char const c)
{
	t_uint		i;
	t_uint		count;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (0);
	count = 0;
	i = 0;
	while (strarr[i])
	{
		count += String_Count_Char(strarr[i], c);
		++i;
	}
	return (count);
}



t_uint		StringArray_Count_Charset(t_char const* const* strarr, t_char const* charset)
{
	t_uint		i;
	t_uint		count;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (0);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "charset given is NULL")
		return (0);
	count = 0;
	i = 0;
	while (strarr[i])
	{
		count += String_Count_Charset(strarr[i], charset);
		++i;
	}
	return (count);
}



t_uint		StringArray_Count_String(t_char const* const* strarr, t_char const* query)
{
	t_uint		i;
	t_uint		count;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (0);
	if CCCERROR((query == NULL), ERROR_NULLPOINTER, "query string given is NULL")
		return (0);
	count = 0;
	i = 0;
	while (strarr[i])
	{
		count += String_Count_String(strarr[i], query);
		++i;
	}
	return (count);
}
