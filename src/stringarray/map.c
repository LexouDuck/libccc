
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**		StringArray_Map(t_char const* const* strarr,
	t_char* (*map)(t_char const* str))
{
	t_char**	result;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (map == NULL), return (NULL);)
	result = StringArray_New(StringArray_Length(strarr));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	for (t_uint i = 0; strarr[i]; ++i)
	{
		result[i] = map(strarr[i]);
	}
	return (result);
}



t_char**		StringArray_Map_I(t_char const* const* strarr,
	t_char* (*map)(t_char const* str, t_uint index))
{
	t_char**	result;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (map == NULL), return (NULL);)
	result = StringArray_New(StringArray_Length(strarr));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	for (t_uint i = 0; strarr[i]; ++i)
	{
		result[i] = map(strarr[i], i);
	}
	return (result);
}
