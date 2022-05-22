
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Replace(T)(s_array(T) const* array, T item_old, T item_new)
{
	s_array(T)*	result;

	if CCCERROR((array == NULL), ERROR_NULLPOINTER, NULL) return (NULL);
	result = Array_Duplicate(T)(array);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if (result->items == NULL)
		return (result);
	result->length = array->length;
	for (t_uint i = 0; i < result->length; ++i)
	{
		if (T_EQUALS(result->items[i], item_old))
		{
			result->items[i] = item_new;
		}
	}
	return (result);
}



_GENERIC()
s_array(T)*	Array_ReplaceFirst(T)(s_array(T) const* array, T item_old, T item_new, t_uint n)
{
	s_array(T)*	result;

	if CCCERROR((array == NULL), ERROR_NULLPOINTER, NULL) return (NULL);
	result = Array_Duplicate(T)(array);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if (result->items == NULL)
		return (result);
	result->length = array->length;
	for (t_uint i = 0; i < result->length; ++i)
	{
		if (n == 0)
			return (result);
		if (T_EQUALS(result->items[i], item_old))
		{
			result->items[i] = item_new;
			n -= 1;
		}
	}
	return (result);
}



_GENERIC()
s_array(T)*	Array_ReplaceLast(T)(s_array(T) const* array, T item_old, T item_new, t_uint n)
{
	s_array(T)*	result;

	if CCCERROR((array == NULL), ERROR_NULLPOINTER, NULL) return (NULL);
	result = Array_Duplicate(T)(array);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if (result->items == NULL)
		return (result);
	result->length = array->length;
	t_uint i = result->length;
	while (i--)
	{
		if (n == 0)
			return (result);
		if (T_EQUALS(result->items[i], item_old))
		{
			result->items[i] = item_new;
			n -= 1;
		}
	}
	return (result);
}
