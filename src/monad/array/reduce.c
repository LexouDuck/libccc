
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void*	Array_Reduce(T)(s_array(T) const* array,
	void* (*f)(T item, void* acc))
{
	void*		accumulator = NULL;

	HANDLE_ERROR(NULLPOINTER, (f == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
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

	HANDLE_ERROR(NULLPOINTER, (f == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
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

	HANDLE_ERROR(NULLPOINTER, (f == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
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

	HANDLE_ERROR(NULLPOINTER, (f == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	for (t_uint i = 0; i < array->length; ++i)
	{
		accumulator = f(array->items[i], accumulator, i);
	}
	return (accumulator);
}
