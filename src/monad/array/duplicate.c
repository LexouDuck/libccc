
#include "libccc/memory.h"
#include "libccc/monad/array.h"


_GENERIC()
s_array_T	CONCAT(Array_Duplicate,T_NAME)(s_array_T const* array)
{
	s_array_T	result = {0};

	LIBCONFIG_HANDLE_NULLPOINTER(array, result)
	LIBCONFIG_HANDLE_NULLPOINTER(array->items, result)
	result.items = (T*)Memory_Duplicate(array->items, sizeof(T) * array->length);
	if (result.items)
		result.length = array->length;
	return (result);
}
