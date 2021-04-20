
#include "libccc/memory.h"
#include "libccc/monad/array.h"



void	CONCAT(Array_T,_Prepend)(s_array_T* array, T item)
{
	T*	result;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return;
#endif
	result = (T*)Memory_Alloc(sizeof(T) * (array->length + 1));
	if (result == NULL)
		return;
	result[0] = item;
	for (t_uint i = 0; i < array->length; ++i)
	{
		result[i + 1] = array->items[i];
	}
	Memory_Free(array->items);
	array->items = result;
	array->length += 1;
}
