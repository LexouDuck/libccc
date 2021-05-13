
#include "libccc/monad/array.h"


_GENERIC()
T	CONCAT(Array_Get,T_NAME)(s_array_T const* array, t_uint index)
{
	LIBCONFIG_HANDLE_NULLPOINTER(T_DEFAULT, array)
	LIBCONFIG_HANDLE_NULLPOINTER(T_DEFAULT, array->items)
	if (index >= array->length)
		return (T_DEFAULT);
	return (array->items[index]);
}
