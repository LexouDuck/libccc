
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArray_Wedge(t_char** dest, t_char const** src, t_uint index)
{
	t_char**	result;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string array given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "string array to insert given is NULL")
		return (NULL);
	result = StringArray_Sub((t_char const**)dest, 0, index);
	StringArray_Append(&result, src);
	StringArray_Append(&result, (t_char const**)dest + index);
	StringArray_Free(dest);
	return (result);
}
