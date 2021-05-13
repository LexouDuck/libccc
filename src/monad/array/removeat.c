
#include "libccc/memory.h"
#include "libccc/monad/array.h"


_GENERIC()
void	CONCAT(Array_RemoveAt,T_NAME)(s_array_T* array, t_uint index)
{
	T*	result;

	LIBCONFIG_HANDLE_NULLPOINTER(, array)
	LIBCONFIG_HANDLE_NULLPOINTER(, array->items)
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
		else
			result[i] = array->items[i + 1];
	}
	Memory_Free(array->items);
	array->items = result;
	array->length -= 1;
}


_GENERIC()
void	CONCAT(Array_RemoveAt_F,T_NAME)(s_array_T* array, t_uint index, void (*delete)(T))
{
	T*	result;

	LIBCONFIG_HANDLE_NULLPOINTER(, array)
	LIBCONFIG_HANDLE_NULLPOINTER(, array->items)
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
		{
			delete(array->items[i]);
			result[i] = array->items[i + 1];
		}
		else
			result[i] = array->items[i + 1];
	}
	Memory_Free(array->items);
	array->items = result;
	array->length -= 1;
}
