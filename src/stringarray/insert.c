
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArray_Insert(t_char** dest, t_char const* str, t_uint index)
{
	t_char**	result;
	t_size	length;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string array given is NULL")
		return (NULL);
	if CCCERROR((str  == NULL), ERROR_NULLPOINTER, "string to insert given is NULL")
		return (NULL);
	length = StringArray_Length((t_char const**)dest);
	result = StringArray_New(length + 1);
	for (t_uint i = 0; i <= length; ++i)
	{
		if (i < index)
			result[i] = dest[i];
		else if (i == index)
			result[i] = String_Duplicate(str);
		else
			result[i] = dest[i - 1];
	}
	StringArray_Free(dest);
	return (result);
}
