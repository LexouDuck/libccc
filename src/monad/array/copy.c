
#include "libccc/monad/array.h"


_GENERIC()
s_array_T*	CONCAT(Array_Copy,T_NAME)(s_array_T* dest, s_array_T const* src, t_uint n)
{
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, dest)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, dest->items)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, src)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, src->items)
	for (t_uint i = 0; i < n; ++i)
	{
		if (i >= dest->length || i >= src->length)
			return (dest);
		dest->items[i] = src->items[i];
	}
	return (dest);
}
