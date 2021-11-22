
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	CONCAT(Array_Remove,T_NAME)(s_array_T* array, T item)
{
	t_sint	index;
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return;)
	index = CONCAT(Array_IndexOf,T_NAME)(array, item);
	if (index == ERROR)
		return;
	CONCAT(Array_RemoveAt,T_NAME)(array, index);
}



_GENERIC()
void	CONCAT(Array_Remove_F,T_NAME)(s_array_T* array, T item, void (*delete)(T))
{
	t_sint	index;
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return;)
	index = CONCAT(Array_IndexOf,T_NAME)(array, item);
	if (index == ERROR)
		return;
	CONCAT(Array_RemoveAt_F,T_NAME)(array, index, delete);
}



_GENERIC()
void	CONCAT(Array_RemoveAll,T_NAME)(s_array_T* array, T item)
{
	T*	result;
	t_uint	i;
	t_uint	amount;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return;)
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
	result = (T*)Memory_Allocate(sizeof(T) * (array->length - amount));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return;)
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

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return;)
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
	result = (T*)Memory_Allocate(sizeof(T) * (array->length - amount));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return;)
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
