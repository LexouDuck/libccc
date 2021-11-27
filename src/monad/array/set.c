
#include "libccc/monad/array.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
T*	Array_Set(T)(s_array(T)* array, t_uint index, T item)
{
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (NULL);)
	HANDLE_ERROR_SF(INDEX2LARGE, (array->length <= index), return (NULL);,
		", index given ("SF_UINT") is beyond end of array (length: "SF_UINT")",
		index, array->length)
	array->items[index] = item;
	return (&array->items[index]);
}
