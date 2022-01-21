
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Reverse(T)(s_array(T) const* array)
{
	s_array(T)*	result;
	t_uint		index;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array->length > 0 && array->items == NULL), return (NULL);)
	result = Array_New(T)(array->length, T_NULL);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	index = array->length - 1;
	for (t_uint i = 0; i < result->length; ++i, --index)
	{
		result->items[i] = array->items[index];
	}
	return (result);
}
