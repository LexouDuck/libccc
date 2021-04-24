
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/encode/json.h"



s_json*	JSON_DetachItem(s_json* parent, s_json* const item)
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

s_json*	JSON_DetachItemFromArray(s_json* array, t_sint which)
{
	if (which < 0)
		return (NULL);
	return (JSON_DetachItem(array, JSON_GetArrayItem(array, which)));
}

s_json*	JSON_DetachItemFromObject(s_json* object, t_char const* key)
{
	s_json* to_detach = JSON_GetObjectItem(object, key);
	return (JSON_DetachItem(object, to_detach));
}

s_json*	JSON_DetachItemFromObject_CaseSensitive(s_json* object, t_char const* key)
{
	s_json* to_detach = JSON_GetObjectItem_CaseSensitive(object, key);
	return (JSON_DetachItem(object, to_detach));
}
