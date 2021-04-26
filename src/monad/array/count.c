
#include "libccc/monad/array.h"


_GENERIC()
t_uint	CONCAT(Array_Count,T_NAME)(s_array_T const* array, T item)
{
	t_uint	result = 0;

	LIBCONFIG_HANDLE_NULLPOINTER(array, 0)
	LIBCONFIG_HANDLE_NULLPOINTER(array->items, 0)
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
			result += 1;
	}
	return (result);
}
