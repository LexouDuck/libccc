
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**		StringArray_Map(t_char const* const* strarr,
	t_char* (*map)(t_char const* str))
{
	t_char**	result;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	result = StringArray_New(StringArray_Length(strarr));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
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

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	result = StringArray_New(StringArray_Length(strarr));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (t_uint i = 0; strarr[i]; ++i)
	{
		result[i] = map(strarr[i], i);
	}
	return (result);
}
