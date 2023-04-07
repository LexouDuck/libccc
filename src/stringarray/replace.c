
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArray_Replace(t_char const* const* strarr, t_char const* str_old, t_char const* str_new)
{
	t_char**	result;
	t_uint		length;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArray_Length(strarr);
	result = StringArray_Duplicate(strarr);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if (result == NULL)
		return (result);
	for (t_uint i = 0; i < length; ++i)
	{
		if (result[i] == str_old)
		{
			result[i] = (t_char*)str_new;
		}
	}
	return (result);
}



t_char**	StringArray_ReplaceFirst(t_char const* const* strarr, t_char const* str_old, t_char const* str_new, t_uint n)
{
	t_char**	result;
	t_uint		length;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArray_Length(strarr);
	result = StringArray_Duplicate(strarr);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if (result == NULL)
		return (result);
	for (t_uint i = 0; i < length; ++i)
	{
		if (n == 0)
			return (result);
		if (result[i] == str_old)
		{
			result[i] = (t_char*)str_new;
			n -= 1;
		}
	}
	return (result);
}



t_char**	StringArray_ReplaceLast(t_char const* const* strarr, t_char const* str_old, t_char const* str_new, t_uint n)
{
	t_char**	result;
	t_uint		length;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArray_Length(strarr);
	result = StringArray_Duplicate(strarr);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if (result == NULL)
		return (result);
	t_uint i = length;
	while (i--)
	{
		if (n == 0)
			return (result);
		if (result[i] == str_old)
		{
			result[i] = (t_char*)str_new;
			n -= 1;
		}
	}
	return (result);
}
