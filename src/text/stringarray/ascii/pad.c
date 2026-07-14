
#include "libccc/memory.h"
#include "libccc/text/string/ascii.h"
#include "libccc/text/stringarray/ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArrayASCII_Pad_L(t_char const* const* strarr, t_char const c, t_uint n)
{
	t_char**		result;
	t_uint		strarr_length;
	t_uint		i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	strarr_length = StringArrayASCII_Length(strarr);
	result = StringArrayASCII_New(strarr_length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (strarr[i])
	{
		result[i] = StringASCII_Pad_L(strarr[i], c, n);
		if CCCERROR((result[i] == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			StringArrayASCII_Delete(&result);
			return (NULL);
		}
		++i;
	}
	result[i] = NULL;
	return (result);
}

// TODO StringArrayASCII_Pad_R
// TODO StringArrayASCII_Pad
