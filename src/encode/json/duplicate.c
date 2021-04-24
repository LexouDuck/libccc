
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/encode/json.h"



s_json*	JSON_Duplicate(s_json const* item, t_bool recurse)
{
	s_json* newitem = NULL;
	s_json* child = NULL;
	s_json* next = NULL;
	s_json* newchild = NULL;

	// Bail on bad ptr
	if (!item)
	{
		goto fail;
	}
	// Create new item
	newitem = JSON_New_Item();
	if (!newitem)
	{
		goto fail;
	}
	// Copy over all vars
	newitem->type = item->type & (~JSON_TYPE_ISREFERENCE);
	newitem->value_number = item->value_number;
	if (item->value_string)
	{
		newitem->value_string = (t_char*)String_Duplicate((t_char*)item->value_string);
		if (!newitem->value_string)
		{
			goto fail;
		}
	}
	if (item->key)
	{
		newitem->key = (item->type & JSON_TYPE_CONSTSTRING) ? item->key :
			(t_char*)String_Duplicate((t_char*)item->key);
		if (!newitem->key)
		{
			goto fail;
		}
	}
	// If non-recursive, then we're done!
	if (!recurse)
		return (newitem);
	// Walk the ->next chain for the child.
	child = item->child;
	while (child != NULL)
	{
		newchild = JSON_Duplicate(child, TRUE); // Duplicate (with recurse) each item in the ->next chain
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
			newitem->child = newchild;
			next = newchild;
		}
		child = child->next;
	}
	if (newitem && newitem->child)
	{
		newitem->child->prev = newchild;
	}
	return (newitem);

fail:
	if (newitem != NULL)
	{
		JSON_Delete(newitem);
	}
	return (NULL);
}
