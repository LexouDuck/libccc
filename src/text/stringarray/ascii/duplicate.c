
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**		StringArray_Duplicate(t_char const* const* strarr)
{
	t_uint	i;
	t_char**	result;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	result = StringArray_New(StringArray_Length(strarr));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (strarr[i])
	{
		result[i] = String_Duplicate(strarr[i]);
		++i;
	}
	return (result);
}
