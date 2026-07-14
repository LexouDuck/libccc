
#include "libccc/memory.h"
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8**	StringArrayUTF8_Wedge(t_utf8** dest, t_utf8 const** src, t_uint index)
{
	t_utf8**	result;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string array given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "string array to insert given is NULL")
		return (NULL);
	if CCCERROR((index > StringArrayUTF8_Length((t_utf8 const* const*)dest)), ERROR_INDEX2LARGE, NULL)
		return (NULL);
	result = StringArrayUTF8_Sub((t_utf8 const* const*)dest, 0, index);
	StringArrayUTF8_Append(&result, (t_utf8 const* const*)src);
	StringArrayUTF8_Append(&result, (t_utf8 const* const*)(dest + index));
	StringArrayUTF8_Free(dest);
	return (result);
}
