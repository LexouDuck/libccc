
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8**	StringArrayUTF8_Replace(t_utf8 const* const* strarr, t_utf8 const* str_old, t_utf8 const* str_new)
{
	t_utf8**	result;
	t_uint		length;
	t_uint		i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	if CCCERROR((str_old == NULL), ERROR_NULLPOINTER, "string to replace given is NULL")
		return (NULL);
	if CCCERROR((str_new == NULL), ERROR_NULLPOINTER, "replacement string given is NULL")
		return (NULL);
	length = StringArrayUTF8_Length(strarr);
	result = StringArrayUTF8_Duplicate(strarr);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i < length; ++i)
	{
		if (StringUTF8_Equals(result[i], str_old))
		{
			StringUTF8_Free(result[i]);
			result[i] = StringUTF8_Duplicate(str_new);
		}
	}
	return (result);
}



t_utf8**	StringArrayUTF8_ReplaceFirst(t_utf8 const* const* strarr, t_utf8 const* str_old, t_utf8 const* str_new, t_uint n)
{
	t_utf8**	result;
	t_uint		length;
	t_uint		i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	if CCCERROR((str_old == NULL), ERROR_NULLPOINTER, "string to replace given is NULL")
		return (NULL);
	if CCCERROR((str_new == NULL), ERROR_NULLPOINTER, "replacement string given is NULL")
		return (NULL);
	length = StringArrayUTF8_Length(strarr);
	result = StringArrayUTF8_Duplicate(strarr);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i < length; ++i)
	{
		if (n == 0)
			return (result);
		if (StringUTF8_Equals(result[i], str_old))
		{
			StringUTF8_Free(result[i]);
			result[i] = StringUTF8_Duplicate(str_new);
			n -= 1;
		}
	}
	return (result);
}



t_utf8**	StringArrayUTF8_ReplaceLast(t_utf8 const* const* strarr, t_utf8 const* str_old, t_utf8 const* str_new, t_uint n)
{
	t_utf8**	result;
	t_uint		length;
	t_uint		i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	if CCCERROR((str_old == NULL), ERROR_NULLPOINTER, "string to replace given is NULL")
		return (NULL);
	if CCCERROR((str_new == NULL), ERROR_NULLPOINTER, "replacement string given is NULL")
		return (NULL);
	length = StringArrayUTF8_Length(strarr);
	result = StringArrayUTF8_Duplicate(strarr);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = length;
	while (i--)
	{
		if (n == 0)
			return (result);
		if (StringUTF8_Equals(result[i], str_old))
		{
			StringUTF8_Free(result[i]);
			result[i] = StringUTF8_Duplicate(str_new);
			n -= 1;
		}
	}
	return (result);
}
