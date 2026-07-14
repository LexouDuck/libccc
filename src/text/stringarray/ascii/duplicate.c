
#include "libccc/memory.h"
#include "libccc/text/string/ascii.h"
#include "libccc/text/stringarray/ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**		StringArrayASCII_Duplicate(t_char const* const* strarr)
{
	t_uint	i;
	t_char**	result;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	result = StringArrayASCII_New(StringArrayASCII_Length(strarr));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (strarr[i])
	{
		result[i] = StringASCII_Duplicate(strarr[i]);
		++i;
	}
	return (result);
}
