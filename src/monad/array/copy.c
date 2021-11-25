
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array_T*	CONCAT(Array_Copy,T_NAME)(
	s_array_T* dest,      t_uint dest_i,
	s_array_T const* src, t_uint src_i,
	t_uint n)
{
	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, ( src == NULL), return (NULL);)
	HANDLE_ERROR(INDEX2LARGE, (dest_i >= dest->length),    return (NULL);)
	HANDLE_ERROR(INDEX2LARGE, ( src_i >=  src->length),    return (NULL);)
	HANDLE_ERROR(LENGTH2LARGE, (dest_i + n > dest->length), return (NULL);)
	HANDLE_ERROR(LENGTH2LARGE, ( src_i + n >  src->length), return (NULL);)
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
