
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



e_cccerror	KVT_Insert_InArray(s_kvt* array, t_sint index, s_kvt* newitem)
{
	s_kvt* after_inserted = NULL;

	if CCCERROR((array == NULL), ERROR_NULLPOINTER, NULL) return (ERROR_NULLPOINTER);
	after_inserted = KVT_GetArrayItem(array, index);
	if CCCERROR((after_inserted == NULL), ERROR_INDEX2LARGE,
		"invalid index for kvt array item insert: "SF_SINT, index)
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
	return (ERROR_NONE);
}
