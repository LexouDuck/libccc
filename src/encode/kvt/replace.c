
#include "libccc.h"
#include "libccc/string.h"
#include "libccc/memory.h"
#include "libccc/encode/common.h"



e_error_kvt	KVT_Replace(s_kvt* const parent, s_kvt* const item, s_kvt* replacement)
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
	if (parent->value.child == item)
	{
		if (parent->value.child->prev == parent->value.child)
		{
			replacement->prev = replacement;
		}
		parent->value.child = replacement;
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
			parent->value.child->prev = replacement;
		}
	}

	item->next = NULL;
	item->prev = NULL;
	KVT_Delete(item);
	return (TRUE);
}

e_error_kvt	KVT_Replace_InArray(s_kvt* array, t_sint index, s_kvt* newitem)
{
	if (index < 0)
		return (KVT_SetError(ERROR_KVT_INVALIDARGS));
	return (KVT_Replace(array, KVT_GetArrayItem(array, index), newitem));
}



static
e_error_kvt replace_item_in_object(s_kvt* object, t_char const* key, s_kvt* replacement, t_bool case_sensitive)
{
	if ((replacement == NULL) || (key == NULL))
		return (KVT_SetError(ERROR_KVT_INVALIDARGS));
	// replace the name in the replacement
	if (replacement->key != NULL)
	{
		Memory_Free(replacement->key);
	}
	replacement->key = (t_char*)String_Duplicate((t_char const*)key);
	return (KVT_Replace(object, case_sensitive ?
		KVT_GetObjectItem_CaseSensitive(object, key) :
		KVT_GetObjectItem(object, key), replacement));
}

e_error_kvt	KVT_Replace_InObject_IgnoreCase(s_kvt* object, t_char const* key, s_kvt* newitem)
{
	return (replace_item_in_object(object, key, newitem, FALSE));
}

e_error_kvt	KVT_Replace_InObject_CaseSensitive(s_kvt* object, t_char const* key, s_kvt* newitem)
{
	return (replace_item_in_object(object, key, newitem, TRUE));
}
