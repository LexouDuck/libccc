
#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



s_kvt*	KVT_Merge(s_kvt const* kvt1, s_kvt const* kvt2, t_bool recurse)
{
	s_kvt*	result;
	s_kvt*	item;
	s_kvt*	other;
	s_kvt*	append;
	s_kvt*	current;
	s_kvt*	new;

	HANDLE_ERROR(WRONGTYPE, !KVT_IsObject(kvt1), return (NULL);)
	HANDLE_ERROR(WRONGTYPE, !KVT_IsObject(kvt2), return (NULL);)
	result = KVT_Duplicate(kvt1, recurse);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	append = NULL;
	other = kvt2->value.child;
	while (other)
	{
		item = result->value.child;
		while (item)
		{
			if (item->key && String_Equals(item->key, other->key))
				break;
			item = item->next;
		}
		if (item) // matching keys, merge values
		{
			if (recurse && KVT_IsObject(other))
			{
				if (KVT_IsObject(item))
					new = KVT_Merge(item, other, recurse);
				else new = KVT_Duplicate(other, recurse);
			}
			else
			{
				new = KVT_Duplicate(other, recurse);
			}
			KVT_Replace(result, item, new);
		}
		else
		{
			new = KVT_Duplicate(other, recurse);
			if (append == NULL)
			{
				append = new;
				current = new;
			}
			else
			{
				current->next = new;
				new->prev = current;
				current = new;
			}
		}
		other = other->next;
	}
	if (append)
	{
		result->value.child->prev->next = append->value.child; // use `prev` to access last element without looping
		append->value.child->prev = result->value.child->prev;
		result->value.child->prev = append->value.child->prev;
	}
	return (result);
}
