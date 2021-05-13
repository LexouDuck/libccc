
#include "libccc/monad/array.h"


_GENERIC()
T*	CONCAT(Array_Find,T_NAME)(s_array_T const* array, T item)
{
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, array)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, array->items)
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
			return (&(array->items[i]));
	}
	return (NULL);
}


_GENERIC()
T*	CONCAT(Array_Find_F,T_NAME)(s_array_T const* array, t_bool (*match)(T item))
{
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, array)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, array->items)
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (match(array->items[i]))
			return (&(array->items[i]));
	}
	return (NULL);
}


_GENERIC()
t_sint	CONCAT(Array_IndexOf,T_NAME)(s_array_T const* array, T item)
{
	LIBCONFIG_HANDLE_NULLPOINTER(ERROR, array)
	LIBCONFIG_HANDLE_NULLPOINTER(ERROR, array->items)
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
			return (i);
	}
	return (ERROR);
}


_GENERIC()
t_sint	CONCAT(Array_IndexOf_F,T_NAME)(s_array_T const* array, t_bool (*match)(T item))
{
	LIBCONFIG_HANDLE_NULLPOINTER(ERROR, array)
	LIBCONFIG_HANDLE_NULLPOINTER(ERROR, array->items)
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (match(array->items[i]))
			return (i);
	}
	return (ERROR);
}
