
#include "libccc/memory.h"
#include "libccc/generic/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Filter(T)(s_array(T) const* array, t_bool (*filter)(T item))
{
	s_array(T)*	result;
	t_bool*	tmp;
	t_uint	length;
	t_uint	i;

	if CCCERROR((filter == NULL), ERROR_NULLPOINTER, "filter() function given is NULL")
		return (NULL);
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	if (array->length == 0 || array->items == NULL)
		return ((s_array(T)*)Memory_New(sizeof(s_array(T))));
	tmp = (t_bool*)Memory_Allocate(sizeof(t_bool) * array->length);
	if CCCERROR((tmp == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	length = 0;
	for (i = 0; i < array->length; ++i)
	{
		tmp[i] = filter(array->items[i]);
		if (tmp[i])
			++length;
	}
	result = Array_New(T)(length, T_NULL);
	if CCCERROR((result == NULL || result->items == NULL), ERROR_ALLOCFAILURE, NULL)
		return (result);
	if (result->items == NULL)
		return (result);
	result->length = length;
	length = 0;
	for (i = 0; i < result->length; ++i)
	{
		if (tmp[i])
		{
			result->items[i] = array->items[i + length];
		}
		else ++length;
	}
	Memory_Free(tmp);
	return (result);
}


_GENERIC()
s_array(T)*	Array_Filter_I(T)(s_array(T) const* array, t_bool (*filter)(T item, t_uint index))
{
	s_array(T)*	result;
	t_bool*	tmp;
	t_uint	length;
	t_uint	i;

	if CCCERROR((filter == NULL), ERROR_NULLPOINTER, "filter() function given is NULL")
		return (NULL);
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	if (array->length == 0 || array->items == NULL)
		return ((s_array(T)*)Memory_New(sizeof(s_array(T))));
	tmp = (t_bool*)Memory_Allocate(sizeof(t_bool) * array->length);
	if CCCERROR((tmp == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	length = 0;
	for (i = 0; i < array->length; ++i)
	{
		tmp[i] = filter(array->items[i], i);
		if (tmp[i])
			++length;
	}
	result = Array_New(T)(length, T_NULL);
	if CCCERROR((result == NULL || result->items == NULL), ERROR_ALLOCFAILURE, NULL)
		return (result);
	if (result->items == NULL)
		return (result);
	result->length = length;
	length = 0;
	for (i = 0; i < result->length; ++i)
	{
		if (tmp[i])
		{
			result->items[i] = array->items[i + length];
		}
		else ++length;
	}
	Memory_Free(tmp);
	return (result);
}
