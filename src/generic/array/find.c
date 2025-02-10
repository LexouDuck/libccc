
#include "libccc/generic/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
T*	Array_Find(T)(s_array(T) const* array, T item)
{
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	if CCCERROR((array->length > 0 && array->items == NULL), ERROR_INVALIDARGS, "invalid array given")
		return (NULL);
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
			return (&(array->items[i]));
	}
	CCCERROR(TRUE, ERROR_NOTFOUND, NULL);
	return (NULL);
}


_GENERIC()
T*	Array_Find_F(T)(s_array(T) const* array, t_bool (*match)(T item))
{
	if CCCERROR((match == NULL), ERROR_NULLPOINTER, "match() function given is NULL")
		return (NULL);
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	if CCCERROR((array->length > 0 && array->items == NULL), ERROR_INVALIDARGS, "invalid array given")
		return (NULL);
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (match(array->items[i]))
			return (&(array->items[i]));
	}
	CCCERROR(TRUE, ERROR_NOTFOUND, NULL);
	return (NULL);
}


_GENERIC()
t_sint	Array_IndexOf(T)(s_array(T) const* array, T item)
{
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (ERROR);
	if CCCERROR((array->length > 0 && array->items == NULL), ERROR_INVALIDARGS, "invalid array given")
		return (ERROR);
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
			return (i);
	}
	CCCERROR(TRUE, ERROR_NOTFOUND, NULL);
	return (ERROR);
}


_GENERIC()
t_sint	Array_IndexOf_F(T)(s_array(T) const* array, t_bool (*match)(T item))
{
	if CCCERROR((match == NULL), ERROR_NULLPOINTER, "match() function given is NULL")
		return (ERROR);
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (ERROR);
	if CCCERROR((array->length > 0 && array->items == NULL), ERROR_INVALIDARGS, "invalid array given")
		return (ERROR);
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (match(array->items[i]))
			return (i);
	}
	CCCERROR(TRUE, ERROR_NOTFOUND, NULL);
	return (ERROR);
}
