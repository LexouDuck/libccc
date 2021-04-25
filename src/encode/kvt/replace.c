
#include "libccc.h"
#include "libccc/string.h"
#include "libccc/memory.h"
#include "libccc/encode/common.h"



t_bool	KVT_ReplaceItem(s_kvt* const parent, s_kvt* const item, s_kvt * replacement)
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
	KVT_Delete(item);
	return (TRUE);
}

t_bool	KVT_ReplaceItemInArray(s_kvt* array, t_sint which, s_kvt* newitem)
{
	if (which < 0)
		return (FALSE);
	return (KVT_ReplaceItem(array, KVT_GetArrayItem(array, which), newitem));
}



static t_bool replace_item_in_object(s_kvt* object, t_char const* key, s_kvt* replacement, t_bool case_sensitive)
{
	if ((replacement == NULL) || (key == NULL))
		return (FALSE);

	// replace the name in the replacement
	if (!(replacement->type & KVT_TYPE_CONSTSTRING) && (replacement->key != NULL))
	{
		Memory_Free(replacement->key);
	}
	replacement->key = (t_char*)String_Duplicate((t_char const*)key);
	replacement->type &= ~KVT_TYPE_CONSTSTRING;
	return (KVT_ReplaceItem(object, case_sensitive ?
		KVT_GetObjectItem_CaseSensitive(object, key) :
		KVT_GetObjectItem(object, key), replacement));
}

t_bool	KVT_ReplaceItemInObject(s_kvt* object, t_char const* key, s_kvt* newitem)
{
	return (replace_item_in_object(object, key, newitem, FALSE));
}

t_bool	KVT_ReplaceItemInObject_CaseSensitive(s_kvt* object, t_char const* key, s_kvt* newitem)
{
	return (replace_item_in_object(object, key, newitem, TRUE));
}
