
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array_T*	CONCAT(Array_Duplicate,T_NAME)(s_array_T const* array)
{
	s_array_T*	result;

	HANDLE_ERROR(NULLPOINTER, (array        == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (NULL);)
	result = (s_array_T*)Memory_New(sizeof(s_array_T));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	result->items = (T*)Memory_Duplicate(array->items, sizeof(T) * array->length);
	result->length = (array->items ? array->length : 0);
	return (result);
}
