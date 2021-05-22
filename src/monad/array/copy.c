
#include "libccc/monad/array.h"

#include LIBCONFIG_HANDLE_INCLUDE



_GENERIC()
s_array_T*	CONCAT(Array_Copy,T_NAME)(s_array_T* dest, s_array_T const* src, t_uint n)
{
	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (dest->items == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src->items == NULL), return (NULL);)
	for (t_uint i = 0; i < n; ++i)
	{
		if (i >= dest->length || i >= src->length)
			return (dest);
		dest->items[i] = src->items[i];
	}
	return (dest);
}
