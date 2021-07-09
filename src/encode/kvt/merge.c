
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
	item = result->value.child;
	while (item)
	{
		other = kvt2->value.child;
		while (other)
		{
			if (other->key && String_Equals(item->key, other->key))
				break;
			other = other->next;
		}
		if (other) // matching keys, merge values
		{
			if (recurse && KVT_IsObject(other))
			{
				if (KVT_IsObject(item))
					new = KVT_Merge(item, other, recurse);
				else new = KVT_Duplicate(other, recurse);
				item->type = DYNAMICTYPE_OBJECT;
				item->value.child = new;
			}
			else if (recurse && KVT_IsArray(other))
			{
				new = KVT_Duplicate(other, recurse);
				item->type = DYNAMICTYPE_OBJECT;
				item->value.child = new;
			}
			else
			{
				item->type = other->type;
				Memory_Copy(&item->value, &other->value, sizeof(u_dynamic));
			}
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
			other = other->next;
		}
		item = item->next;
	}
	KVT_AddToArray_Item(result, append);
	return (result);
}
