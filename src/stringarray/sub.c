
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArray_Sub(t_char const* const* strarr, t_uint index, t_uint n)
{
	t_char**		result;
	t_uint		length;
	t_uint		i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArray_Length(strarr);
	if CCCERROR((index > length), ERROR_INDEX2LARGE, NULL)
		return (NULL);
	if CCCERROR((index + n > length), ERROR_LENGTH2LARGE, NULL)
		return (NULL);
	result = StringArray_New(n);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		result[i] = String_Duplicate(strarr[index + i]);
		if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			StringArray_Delete(&result);
			return (NULL);
		}
		++i;
	}
	result[i] = NULL;
	return (result);
}
