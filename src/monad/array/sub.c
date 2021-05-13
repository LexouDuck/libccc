
#include "libccc/memory.h"
#include "libccc/monad/array.h"


_GENERIC()
s_array_T		CONCAT(Array_Sub,T_NAME)(s_array_T const* array, t_uint index, t_uint n)
{
	s_array_T	result = {0};

	LIBCONFIG_HANDLE_NULLPOINTER(result, array)
	LIBCONFIG_HANDLE_NULLPOINTER(result, array->items)
	if (index > array->length || index + n > array->length)
		return (result);
	result.items = (T*)Memory_Alloc(sizeof(T) * n);
	if (result.items == NULL)
		return (result);
	result.length = n;
	for (t_uint i = 0; i < n; ++i)
	{
		result.items[i] = array->items[index + i];
	}
	return (result);
}
