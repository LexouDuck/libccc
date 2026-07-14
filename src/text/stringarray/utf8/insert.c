
#include "libccc/memory.h"
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8**	StringArrayUTF8_Insert(t_utf8** dest, t_utf8 const* str, t_uint index)
{
	t_utf8**	result;
	t_uint	length;
	t_uint	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string array given is NULL")
		return (NULL);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to insert given is NULL")
		return (NULL);
	length = StringArrayUTF8_Length((t_utf8 const* const*)dest);
	if CCCERROR((index > length), ERROR_INDEX2LARGE, NULL)
		return (NULL);
	result = StringArrayUTF8_New(length + 1);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i <= length; ++i)
	{
		if (i < index)
			result[i] = dest[i];
		else if (i == index)
			result[i] = StringUTF8_Duplicate(str);
		else
			result[i] = dest[i - 1];
	}
	Memory_Free(dest);
	return (result);
}
