
#include "libccc/monad/array.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
T*	Array_Get(T)(s_array(T) const* array, t_uint index)
{
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	if CCCERROR((array->length <= index), ERROR_INDEX2LARGE, 
		"index given (" SF_UINT ") is beyond end of array (length: " SF_UINT ")", index, array->length)
		return (NULL);
	if CCCERROR((array->items == NULL), ERROR_NULLPOINTER,
		"array given is invalid - `.length` doesn't match `.items`")
		return (NULL);
	return (&array->items[index]);
}
