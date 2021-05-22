
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_HANDLE_INCLUDE



e_error_kvt	KVT_Insert_InArray(s_kvt* array, t_sint index, s_kvt* newitem)
{
	s_kvt* after_inserted = NULL;

	if (index < 0)
		return (KVT_SetError(ERROR_KVT_INVALIDARGS));
	after_inserted = KVT_GetArrayItem(array, index);
	if (after_inserted == NULL)
		return (KVT_AddToArray_Item(array, newitem));
	newitem->next = after_inserted;
	newitem->prev = after_inserted->prev;
	after_inserted->prev = newitem;
	if (after_inserted == array->value.child)
	{
		array->value.child = newitem;
	}
	else
	{
		newitem->prev->next = newitem;
	}
	return (OK);
}
