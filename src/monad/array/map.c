
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Map(T)(s_array(T) const* array, T (*map)(T item))
{
	s_array(T)*	result;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	if (array->length == 0 || array->items == NULL)
		return ((s_array(T)*)Memory_New(sizeof(s_array(T))));
	result = Array_New(T)(array->length, T_NULL);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (t_uint i = 0; i < array->length; ++i)
	{
		result->items[i] = map(array->items[i]);
	}
	return (result);
}


_GENERIC()
s_array(T)*	Array_Map_I(T)(s_array(T) const* array, T (*map)(T item, t_uint index))
{
	s_array(T)*	result;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	if (array->length == 0 || array->items == NULL)
		return ((s_array(T)*)Memory_New(sizeof(s_array(T))));
	result = Array_New(T)(array->length, T_NULL);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (t_uint i = 0; i < array->length; ++i)
	{
		result->items[i] = map(array->items[i], i);
	}
	return (result);
}
