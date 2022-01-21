
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArray_Reverse(t_char const* const* strarr)
{
	t_char**	result;
	t_uint	length;
	t_uint	index;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (NULL);)
	length = StringArray_Length(strarr);
	HANDLE_ERROR(NULLPOINTER, (length > 0 && strarr == NULL), return (NULL);)
	result = StringArray_New(length);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	index = length - 1;
	for (t_uint i = 0; i < length; ++i, --index)
	{
		result[i] = String_Duplicate(strarr[index]);
	}
	return (result);
}
