
#include "libccc/monad/array.h"

#include LIBCONFIG_HANDLE_INCLUDE



_GENERIC()
T	CONCAT(Array_Get,T_NAME)(s_array_T const* array, t_uint index)
{
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (T_DEFAULT);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (T_DEFAULT);)
	if (index >= array->length)
		return (T_DEFAULT);
	return (array->items[index]);
}
