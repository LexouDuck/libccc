
#include "libccc/monad/array.h"


_GENERIC()
void	CONCAT(Array_Set,T_NAME)(s_array_T* array, t_uint index, T item)
{
	LIBCONFIG_HANDLE_NULLPOINTER(array, )
	LIBCONFIG_HANDLE_NULLPOINTER(array->items, )
	if (index >= array->length)
		return;
	array->items[index] = item;
}
