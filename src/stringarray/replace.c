
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArray_Replace(t_char const** strarr, t_char const* old, t_char const* new)
{
	t_char**	result;
	t_uint		length;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (NULL);)
	length = StringArray_Length(strarr);
	result = StringArray_Duplicate(strarr);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	if (result == NULL)
		return (result);
	for (t_uint i = 0; i < length; ++i)
	{
		if (result[i] == old)
		{
			result[i] = (void*)new;
		}
	}
	return (result);
}



t_char**	StringArray_ReplaceFirst(t_char const** strarr, t_char const* old, t_char const* new, t_uint n)
{
	t_char**	result;
	t_uint		length;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (NULL);)
	length = StringArray_Length(strarr);
	result = StringArray_Duplicate(strarr);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	if (result == NULL)
		return (result);
	for (t_uint i = 0; i < length; ++i)
	{
		if (n == 0)
			return (result);
		if (result[i] == old)
		{
			result[i] = (void*)new;
			n -= 1;
		}
	}
	return (result);
}



t_char**	StringArray_ReplaceLast(t_char const** strarr, t_char const* old, t_char const* new, t_uint n)
{
	t_char**	result;
	t_uint		length;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (NULL);)
	length = StringArray_Length(strarr);
	result = StringArray_Duplicate(strarr);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	if (result == NULL)
		return (result);
	t_uint i = length;
	while (i--)
	{
		if (n == 0)
			return (result);
		if (result[i] == old)
		{
			result[i] = (void*)new;
			n -= 1;
		}
	}
	return (result);
}