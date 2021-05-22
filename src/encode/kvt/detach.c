
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_HANDLE_INCLUDE



s_kvt*	KVT_Detach(s_kvt* parent, s_kvt* const item)
{
	if ((parent == NULL) || (item == NULL))
	{
		KVT_SetError(ERROR_KVT_INVALIDARGS);
		return (NULL);
	}
	if (item != parent->value.child)
	{	// not the first element
		item->prev->next = item->next;
	}
	if (item->next != NULL)
	{	// not the last element
		item->next->prev = item->prev;
	}

	if (item == parent->value.child)
	{	// first element
		parent->value.child = item->next;
	}
	else if (item->next == NULL)
	{	// last element
		parent->value.child->prev = item->prev;
	}
	// make sure the detached item doesn't point anywhere anymore
	item->prev = NULL;
	item->next = NULL;
	return (item);
}

s_kvt*	KVT_Detach_FromArray(s_kvt* array, t_sint index)
{
	if (index < 0)
	{
		KVT_SetError(ERROR_KVT_INVALIDARGS);
		return (NULL);
	}
	return (KVT_Detach(array, KVT_GetArrayItem(array, index)));
}

s_kvt*	KVT_Detach_FromObject_IgnoreCase(s_kvt* object, t_char const* key)
{
	s_kvt* to_detach = KVT_GetObjectItem(object, key);
	return (KVT_Detach(object, to_detach));
}

s_kvt*	KVT_Detach_FromObject_CaseSensitive(s_kvt* object, t_char const* key)
{
	s_kvt* to_detach = KVT_GetObjectItem_CaseSensitive(object, key);
	return (KVT_Detach(object, to_detach));
}
