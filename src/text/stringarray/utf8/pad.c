
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8**	StringArrayUTF8_Pad_L(t_utf8 const* const* strarr, t_utf32 c, t_uint n)
{
	t_utf8**	result;
	t_uint	length;
	t_uint	i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArrayUTF8_Length(strarr);
	result = StringArrayUTF8_New(length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (strarr[i])
	{
		result[i] = StringUTF8_Pad_L(strarr[i], c, n);
		if CCCERROR((result[i] == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			StringArrayUTF8_Delete(&result);
			return (NULL);
		}
		++i;
	}
	result[i] = NULL;
	return (result);
}

// TODO StringArrayUTF8_Pad_R
// TODO StringArrayUTF8_Pad
