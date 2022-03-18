
#include "libccc/monad/array.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
T*	Array_Get(T)(s_array(T) const* array, t_uint index)
{
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (NULL);)
	HANDLE_ERROR_SF(INDEX2LARGE, (array->length <= index), return (NULL);,
		"index given ("SF_UINT") is beyond end of array (length: "SF_UINT")",
		index, array->length)
	return (&array->items[index]);
}
