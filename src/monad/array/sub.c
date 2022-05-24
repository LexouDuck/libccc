
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Sub(T)(s_array(T) const* array, t_uint index, t_uint n)
{
	s_array(T)*	result;

	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	if CCCERROR((index >= array->length), ERROR_INDEX2LARGE, NULL)
		return (NULL);
	if CCCERROR((index + n > array->length), ERROR_LENGTH2LARGE, NULL)
		return (NULL);
	if (n == 0)
		n = array->length - index;
	result = Array_New(T)(n, T_NULL);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (t_uint i = 0; i < n; ++i)
	{
		result->items[i] = array->items[index + i];
	}
	return (result);
}
