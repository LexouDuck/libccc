
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



s_kvt*	KVT_Detach(s_kvt* parent, s_kvt* const item)
{
	HANDLE_ERROR(NULLPOINTER, (parent == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (item   == NULL), return (NULL);)
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
	s_kvt*	tmp;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	tmp = KVT_GetArrayItem(array, index);
	HANDLE_ERROR_SF(INDEX2LARGE,
		(tmp == NULL), return (NULL);,
		"could not detach array value, invalid index: "SF_SINT, index)
	return (KVT_Detach(array, tmp));
}

s_kvt*	KVT_Detach_FromObject_IgnoreCase(s_kvt* object, t_char const* key)
{
	s_kvt*	tmp;

	HANDLE_ERROR(NULLPOINTER, (object == NULL), return (NULL);)
	tmp = KVT_GetObjectItem(object, key);
	HANDLE_ERROR_SF(KEYNOTFOUND,
		(tmp == NULL), return (NULL);,
		"could not detach object value, no matching key: \"%s\"", key)
	return (KVT_Detach(object, tmp));
}

s_kvt*	KVT_Detach_FromObject_CaseSensitive(s_kvt* object, t_char const* key)
{
	s_kvt*	tmp;

	HANDLE_ERROR(NULLPOINTER, (object == NULL), return (NULL);)
	tmp = KVT_GetObjectItem_CaseSensitive(object, key);
	HANDLE_ERROR_SF(KEYNOTFOUND,
		(tmp == NULL), return (NULL);,
		"could not detach object value, no matching key: \"%s\"", key)
	return (KVT_Detach(object, tmp));
}
