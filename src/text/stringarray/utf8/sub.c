
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8**	StringArrayUTF8_Sub(t_utf8 const* const* strarr, t_uint start, t_uint length)
{
	t_utf8**	result;
	t_uint	total;
	t_uint	i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	total = StringArrayUTF8_Length(strarr);
	if CCCERROR((start > total), ERROR_INDEX2LARGE, NULL)
		return (NULL);
	if CCCERROR((start + length > total), ERROR_LENGTH2LARGE, NULL)
		return (NULL);
	result = StringArrayUTF8_New(length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = StringUTF8_Duplicate(strarr[start + i]);
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
