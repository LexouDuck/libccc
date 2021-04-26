
#include "libccc/monad/array.h"


_GENERIC()
T	CONCAT(Array_Get,T_NAME)(s_array_T const* array, t_uint index)
{
	LIBCONFIG_HANDLE_NULLPOINTER(array, T_DEFAULT)
	LIBCONFIG_HANDLE_NULLPOINTER(array->items, T_DEFAULT)
	if (index >= array->length)
		return (T_DEFAULT);
	return (array->items[index]);
}
