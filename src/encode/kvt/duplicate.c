
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

	if CCCERROR((item == NULL), ERROR_NULLPOINTER, NULL)
		goto failure;
	// Create new item
	newitem = KVT_Item();
	if CCCERROR((newitem == NULL), ERROR_ALLOCFAILURE, NULL)
		goto failure;
	// Copy over all vars
	newitem->type = item->type & (~DYNAMICTYPE_ISREFERENCE);
	if (item->type & DYNAMICTYPE_NULL)		{ newitem->value.child = NULL; } // Memory_Clear(&newitem->value, sizeof(u_dynamic)); } // TODO C++ cant handle sizeof() on a forward-declared recursive union type
	if (item->type & DYNAMICTYPE_BOOLEAN)	{ newitem->value.boolean = item->value.boolean; }
	if (item->type & DYNAMICTYPE_INTEGER)	{ newitem->value.integer = item->value.integer; }
	if (item->type & DYNAMICTYPE_FLOAT)		{ newitem->value.number = item->value.number; }
	if (item->type & DYNAMICTYPE_STRING)	{ newitem->value.string = String_Duplicate(item->value.string); if CCCERROR((newitem->value.string == NULL), ERROR_ALLOCFAILURE, NULL) goto failure; }
	if (item->type & DYNAMICTYPE_RAW)		{ newitem->value.string = String_Duplicate(item->value.string); if CCCERROR((newitem->value.string == NULL), ERROR_ALLOCFAILURE, NULL) goto failure; }
	if (item->type & DYNAMICTYPE_ARRAY)		{ newitem->value.child = NULL; }
	if (item->type & DYNAMICTYPE_OBJECT)	{ newitem->value.child = NULL; }

	if (item->key)
	{
		newitem->key = String_Duplicate(item->key);
		if CCCERROR((newitem->key == NULL), ERROR_ALLOCFAILURE, NULL)
			goto failure;
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
			if CCCERROR((newchild == NULL), ERROR_ALLOCFAILURE, NULL)
				goto failure;
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
