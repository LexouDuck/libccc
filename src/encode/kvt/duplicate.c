
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



s_kvt*	KVT_Duplicate(s_kvt const* item, t_bool recurse)
{
	s_kvt*	newitem = NULL;
	s_kvt*	newchild = NULL;
	s_kvt*	next = NULL;
	s_kvt*	child = NULL;

	HANDLE_ERROR(NULLPOINTER, (item == NULL), goto failure;)
	// Create new item
	newitem = KVT_Item();
	HANDLE_ERROR(ALLOCFAILURE, (newitem == NULL), goto failure;)
	// Copy over all vars
	newitem->type = item->type & (~DYNAMICTYPE_ISREFERENCE);
	if (item->type & DYNAMICTYPE_NULL)		{ Memory_Clear(&newitem->value, sizeof(union dynamic)); }
	if (item->type & DYNAMICTYPE_BOOLEAN)	{ newitem->value.boolean = item->value.boolean; }
	if (item->type & DYNAMICTYPE_INTEGER)	{ newitem->value.integer = item->value.integer; }
	if (item->type & DYNAMICTYPE_FLOAT)		{ newitem->value.number = item->value.number; }
	if (item->type & DYNAMICTYPE_STRING)	{ newitem->value.string = String_Duplicate(item->value.string); HANDLE_ERROR(ALLOCFAILURE, (newitem->value.string == NULL), goto failure;) }
	if (item->type & DYNAMICTYPE_RAW)		{ newitem->value.string = String_Duplicate(item->value.string); HANDLE_ERROR(ALLOCFAILURE, (newitem->value.string == NULL), goto failure;) }
	if (item->type & DYNAMICTYPE_ARRAY)		{ newitem->value.child = NULL; }
	if (item->type & DYNAMICTYPE_OBJECT)	{ newitem->value.child = NULL; }

	if (item->key)
	{
		newitem->key = String_Duplicate(item->key);
		HANDLE_ERROR(ALLOCFAILURE, (newitem->key == NULL), goto failure;)
	}
	// If non-recursive, then we're done!
	if (!recurse)
		return (newitem);
	// Walk the `->next` chain for the child.
	if ((item->type & DYNAMICTYPE_ARRAY) || (item->type & DYNAMICTYPE_OBJECT))
	{
		if (newitem->value.child == NULL)
		{
			child = item->value.child;
		}
		while (child != NULL)
		{
			newchild = KVT_Duplicate(child, TRUE); // Duplicate (with recurse) each item in the `->next` chain
			HANDLE_ERROR(ALLOCFAILURE, (newchild == NULL), goto failure;)
			if (next != NULL)
			{	// If `newitem->child` already set, then crosswire `->prev` and `->next` and move on
				next->next = newchild;
				newchild->prev = next;
				next = newchild;
			}
			else
			{	// Set newitem->child and move to it
				newitem->value.child = newchild;
				next = newchild;
			}
			child = child->next;
		}
		if (newitem && newitem->value.child)
		{
			newitem->value.child->prev = newchild;
		}
	}
	return (newitem);

failure:
	if (newitem != NULL)
	{
		KVT_Delete(newitem);
	}
	return (NULL);
}
