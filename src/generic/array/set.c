
#include "libccc/generic/array.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
T*	Array_Set(T)(s_array(T)* array, t_uint index, T item)
{
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	if CCCERROR((array->length <= index), ERROR_INDEX2LARGE, 
		"index given (" SF_UINT ") is greater than array->length: " SF_UINT, index, array->length)
		return (NULL);
	if CCCERROR((array->items == NULL), ERROR_INVALIDARGS,
		"invalid array given - array->length (" SF_UINT ") doesn't match array->items", array->length)
		return (NULL);
	array->items[index] = item;
	return (&array->items[index]);
}
