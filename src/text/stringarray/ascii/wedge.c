
#include "libccc/memory.h"
#include "libccc/text/string/ascii.h"
#include "libccc/text/stringarray/ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArrayASCII_Wedge(t_char** dest, t_char const** src, t_uint index)
{
	t_char**	result;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string array given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "string array to insert given is NULL")
		return (NULL);
	result = StringArrayASCII_Sub((t_char const**)dest, 0, index);
	StringArrayASCII_Append(&result, src);
	StringArrayASCII_Append(&result, (t_char const**)dest + index);
	StringArrayASCII_Free(dest);
	return (result);
}
