
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8**	StringArrayUTF8_Copy(
	t_utf8** dest,            t_uint dest_i,
	t_utf8 const* const* src, t_uint src_i,
	t_uint length)
{
	t_uint	dest_length;
	t_uint	src_length;
	t_uint	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string array given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "source string array given is NULL")
		return (NULL);
	dest_length = StringArrayUTF8_Length((t_utf8 const* const*)dest);
	src_length  = StringArrayUTF8_Length(src);
	if CCCERROR((dest_i >= dest_length), ERROR_INDEX2LARGE, NULL)	return (NULL);
	if CCCERROR(( src_i >=  src_length), ERROR_INDEX2LARGE, NULL)	return (NULL);
	if (length == 0)
		length = src_length - src_i;
	if CCCERROR((dest_i + length > dest_length), ERROR_LENGTH2LARGE, NULL)	return (NULL);
	if CCCERROR(( src_i + length >  src_length), ERROR_LENGTH2LARGE, NULL)	return (NULL);
	for (i = 0; i < length; ++i)
	{
		StringUTF8_Free(dest[dest_i + i]);
		dest[dest_i + i] = StringUTF8_Duplicate(src[src_i + i]);
	}
	return (dest);
}
