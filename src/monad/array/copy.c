
#include "libccc/monad/array.h"



s_array_T*	CONCAT(Array_T,_Copy)(s_array_T* dest, s_array_T const* src, t_uint n)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (dest == NULL || dest->items == NULL ||
		src == NULL || src->items == NULL)
		return (NULL);
#endif
	for (t_uint i = 0; i < n; ++i)
	{
		if (i >= dest->length || i >= src->length)
			return (dest);
		dest->items[i] = src->items[i];
	}
	return (dest);
}
