
#include "libccc/monad/array.h"


_GENERIC()
void	CONCAT(Array_Set,T_NAME)(s_array_T* array, t_uint index, T item)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL)
		return;
#endif
	if (index >= array->length)
		return;
	array->items[index] = item;
}
