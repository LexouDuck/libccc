
#include "libccc/memory.h"
#include "libccc/text/string/ascii.h"
#include "libccc/text/stringarray/ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArrayASCII_Copy(
	t_char** dest,            t_uint dest_i,
	t_char const* const* src, t_uint src_i,
	t_uint n)
{
	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string array given is NULL")
		return (NULL);
	if CCCERROR(( src == NULL), ERROR_NULLPOINTER, "source string array given is NULL")
		return (NULL);
	t_uint	dest_length = StringArrayASCII_Length((t_char const**)dest);
	t_uint	src_length  = StringArrayASCII_Length((t_char const**)src);
	if CCCERROR((dest_i >= dest_length), ERROR_INDEX2LARGE, NULL)	return (NULL);
	if CCCERROR(( src_i >=  src_length), ERROR_INDEX2LARGE, NULL)	return (NULL);
	if CCCERROR((dest_i + n > dest_length), ERROR_LENGTH2LARGE, NULL)	return (NULL);
	if CCCERROR(( src_i + n >  src_length), ERROR_LENGTH2LARGE, NULL)	return (NULL);
	if (n == 0)
		n = src_length - src_i;
	for (t_uint i = 0; i < n; ++i)
	{
		if (dest_i + i >= dest_length)
			return (dest);
		StringASCII_Free(dest[dest_i + i]);
		dest[dest_i + i] = StringASCII_Duplicate(src[src_i + i]);
	}
	return (dest);
}
