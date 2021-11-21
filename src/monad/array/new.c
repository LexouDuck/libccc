
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



#if 0
_GENERIC()
s_array_T	CONCAT(Array,T_NAME)(t_uint n)
{
	s_array_T	result;

	result.length = n;
	result.items = NULL;
	if (n == 0)
		return (result);
	result.items = (T*)Memory_Allocate(sizeof(T) * n);
	HANDLE_ERROR(ALLOCFAILURE, (result.items == NULL), return (result);)
	for (t_uint i = 0; i < n; ++i)
	{
		result.items[i] = T_DEFAULT;
	}
	return (result);
}
#endif



_GENERIC()
s_array_T*	CONCAT(Array_New,T_NAME)(t_uint n, T value)
{
	s_array_T*	result;

	result = (s_array_T*)Memory_Allocate(sizeof(s_array_T));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL),
		return (NULL);)
	result->length = n;
	result->items = NULL;
	if (n == 0)
		return (result);
	result->items = (T*)Memory_Allocate(sizeof(T) * n);
	HANDLE_ERROR(ALLOCFAILURE, (result->items == NULL),
		Memory_Delete((void*)&result); return (NULL);)
	for (t_uint i = 0; i < n; ++i)
	{
		result->items[i] = value;
	}
	return (result);
}
