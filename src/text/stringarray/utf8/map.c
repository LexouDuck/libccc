
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8**	StringArrayUTF8_Map(t_utf8 const* const* strarr,
	t_utf8* (*map)(t_utf8 const* str))
{
	t_utf8**	result;
	t_uint	i;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	result = StringArrayUTF8_New(StringArrayUTF8_Length(strarr));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; strarr[i]; ++i)
	{
		result[i] = map(strarr[i]);
	}
	return (result);
}



t_utf8**	StringArrayUTF8_Map_I(t_utf8 const* const* strarr,
	t_utf8* (*map)(t_utf8 const* str, t_uint index))
{
	t_utf8**	result;
	t_uint	i;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	result = StringArrayUTF8_New(StringArrayUTF8_Length(strarr));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; strarr[i]; ++i)
	{
		result[i] = map(strarr[i], i);
	}
	return (result);
}
