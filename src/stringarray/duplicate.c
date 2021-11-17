
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**		StringArray_Duplicate(t_char const** strarr)
{
	t_uint	i;
	t_char**	result;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (*strarr == NULL), return (NULL);)
	result = StringArray_New(StringArray_Length(strarr));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	while (strarr[i])
	{
		result[i] = String_Duplicate(strarr[i]);
		++i;
	}
	return (result);
}
