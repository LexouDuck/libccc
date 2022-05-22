
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Copy(T)(
	s_array(T)* dest,      t_uint dest_i,
	s_array(T) const* src, t_uint src_i,
	t_uint n)
{
	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination array given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "source array given is NULL")
		return (NULL);
	if CCCERROR((dest_i >= dest->length), ERROR_INDEX2LARGE, NULL)	return (NULL);
	if CCCERROR(( src_i >=  src->length), ERROR_INDEX2LARGE, NULL)	return (NULL);
	if CCCERROR((dest_i + n > dest->length), ERROR_LENGTH2LARGE, NULL)	return (NULL);
	if CCCERROR(( src_i + n >  src->length), ERROR_LENGTH2LARGE, NULL)	return (NULL);
	if (n == 0)
		n = src->length - src_i;
	for (t_uint i = 0; i < n; ++i)
	{
		if (dest_i + i >= dest->length)
			return (dest);
		dest->items[dest_i + i] = src->items[src_i + i];
	}
	return (dest);
}
