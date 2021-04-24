
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/encode/json.h"



t_bool	JSON_InsertItemInArray(s_json* array, t_sint which, s_json* newitem)
{
	s_json* after_inserted = NULL;

	if (which < 0)
		return (FALSE);

	after_inserted = JSON_GetArrayItem(array, which);
	if (after_inserted == NULL)
		return (JSON_AddToArray_Item(array, newitem));

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
