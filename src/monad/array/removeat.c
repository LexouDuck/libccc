
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	Array_RemoveAt(T)(s_array(T)* array, t_uint index)
{
	T*	result;

	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return;
	if CCCERROR((array->length > 0 && array->items == NULL), ERROR_INVALIDARGS, "array given is invalid")
		return;
	if CCCERROR((array->length <= index), ERROR_INDEX2LARGE, 
		"index given (" SF_UINT ") is beyond end of array (length: " SF_UINT ")", index, array->length)
		return;
	array->length -= 1;
	if (array->length == 0)
	{
		Memory_Free(array->items);
		array->items = NULL;
		return;
	}
	result = (T*)Memory_Allocate(sizeof(T) * array->length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return;
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
void	Array_RemoveAt_F(T)(s_array(T)* array, t_uint index, void (*del)(T))
{
	T*	result;

	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "delete() function given is NULL")
		return;
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return;
	if CCCERROR((array->length > 0 && array->items == NULL), ERROR_INVALIDARGS, "array given is invalid")
		return;
	if CCCERROR((array->length <= index), ERROR_INDEX2LARGE, 
		"index given (" SF_UINT ") is beyond end of array (length: " SF_UINT ")", index, array->length)
		return;
	array->length -= 1;
	if (array->length == 0)
	{
		Memory_Free(array->items);
		array->items = NULL;
		return;
	}
	result = (T*)Memory_Allocate(sizeof(T) * array->length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return;
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (i < index)
			result[i] = array->items[i];
		else if (i == index)
		{
			del(array->items[i]);
			result[i] = array->items[i + 1];
		}
		else
			result[i] = array->items[i + 1];
	}
	Memory_Free(array->items);
	array->items = result;
}
