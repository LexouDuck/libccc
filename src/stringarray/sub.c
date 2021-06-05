
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArray_Sub(t_char const** strarr, t_uint index, t_uint n)
{
	t_char**		result;
	t_uint		length;
	t_uint		i;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (NULL);)
	length = StringArray_Length(strarr);
	HANDLE_ERROR(INDEX2LARGE, (index > length), return (NULL);)
	HANDLE_ERROR(LENGTH2LARGE, (index + n > length), return (NULL);)
	result = StringArray_New(n);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	while (i < n)
	{
		result[i] = String_Duplicate(strarr[index + i]);
		HANDLE_ERROR(ALLOCFAILURE, (result == NULL),
		{
			StringArray_Delete(&result);
			return (NULL);
		})
		++i;
	}
	result[i] = NULL;
	return (result);
}
