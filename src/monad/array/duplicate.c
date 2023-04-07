
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Duplicate(T)(s_array(T) const* array)
{
	s_array(T)*	result;

	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	if CCCERROR((array->length > 0 && array->items == NULL), ERROR_INVALIDARGS, "array given is invalid")
		return (NULL);
	result = (s_array(T)*)Memory_New(sizeof(s_array(T)));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result->items = (T*)Memory_Duplicate(array->items, sizeof(T) * array->length);
	result->length = (array->items ? array->length : 0);
	return (result);
}
