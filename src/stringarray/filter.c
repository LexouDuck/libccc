
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArray_Filter(t_char const** strarr, t_bool (*filter)(t_char const* str))
{
	t_char**	result;
	t_bool*	tmp;
	t_uint	result_length;
	t_uint	length;
	t_uint	i;

	HANDLE_ERROR(NULLPOINTER, (filter == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (NULL);)
	length = StringArray_Length(strarr);
	if (length == 0 || strarr == NULL)
		return ((t_char**)String_New(sizeof(void*)));
	tmp = (t_bool*)Memory_Allocate(sizeof(t_bool) * length);
	HANDLE_ERROR(ALLOCFAILURE, (tmp == NULL), return (NULL);)
	result_length = 0;
	for (i = 0; i < length; ++i)
	{
		tmp[i] = filter(strarr[i]);
		if (tmp[i])
			++result_length;
	}
	result = StringArray_New(result_length);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (result);)
	if (result_length == 0)
		return (result);
	t_uint	index = 0;
	for (i = 0; i < length; ++i)
	{
		if (tmp[i])
		{
			result[index++] = String_Duplicate(strarr[i]);
		}
		if (index >= result_length)
			break;
	}
	Memory_Free(tmp);
	return (result);
}


t_char**	StringArray_Filter_I(t_char const** strarr, t_bool (*filter)(t_char const* str, t_uint index))
{
	t_char**	result;
	t_bool*	tmp;
	t_uint	result_length;
	t_uint	length;
	t_uint	i;

	HANDLE_ERROR(NULLPOINTER, (filter == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (NULL);)
	length = StringArray_Length(strarr);
	if (length == 0 || strarr == NULL)
		return ((t_char**)String_New(sizeof(void*)));
	tmp = (t_bool*)Memory_Allocate(sizeof(t_bool) * length);
	HANDLE_ERROR(ALLOCFAILURE, (tmp == NULL), return (NULL);)
	result_length = 0;
	for (i = 0; i < length; ++i)
	{
		tmp[i] = filter(strarr[i], i);
		if (tmp[i])
			++result_length;
	}
	result = StringArray_New(result_length);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (result);)
	if (result_length == 0)
		return (result);
	t_uint	index = 0;
	for (i = 0; i < length; ++i)
	{
		if (tmp[i])
		{
			result[index++] = String_Duplicate(strarr[i]);
		}
		if (index >= result_length)
			break;
	}
	Memory_Free(tmp);
	return (result);
}
