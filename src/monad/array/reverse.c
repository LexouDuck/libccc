
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array_T*	CONCAT(Array_Reverse,T_NAME)(s_array_T const* array)
{
	s_array_T*	result;
	t_uint		index;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array->length > 0 && array->items == NULL), return (NULL);)
	result = CONCAT(Array_New,T_NAME)(array->length, T_DEFAULT);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	index = array->length - 1;
	for (t_uint i = 0; i < result->length; ++i, --index)
	{
		result->items[i] = array->items[index];
	}
	return (result);
}
