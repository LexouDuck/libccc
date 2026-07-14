
#include "libccc/memory.h"
#include "libccc/text/string/ascii.h"
#include "libccc/text/stringarray/ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_uint		StringArrayASCII_Length(t_char const* const* strarr)
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



t_size		StringArrayASCII_TotalLength(t_char const* const* strarr, t_uint n)
{
	t_size	result;
	t_uint	i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (0);
	result = 0;
	i = 0;
	while (strarr[i] && i < n)
	{
		result += StringASCII_Length(strarr[i]);
		++i;
	}
	return (result);
}
