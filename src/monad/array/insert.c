
#include "libccc/memory.h"
#include "libccc/monad/array.h"



void	CONCAT(Array_T,_Insert)(s_array_T* array, T item, t_uint index)
{
	T*	result;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return;
#endif
	if (array->length < index)
		return;
	result = (T*)Memory_Alloc(sizeof(T) * (array->length + 1));
	if (result == NULL)
		return;
	for (t_uint i = 0; i <= array->length; ++i)
	{
		if (i < index)
			result[i] = array->items[i];
		else if (i == index)
			result[i] = item;
		else
			result[i] = array->items[i - 1];
	}
	Memory_Free(array->items);
	array->items = result;
	array->length += 1;
}
