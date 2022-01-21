
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Duplicate(T)(s_array(T) const* array)
{
	s_array(T)*	result;

	HANDLE_ERROR(NULLPOINTER, (array        == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (NULL);)
	result = (s_array(T)*)Memory_New(sizeof(s_array(T)));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	result->items = (T*)Memory_Duplicate(array->items, sizeof(T) * array->length);
	result->length = (array->items ? array->length : 0);
	return (result);
}
