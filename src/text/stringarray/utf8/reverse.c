
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8**	StringArrayUTF8_Reverse(t_utf8 const* const* strarr)
{
	t_utf8**	result;
	t_uint	length;
	t_uint	index;
	t_uint	i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArrayUTF8_Length(strarr);
	result = StringArrayUTF8_New(length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	index = length - 1;
	for (i = 0; i < length; ++i, --index)
	{
		result[i] = StringUTF8_Duplicate(strarr[index]);
	}
	return (result);
}
