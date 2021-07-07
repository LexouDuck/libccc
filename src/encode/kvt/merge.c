
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

	HANDLE_ERROR(WRONGTYPE, !KVT_IsObject(kvt1), return (NULL);)
	HANDLE_ERROR(WRONGTYPE, !KVT_IsObject(kvt2), return (NULL);)
	result = KVT_Duplicate(kvt1, recurse);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	item = result->value.child;
	other = kvt2->value.child;
	append = NULL;
	while (item)
	{
		s_kvt*	new;

		if (String_Equals(item->key, other->key))
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
			}
			else
			{
				KVT_AddToArray_Item(append, new);
			}
		}
		item = item->next;
	}
	return (result);
}
