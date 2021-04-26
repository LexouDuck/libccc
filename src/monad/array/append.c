
#include "libccc/memory.h"
#include "libccc/monad/array.h"



_GENERIC()
void	CONCAT(Array_Append,T_NAME)(s_array_T* array, T item)
{
	T*	result;

	LIBCONFIG_HANDLE_NULLPOINTER(array, )
	LIBCONFIG_HANDLE_NULLPOINTER(array->items, )
	result = (T*)Memory_Alloc(sizeof(T) * (array->length + 1));
	if (result == NULL)
		return;
	for (t_uint i = 0; i < array->length; ++i)
	{
		result[i] = array->items[i];
	}
	result[array->length] = item;
	Memory_Free(array->items);
	array->items = result;
	array->length += 1;
}
