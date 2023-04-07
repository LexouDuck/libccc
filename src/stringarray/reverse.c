
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArray_Reverse(t_char const* const* strarr)
{
	t_char**	result;
	t_uint	length;
	t_uint	index;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArray_Length(strarr);
	result = StringArray_New(length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	index = length - 1;
	for (t_uint i = 0; i < length; ++i, --index)
	{
		result[i] = String_Duplicate(strarr[index]);
	}
	return (result);
}
