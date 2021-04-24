
#include "libccc.h"
#include "libccc/string.h"
#include "libccc/memory.h"
#include "libccc/encode/json.h"



t_bool	JSON_ReplaceItem(s_json* const parent, s_json* const item, s_json * replacement)
{
	if ((parent == NULL) || (replacement == NULL) || (item == NULL))
		return (FALSE);

	if (replacement == item)
		return (TRUE);

	replacement->next = item->next;
	replacement->prev = item->prev;

	if (replacement->next != NULL)
	{
		replacement->next->prev = replacement;
	}
	if (parent->child == item)
	{
		if (parent->child->prev == parent->child)
		{
			replacement->prev = replacement;
		}
		parent->child = replacement;
	}
	else
	{   // To find the last item in array quickly, we use prev in array.
		// We can't modify the last item's next pointer where this item was the parent's child
		if (replacement->prev != NULL)
		{
			replacement->prev->next = replacement;
		}
		if (replacement->next == NULL)
		{
			parent->child->prev = replacement;
		}
	}

	item->next = NULL;
	item->prev = NULL;
	JSON_Delete(item);
	return (TRUE);
}

t_bool	JSON_ReplaceItemInArray(s_json* array, t_sint which, s_json* newitem)
{
	if (which < 0)
		return (FALSE);
	return (JSON_ReplaceItem(array, JSON_GetArrayItem(array, which), newitem));
}



static t_bool replace_item_in_object(s_json* object, t_char const* key, s_json* replacement, t_bool case_sensitive)
{
	if ((replacement == NULL) || (key == NULL))
		return (FALSE);

	// replace the name in the replacement
	if (!(replacement->type & JSON_TYPE_CONSTSTRING) && (replacement->key != NULL))
	{
		Memory_Free(replacement->key);
	}
	replacement->key = (t_char*)String_Duplicate((t_char const*)key);
	replacement->type &= ~JSON_TYPE_CONSTSTRING;
	return (JSON_ReplaceItem(object, case_sensitive ?
		JSON_GetObjectItem_CaseSensitive(object, key) :
		JSON_GetObjectItem(object, key), replacement));
}

t_bool	JSON_ReplaceItemInObject(s_json* object, t_char const* key, s_json* newitem)
{
	return (replace_item_in_object(object, key, newitem, FALSE));
}

t_bool	JSON_ReplaceItemInObject_CaseSensitive(s_json* object, t_char const* key, s_json* newitem)
{
	return (replace_item_in_object(object, key, newitem, TRUE));
}
