
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArray_Filter(t_char const* const* strarr, t_bool (*filter)(t_char const* str))
{
	t_char**	result;
	t_bool*	tmp;
	t_uint	result_length;
	t_uint	length;
	t_uint	i;

	if CCCERROR((filter == NULL), ERROR_NULLPOINTER, "filter() function given is NULL")
		return (NULL);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArray_Length(strarr);
	if (length == 0 || strarr == NULL)
		return ((t_char**)String_New(sizeof(void*)));
	tmp = (t_bool*)Memory_Allocate(sizeof(t_bool) * length);
	if CCCERROR((tmp == NULL), ERROR_ALLOCFAILURE, NULL) return (NULL);
	result_length = 0;
	for (i = 0; i < length; ++i)
	{
		tmp[i] = filter(strarr[i]);
		if (tmp[i])
			++result_length;
	}
	result = StringArray_New(result_length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL) return (result);
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


t_char**	StringArray_Filter_I(t_char const* const* strarr, t_bool (*filter)(t_char const* str, t_uint index))
{
	t_char**	result;
	t_bool*	tmp;
	t_uint	result_length;
	t_uint	length;
	t_uint	i;

	if CCCERROR((filter == NULL), ERROR_NULLPOINTER, "filter() function given is NULL")
		return (NULL);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArray_Length(strarr);
	if (length == 0 || strarr == NULL)
		return ((t_char**)String_New(sizeof(void*)));
	tmp = (t_bool*)Memory_Allocate(sizeof(t_bool) * length);
	if CCCERROR((tmp == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result_length = 0;
	for (i = 0; i < length; ++i)
	{
		tmp[i] = filter(strarr[i], i);
		if (tmp[i])
			++result_length;
	}
	result = StringArray_New(result_length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (result);
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
