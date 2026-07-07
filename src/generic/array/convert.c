
#include "libccc/memory.h"
#include "libccc/generic/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_FromMemory(T)(T* ptr, t_uint n)
{
	s_array(T)*	result;

	if CCCERROR((ptr == NULL && n > 0), ERROR_NULLPOINTER, "memory buffer given is NULL")
		return (NULL);
	result = (s_array(T)*)Memory_New(sizeof(s_array(T)));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if (n == 0)
		return (result); // an empty (but valid) array
	result->items = (T*)Memory_Duplicate(ptr, n * sizeof(T));
	if CCCERROR((result->items == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Free(result);
		return (NULL);
	}
	result->length = n;
	return (result);
}

_GENERIC()
T*	Array_ToMemory(T)(s_array(T) const* array)
{
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	if CCCERROR((array->length > 0 && array->items == NULL), ERROR_INVALIDARGS,
		"array given is invalid - `.length` doesn't match `.items`")
		return (NULL);
	if (array->length == 0)
		return (NULL); // an empty array yields no memory buffer
	return ((T*)Memory_Duplicate(array->items, array->length * sizeof(T)));
}



_GENERIC()
s_array(T)*	Array_FromPointerArray(T)(T const* const* ptrarr)
{
	s_array(T)*	result;
	t_uint	length;

	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return (NULL);
	length = 0;
	while (ptrarr[length])
	{
		length += 1;
	}
	result = (s_array(T)*)Memory_New(sizeof(s_array(T)));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if (length == 0)
		return (result); // an empty (but valid) array
	result->items = (T*)Memory_Allocate(length * sizeof(T));
	if CCCERROR((result->items == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Free(result);
		return (NULL);
	}
	result->length = length;
	for (t_uint i = 0; i < length; ++i)
	{
		result->items[i] = *(ptrarr[i]);
	}
	return (result);
}

_GENERIC()
void**	Array_ToPointerArray(T)(s_array(T) const* array)
{
	void**	result;

	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	if CCCERROR((array->length > 0 && array->items == NULL), ERROR_INVALIDARGS,
		"array given is invalid - `.length` doesn't match `.items`")
		return (NULL);
	result = (void**)Memory_Allocate((array->length + 1) * sizeof(void*));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	// NOTE: the pointers stored refer to the items held within the given `array`:
	// the underlying item data is not copied, so these pointers are only valid
	// for as long as the given `array` (and its `.items` buffer) stays alive.
	for (t_uint i = 0; i < array->length; ++i)
	{
		result[i] = (void*)&(array->items[i]);
	}
	result[array->length] = NULL;
	return (result);
}
