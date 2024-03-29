
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



t_sint	KVT_GetArrayLength(s_kvt const* array)
{
	s_kvt* child = NULL;
	t_size size = 0;

	if (array == NULL)
		return (0);
	if CCCERROR(!(KVT_IsArray(array) || KVT_IsObject(array)), ERROR_WRONGTYPE,
		"expected kvt of type ARRAY or OBJECT, but got %u", array->type)
		return (0);
	child = array->value.child;
	while (child != NULL)
	{
		size++;
		child = child->next;
	}
	// FIXME: Can overflow here. Cannot be fixed without breaking the API
	return ((t_sint)size);
}
