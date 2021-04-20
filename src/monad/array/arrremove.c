
#include "libccc/memory.h"
#include "libccc/monad/array.h"



void	CONCAT(Array_T,_Remove)(s_array_T* array, t_uint index)
{
	T*	result;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return;
#endif
	if (array->length == 0 ||
		array->length <= index)
		return;
	result = (T*)Memory_Alloc(sizeof(T) * (array->length - 1));
	if (result == NULL)
		return;
	for (t_uint i = 0; i < array->length - 1; ++i)
	{
		if (i < index)
			result[i] = array->items[i];
		else if (i == index)
			continue;
		else
			result[i] = array->items[i + 1];
	}
	Memory_Free(array->items);
	array->items = result;
	array->length -= 1;
}



void	CONCAT(Array_T,_RemoveAll)(s_array_T* array, T target)
{
	T*	result;
	t_uint	i;
	t_uint	amount;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return;
#endif
	if (array->length == 0)
		return;
	amount = 0;
	for (i = 0; i < array->length; ++i)
	{
		if (array->items[i] == target)
		{
			++amount;
		}
	}
	if (array->length == amount)
	{
		Memory_Free(array->items);
		array->items = NULL;
		array->length = 0;
		return;
	}
	result = (T*)Memory_Alloc(sizeof(T) * (array->length - amount));
	if (result == NULL)
		return;
	amount = 0;
	for (i = 0; i < array->length; ++i)
	{
		if (array->items[i] == target)
		{
			++amount;
			continue;
		}
		result[i] = array->items[i + amount];
	}
	Memory_Free(array->items);
	array->items = result;
	array->length = i;
}
