
#include "libccc/monad/array.h"

#include LIBCONFIG_HANDLE_INCLUDE



_GENERIC()
void	CONCAT(Array_Set,T_NAME)(s_array_T* array, t_uint index, T item)
{
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return;)
	if (index >= array->length)
		return;
	array->items[index] = item;
}
