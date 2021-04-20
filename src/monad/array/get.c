
#include "libccc/monad/array.h"



T	CONCAT(Array_T,_Get)(s_array_T const* array, t_uint index)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return (T_DEFAULT);
#endif
	if (index >= array->length)
		return (T_DEFAULT);
	return (array->items[index]);
}
