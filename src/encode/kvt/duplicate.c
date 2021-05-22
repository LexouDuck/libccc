
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_HANDLE_INCLUDE



s_kvt*	KVT_Duplicate(s_kvt const* item, t_bool recurse)
{
	s_kvt* newitem = NULL;
	s_kvt* newchild = NULL;
	s_kvt* next = NULL;
	s_kvt* child = NULL;
	t_utf8* tmp = NULL;

	// Bail on bad ptr
	if (item == NULL)
	{
		goto failure;
	}
	// Create new item
	newitem = KVT_Item();
	if (newitem == NULL)
	{
		goto failure;
	}
	// Copy over all vars
	newitem->type = item->type & (~DYNAMICTYPE_ISREFERENCE);
	newitem->value.number = item->value.number;
	if (item->type & DYNAMICTYPE_NULL)		Memory_Clear(&newitem->value, sizeof(union dynamic));
	if (item->type & DYNAMICTYPE_BOOLEAN)	newitem->value.boolean = item->value.boolean;
	if (item->type & DYNAMICTYPE_INTEGER)	newitem->value.integer = item->value.integer;
	if (item->type & DYNAMICTYPE_FLOAT)		newitem->value.number = item->value.number;
	if (item->type & DYNAMICTYPE_STRING)	tmp = item->value.string;
	if (item->type & DYNAMICTYPE_RAW)		tmp = item->value.string;
	if (item->type & DYNAMICTYPE_ARRAY)		newitem->value.child = NULL;
	if (item->type & DYNAMICTYPE_OBJECT)	newitem->value.child = NULL;
	if (tmp)
	{
		newitem->value.string = (t_char*)String_Duplicate((t_char*)item->value.string);
		if (newitem->value.string == NULL)
		{
			goto failure;
		}
	}
	if (item->key)
	{
		newitem->key = (t_char*)String_Duplicate((t_char*)item->key);
		if (newitem->key == NULL)
		{
			goto failure;
		}
	}
	// If non-recursive, then we're done!
	if (!recurse)
		return (newitem);
	// Walk the ->next chain for the child.
	if (item->type & DYNAMICTYPE_ARRAY)		child = item->value.child;
	if (item->type & DYNAMICTYPE_OBJECT)	child = item->value.child;
	while (child != NULL)
	{
		newchild = KVT_Duplicate(child, TRUE); // Duplicate (with recurse) each item in the ->next chain
		if (newchild == NULL)
		{
			goto failure;
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

failure:
	if (newitem != NULL)
	{
		KVT_Delete(newitem);
	}
	return (NULL);
}
