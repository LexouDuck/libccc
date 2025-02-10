
#include "libccc/generic/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void*	Array_Reduce(T)(s_array(T) const* array,
	void* (*f)(T item, void* acc))
{
	void*		accumulator = NULL;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	for (t_uint i = 0; i < array->length; ++i)
	{
		accumulator = f(array->items[i], accumulator);
	}
	return (accumulator);
}

_GENERIC()
void*	Array_Reduce_I(T)(s_array(T) const* array,
	void* (*f)(T item, void* acc, t_uint index))
{
	void*		accumulator = NULL;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	for (t_uint i = 0; i < array->length; ++i)
	{
		accumulator = f(array->items[i], accumulator, i);
	}
	return (accumulator);
}



_GENERIC()
void*	Array_Fold(T)(s_array(T) const* array,
	void* (*f)(T item, void* acc), void* initial)
{
	void*		accumulator = initial;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	for (t_uint i = 0; i < array->length; ++i)
	{
		accumulator = f(array->items[i], accumulator);
	}
	return (accumulator);
}

_GENERIC()
void*	Array_Fold_I(T)(s_array(T) const* array,
	void* (*f)(T item, void* acc, t_uint index), void* initial)
{
	void*		accumulator = initial;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	for (t_uint i = 0; i < array->length; ++i)
	{
		accumulator = f(array->items[i], accumulator, i);
	}
	return (accumulator);
}
