
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Reverse(T)(s_array(T) const* array)
{
	s_array(T)*	result;
	t_uint		index;

	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	result = Array_New(T)(array->length, T_NULL);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	index = array->length - 1;
	for (t_uint i = 0; i < result->length; ++i, --index)
	{
		result->items[i] = array->items[index];
	}
	return (result);
}
