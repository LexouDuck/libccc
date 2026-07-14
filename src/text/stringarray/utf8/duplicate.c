
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8**	StringArrayUTF8_Duplicate(t_utf8 const* const* strarr)
{
	t_utf8**	result;
	t_uint	i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	result = StringArrayUTF8_New(StringArrayUTF8_Length(strarr));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (strarr[i])
	{
		result[i] = StringUTF8_Duplicate(strarr[i]);
		if CCCERROR((result[i] == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			StringArrayUTF8_Delete(&result);
			return (NULL);
		}
		++i;
	}
	return (result);
}
