
#include "libccc/memory.h"
#include "libccc/monad/array.h"


_GENERIC()
void	CONCAT(Array_RemoveAll,T_NAME)(s_array_T* array, T item)
{
	T*	result;
	t_uint	i;
	t_uint	amount;

	LIBCONFIG_HANDLE_NULLPOINTER(, array)
	LIBCONFIG_HANDLE_NULLPOINTER(, array->items)
	if (array->length == 0)
		return;
	amount = 0;
	for (i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
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
		if (T_EQUALS(array->items[i], item))
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


_GENERIC()
void	CONCAT(Array_RemoveAll_F,T_NAME)(s_array_T* array, T item, void (*delete)(T))
{
	T*	result;
	t_uint	i;
	t_uint	amount;

	LIBCONFIG_HANDLE_NULLPOINTER(, array)
	LIBCONFIG_HANDLE_NULLPOINTER(, array->items)
	if (array->length == 0)
		return;
	amount = 0;
	for (i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
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
		if (T_EQUALS(array->items[i], item))
		{
			delete(array->items[i]);
			++amount;
			continue;
		}
		result[i] = array->items[i + amount];
	}
	Memory_Free(array->items);
	array->items = result;
	array->length = i;
}
