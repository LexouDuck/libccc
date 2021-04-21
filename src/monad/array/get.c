
#include "libccc/monad/array.h"


_GENERIC()
T	CONCAT(Array_Get,T_NAME)(s_array_T const* array, t_uint index)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return (T_DEFAULT);
#endif
	if (index >= array->length)
		return (T_DEFAULT);
	return (array->items[index]);
}
