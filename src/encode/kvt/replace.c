
#include "libccc.h"
#include "libccc/string.h"
#include "libccc/memory.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



e_cccerror	KVT_Replace(s_kvt* const parent, s_kvt* const item, s_kvt* replacement)
{
	if CCCERROR((parent == NULL), ERROR_NULLPOINTER, "KVT parent item given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((item == NULL), ERROR_NULLPOINTER, "KVT child item given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((replacement == NULL), ERROR_NULLPOINTER, "KVT replacement item given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((replacement == item), ERROR_INVALIDARGS, "cannot replace kvt item with itself")
		return (ERROR_INVALIDARGS);
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
	return (ERROR_NONE);
}

e_cccerror	KVT_Replace_InArray(s_kvt* array, t_sint index, s_kvt* newitem)
{
	s_kvt*	item;

	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "KVT array given is NULL")
		return (ERROR_NULLPOINTER);
	item = KVT_GetArrayItem(array, index);
	if CCCERROR((item == NULL), ERROR_INVALIDARGS,
		"could not get kvt array item at index " SF_SINT, index)
		return (ERROR_INDEX2SMALL);
	return (KVT_Replace(array, item, newitem));
}



static
e_cccerror KVT_Replace_InObject_(s_kvt* object, t_char const* key, s_kvt* replacement, t_bool case_sensitive)
{
	if CCCERROR((object == NULL), ERROR_NULLPOINTER, "KVT object given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((key == NULL), ERROR_NULLPOINTER, "KVT item key given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((replacement == NULL), ERROR_NULLPOINTER, "KVT replacement item given is NULL")
		return (ERROR_NULLPOINTER);
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
	return (KVT_Replace_InObject_(object, key, newitem, FALSE));
}

e_cccerror	KVT_Replace_InObject_CaseSensitive(s_kvt* object, t_char const* key, s_kvt* newitem)
{
	return (KVT_Replace_InObject_(object, key, newitem, TRUE));
}
