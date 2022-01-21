
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
T*	Array_Find(T)(s_array(T) const* array, T item)
{
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (NULL);)
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
			return (&(array->items[i]));
	}
	HANDLE_ERROR(NOTFOUND, (TRUE), return (NULL);)
}


_GENERIC()
T*	Array_Find_F(T)(s_array(T) const* array, t_bool (*match)(T item))
{
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (NULL);)
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (match(array->items[i]))
			return (&(array->items[i]));
	}
	HANDLE_ERROR(NOTFOUND, (TRUE), return (NULL);)
}


_GENERIC()
t_sint	Array_IndexOf(T)(s_array(T) const* array, T item)
{
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (ERROR);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (ERROR);)
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
			return (i);
	}
	HANDLE_ERROR(NOTFOUND, (TRUE), return (ERROR);)
}


_GENERIC()
t_sint	Array_IndexOf_F(T)(s_array(T) const* array, t_bool (*match)(T item))
{
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (ERROR);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (ERROR);)
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (match(array->items[i]))
			return (i);
	}
	HANDLE_ERROR(NOTFOUND, (TRUE), return (ERROR);)
}
