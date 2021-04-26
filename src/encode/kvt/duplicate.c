
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"



s_kvt*	KVT_Duplicate(s_kvt const* item, t_bool recurse)
{
	s_kvt* newitem = NULL;
	s_kvt* child = NULL;
	s_kvt* next = NULL;
	s_kvt* newchild = NULL;

	// Bail on bad ptr
	if (!item)
	{
		goto fail;
	}
	// Create new item
	newitem = KVT_Item();
	if (!newitem)
	{
		goto fail;
	}
	// Copy over all vars
	newitem->type = item->type & (~DYNAMIC_TYPE_ISREFERENCE);
	newitem->value.number = item->value.number;
	if (item->value.string)
	{
		newitem->value.string = (t_char*)String_Duplicate((t_char*)item->value.string);
		if (!newitem->value.string)
		{
			goto fail;
		}
	}
	if (item->key)
	{
		newitem->key = (t_char*)String_Duplicate((t_char*)item->key);
		if (!newitem->key)
		{
			goto fail;
		}
	}
	// If non-recursive, then we're done!
	if (!recurse)
		return (newitem);
	// Walk the ->next chain for the child.
	child = item->value.child;
	while (child != NULL)
	{
		newchild = KVT_Duplicate(child, TRUE); // Duplicate (with recurse) each item in the ->next chain
		if (!newchild)
		{
			goto fail;
		}
		if (next != NULL)
		{
			// If newitem->child already set, then crosswire ->prev and ->next and move on
			next->next = newchild;
			newchild->prev = next;
			next = newchild;
		}
		else
		{
			// Set newitem->child and move to it
			newitem->value.child = newchild;
			next = newchild;
		}
		child = child->next;
	}
	if (newitem && newitem->value.child)
	{
		newitem->value.child->prev = newchild;
	}
	return (newitem);

fail:
	if (newitem != NULL)
	{
		KVT_Delete(newitem);
	}
	return (NULL);
}
