
#include "libccc/memory.h"
#include "libccc/monad/array.h"


_GENERIC()
s_array_T	CONCAT(Array_Filter,T_NAME)(s_array_T const* array, t_bool (*filter)(T item))
{
	s_array_T	result = {0};
	t_bool*	tmp;
	t_uint	amount;
	t_uint	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL || filter == NULL)
		return (result);
#endif
	tmp = (t_bool*)Memory_Alloc(sizeof(t_bool) * array->length);
	if (tmp == NULL)
		return (result);
	amount = 0;
	for (i = 0; i < array->length; ++i)
	{
		tmp[i] = filter(array->items[i]);
		if (tmp[i])
			++amount;
	}
	result.items = (T*)Memory_Alloc(sizeof(T) * amount);
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
	s_array_T	result = {0};
	t_bool*	tmp;
	t_uint	amount;
	t_uint	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL || filter == NULL)
		return (result);
#endif
	tmp = (t_bool*)Memory_Alloc(sizeof(t_bool) * array->length);
	if (tmp == NULL)
		return (result);
	amount = 0;
	for (i = 0; i < array->length; ++i)
	{
		tmp[i] = filter(array->items[i], i);
		if (tmp[i])
			++amount;
	}
	result.items = (T*)Memory_Alloc(sizeof(T) * amount);
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
