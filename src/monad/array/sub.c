
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Sub(T)(s_array(T) const* array, t_uint index, t_uint n)
{
	s_array(T)*	result;

	HANDLE_ERROR(NULLPOINTER, (array == NULL),             return (NULL);)
	HANDLE_ERROR(INDEX2LARGE, (index >= array->length),    return (NULL);)
	HANDLE_ERROR(LENGTH2LARGE, (index + n > array->length), return (NULL);)
	if (n == 0)
		n = array->length - index;
	result = Array_New(T)(n, T_NULL);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	for (t_uint i = 0; i < n; ++i)
	{
		result->items[i] = array->items[index + i];
	}
	return (result);
}
