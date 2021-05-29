
#include "libccc.h"
#include "libccc/string.h"
#include "libccc/memory.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_HANDLE_INCLUDE



e_cccerror	KVT_Replace(s_kvt* const parent, s_kvt* const item, s_kvt* replacement)
{
	HANDLE_ERROR(NULLPOINTER, (parent      == NULL), return (ERROR_NULLPOINTER);)
	HANDLE_ERROR(NULLPOINTER, (replacement == NULL), return (ERROR_NULLPOINTER);)
	HANDLE_ERROR(NULLPOINTER, (item        == NULL), return (ERROR_NULLPOINTER);)
	HANDLE_ERROR(INVALIDARGS, (replacement == item), return (ERROR_INVALIDARGS);)
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

e_cccerror	KVT_Replace_InArray(s_kvt* array, t_uint index, s_kvt* newitem)
{
	s_kvt*	item;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (ERROR_NULLPOINTER);)
	item = KVT_GetArrayItem(array, index);
	HANDLE_ERROR(INDEX2SMALL, (item == NULL), return (ERROR_INDEX2SMALL);)
	return (KVT_Replace(array, item, newitem));
}



static
e_cccerror replace_item_in_object(s_kvt* object, t_char const* key, s_kvt* replacement, t_bool case_sensitive)
{
	HANDLE_ERROR(NULLPOINTER, (object      == NULL), return (ERROR_NULLPOINTER);)
	HANDLE_ERROR(NULLPOINTER, (key         == NULL), return (ERROR_NULLPOINTER);)
	HANDLE_ERROR(NULLPOINTER, (replacement == NULL), return (ERROR_NULLPOINTER);)
	// replace the name in the replacement
	if (replacement->key != NULL)
	{
		Memory_Free(replacement->key);
	}
	replacement->key = (t_char*)String_Duplicate(key);
	return (KVT_Replace(object, case_sensitive ?
		KVT_GetObjectItem_CaseSensitive(object, key) :
		KVT_GetObjectItem(object, key), replacement));
}

e_cccerror	KVT_Replace_InObject_IgnoreCase(s_kvt* object, t_char const* key, s_kvt* newitem)
{
	return (replace_item_in_object(object, key, newitem, FALSE));
}

e_cccerror	KVT_Replace_InObject_CaseSensitive(s_kvt* object, t_char const* key, s_kvt* newitem)
{
	return (replace_item_in_object(object, key, newitem, TRUE));
}
