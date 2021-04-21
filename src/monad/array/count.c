
#include "libccc/monad/array.h"


_GENERIC()
t_uint	CONCAT(Array_T,_Count)(s_array_T const* array, T item)
{
	t_uint	result = 0;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return (0);
#endif
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
			result += 1;
	}
	return (result);
}
