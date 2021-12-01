
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	Array_RemoveAt(T)(s_array(T)* array, t_uint index)
{
	T*	result;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return;)
	HANDLE_ERROR_SF(INDEX2LARGE, (array->length <= index), return;,
		", index given ("SF_UINT") is beyond end of array (length: "SF_UINT")",
		index, array->length)
	array->length -= 1;
	if (array->length == 0)
	{
		Memory_Free(array->items);
		array->items = NULL;
		return;
	}
	result = (T*)Memory_Allocate(sizeof(T) * array->length);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return;)
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (i < index)
			result[i] = array->items[i];
		else
			result[i] = array->items[i + 1];
	}
	Memory_Free(array->items);
	array->items = result;
}


_GENERIC()
void	Array_RemoveAt_F(T)(s_array(T)* array, t_uint index, void (*delete)(T))
{
	T*	result;

	HANDLE_ERROR(NULLPOINTER, (delete == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return;)
	HANDLE_ERROR_SF(INDEX2LARGE, (array->length <= index), return;,
		", index given ("SF_UINT") is beyond end of array (length: "SF_UINT")",
		index, array->length)
	array->length -= 1;
	if (array->length == 0)
	{
		Memory_Free(array->items);
		array->items = NULL;
		return;
	}
	result = (T*)Memory_Allocate(sizeof(T) * array->length);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return;)
	for (t_uint i = 0; i < array->length; ++i)
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
}
