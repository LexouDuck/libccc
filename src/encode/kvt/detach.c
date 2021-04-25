
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/encode/common.h"



s_kvt*	KVT_DetachItem(s_kvt* parent, s_kvt* const item)
{
	if ((parent == NULL) || (item == NULL))
		return (NULL);

	if (item != parent->child)
	{
		// not the first element
		item->prev->next = item->next;
	}
	if (item->next != NULL)
	{
		// not the last element
		item->next->prev = item->prev;
	}

	if (item == parent->child)
	{
		// first element
		parent->child = item->next;
	}
	else if (item->next == NULL)
	{
		// last element
		parent->child->prev = item->prev;
	}

	// make sure the detached item doesn't point anywhere anymore
	item->prev = NULL;
	item->next = NULL;
	return (item);
}

s_kvt*	KVT_DetachItemFromArray(s_kvt* array, t_sint which)
{
	if (which < 0)
		return (NULL);
	return (KVT_DetachItem(array, KVT_GetArrayItem(array, which)));
}

s_kvt*	KVT_DetachItemFromObject(s_kvt* object, t_char const* key)
{
	s_kvt* to_detach = KVT_GetObjectItem(object, key);
	return (KVT_DetachItem(object, to_detach));
}

s_kvt*	KVT_DetachItemFromObject_CaseSensitive(s_kvt* object, t_char const* key)
{
	s_kvt* to_detach = KVT_GetObjectItem_CaseSensitive(object, key);
	return (KVT_DetachItem(object, to_detach));
}
