
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



s_kvt*	KVT_Detach(s_kvt* parent, s_kvt* const item)
{
	if CCCERROR((parent == NULL), ERROR_NULLPOINTER, "`parent` to detach item from, is NULL")
		return (NULL);
	if CCCERROR((item == NULL), ERROR_NULLPOINTER, "`item` argument given is NULL")
		return (NULL);
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

	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "KVT array given is NULL")
		return (NULL);
	tmp = KVT_GetArrayItem(array, index);
	if CCCERROR((tmp == NULL), ERROR_INDEX2LARGE,
		"could not detach array value, invalid index: "SF_SINT, index)
		return (NULL);
	return (KVT_Detach(array, tmp));
}

s_kvt*	KVT_Detach_FromObject_IgnoreCase(s_kvt* object, t_char const* key)
{
	s_kvt*	tmp;

	if CCCERROR((object == NULL), ERROR_NULLPOINTER, "KVT object given is NULL")
		return (NULL);
	tmp = KVT_GetObjectItem(object, key);
	if CCCERROR((tmp == NULL), ERROR_KEYNOTFOUND,
		"could not detach object value, no matching key: \"%s\"", key)
		return (NULL);
	return (KVT_Detach(object, tmp));
}

s_kvt*	KVT_Detach_FromObject_CaseSensitive(s_kvt* object, t_char const* key)
{
	s_kvt*	tmp;

	if CCCERROR((object == NULL), ERROR_NULLPOINTER, "KVT object given is NULL")
		return (NULL);
	tmp = KVT_GetObjectItem_CaseSensitive(object, key);
	if CCCERROR((tmp == NULL), ERROR_KEYNOTFOUND,
		"could not detach object value, no matching key: \"%s\"", key)
		return (NULL);
	return (KVT_Detach(object, tmp));
}
