
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array_T*	CONCAT(Array_Sub,T_NAME)(s_array_T const* array, t_uint index, t_uint n)
{
	s_array_T*	result;

	HANDLE_ERROR(NULLPOINTER, (array        == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (NULL);)
	if (index > array->length || index + n > array->length)
		return (NULL);
	result = CONCAT(Array_New,T_NAME)(n, T_DEFAULT);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	for (t_uint i = 0; i < n; ++i)
	{
		result->items[i] = array->items[index + i];
	}
	return (result);
}
