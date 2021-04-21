
#include "libccc/monad/array.h"



T*	CONCAT(Array_T,_Find)(s_array_T const* array, T item)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return (NULL);
#endif
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
			return (&(array->items[i]));
	}
	return (NULL);
}



T*	CONCAT(Array_T,_Find_F)(s_array_T const* array, t_bool (*match)(T item))
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return (NULL);
#endif
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (match(array->items[i]))
			return (&(array->items[i]));
	}
	return (NULL);
}



t_sint	CONCAT(Array_T,_IndexOf)(s_array_T const* array, T item)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return (ERROR);
#endif
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
			return (i);
	}
	return (ERROR);
}



t_sint	CONCAT(Array_T,_IndexOf_F)(s_array_T const* array, t_bool (*match)(T item))
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return (ERROR);
#endif
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (match(array->items[i]))
			return (i);
	}
	return (ERROR);
}
