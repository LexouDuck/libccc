
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/encode/common.h"



t_bool	KVT_InsertItemInArray(s_kvt* array, t_sint which, s_kvt* newitem)
{
	s_kvt* after_inserted = NULL;

	if (which < 0)
		return (FALSE);

	after_inserted = KVT_GetArrayItem(array, which);
	if (after_inserted == NULL)
		return (KVT_AddToArray_Item(array, newitem));

	newitem->next = after_inserted;
	newitem->prev = after_inserted->prev;
	after_inserted->prev = newitem;
	if (after_inserted == array->child)
	{
		array->child = newitem;
	}
	else
	{
		newitem->prev->next = newitem;
	}
	return (TRUE);
}
