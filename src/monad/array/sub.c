
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array_T		CONCAT(Array_Sub,T_NAME)(s_array_T const* array, t_uint index, t_uint n)
{
	s_array_T	result = {0};

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (result);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (result);)
	if (index > array->length || index + n > array->length)
		return (result);
	result.items = (T*)Memory_Allocate(sizeof(T) * n);
	HANDLE_ERROR(ALLOCFAILURE, (result.items == NULL), return (result);)
	result.length = n;
	for (t_uint i = 0; i < n; ++i)
	{
		result.items[i] = array->items[index + i];
	}
	return (result);
}
