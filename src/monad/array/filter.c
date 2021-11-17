
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array_T	CONCAT(Array_Filter,T_NAME)(s_array_T const* array, t_bool (*filter)(T item))
{
	s_array_T	result;// = CONCAT(NULL_ARRAY,T_NAME);
	t_bool*	tmp;
	t_uint	amount;
	t_uint	i;

	Memory_Clear(&result, sizeof(s_array_T));
	HANDLE_ERROR(NULLPOINTER, (filter == NULL), return (result);)
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (result);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (result);)
	tmp = (t_bool*)Memory_Allocate(sizeof(t_bool) * array->length);
	HANDLE_ERROR(ALLOCFAILURE, (tmp == NULL), return (result);)
	amount = 0;
	for (i = 0; i < array->length; ++i)
	{
		tmp[i] = filter(array->items[i]);
		if (tmp[i])
			++amount;
	}
	result.items = (T*)Memory_Allocate(sizeof(T) * amount);
	HANDLE_ERROR(ALLOCFAILURE, (result.items == NULL), return (result);)
	if (result.items == NULL)
		return (result);
	result.length = amount;
	amount = 0;
	for (i = 0; i < result.length; ++i)
	{
		if (tmp[i])
		{
			result.items[i] = array->items[i + amount];
		}
		else ++amount;
	}
	Memory_Free(tmp);
	return (result);
}


_GENERIC()
s_array_T	CONCAT(Array_Filter_I,T_NAME)(s_array_T const* array, t_bool (*filter)(T item, t_uint index))
{
	s_array_T	result;// = CONCAT(NULL_ARRAY,T_NAME);
	t_bool*	tmp;
	t_uint	amount;
	t_uint	i;

	Memory_Clear(&result, sizeof(s_array_T));
	HANDLE_ERROR(NULLPOINTER, (filter == NULL), return (result);)
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (result);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (result);)
	tmp = (t_bool*)Memory_Allocate(sizeof(t_bool) * array->length);
	HANDLE_ERROR(ALLOCFAILURE, (tmp == NULL), return (result);)
	amount = 0;
	for (i = 0; i < array->length; ++i)
	{
		tmp[i] = filter(array->items[i], i);
		if (tmp[i])
			++amount;
	}
	result.items = (T*)Memory_Allocate(sizeof(T) * amount);
	if (result.items == NULL)
		return (result);
	result.length = amount;
	amount = 0;
	for (i = 0; i < result.length; ++i)
	{
		if (tmp[i])
		{
			result.items[i] = array->items[i + amount];
		}
		else ++amount;
	}
	Memory_Free(tmp);
	return (result);
}
