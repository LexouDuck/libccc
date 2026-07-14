
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_uint	StringArrayUTF8_Length(t_utf8 const* const* strarr)
{
	t_uint	i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (0);
	i = 0;
	while (strarr[i])
	{
		++i;
	}
	return (i);
}



t_size	StringArrayUTF8_TotalLength(t_utf8 const* const* strarr, t_uint n)
{
	t_size	result;
	t_uint	i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (0);
	result = 0;
	i = 0;
	while (strarr[i] && i < n)
	{
		result += StringUTF8_Length(strarr[i]);
		++i;
	}
	return (result);
}
