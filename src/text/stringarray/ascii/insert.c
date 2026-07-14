
#include "libccc/memory.h"
#include "libccc/text/string/ascii.h"
#include "libccc/text/stringarray/ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArrayASCII_Insert(t_char** dest, t_char const* str, t_uint index)
{
	t_char**	result;
	t_uint	length;
	t_uint	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string array given is NULL")
		return (NULL);
	if CCCERROR((str  == NULL), ERROR_NULLPOINTER, "string to insert given is NULL")
		return (NULL);
	length = StringArrayASCII_Length((t_char const**)dest);
	if CCCERROR((index > length), ERROR_INDEX2LARGE, NULL)
		return (NULL);
	result = StringArrayASCII_New(length + 1);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i <= length; ++i)
	{
		if (i < index)
			result[i] = dest[i];
		else if (i == index)
			result[i] = StringASCII_Duplicate(str);
		else
			result[i] = dest[i - 1];
	}
	StringArrayASCII_Free(dest);
	return (result);
}
