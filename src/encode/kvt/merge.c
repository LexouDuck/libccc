
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
	s_kvt*	kvt_new;

	if CCCERROR(!KVT_IsObject(kvt1), ERROR_WRONGTYPE, "merge can only be done with two OBJECT-typed KVTs")	return (NULL);
	if CCCERROR(!KVT_IsObject(kvt2), ERROR_WRONGTYPE, "merge can only be done with two OBJECT-typed KVTs")	return (NULL);
	result = KVT_Duplicate(kvt1, recurse);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)	return (NULL);
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
					kvt_new = KVT_Merge(item, other, recurse);
				else kvt_new = KVT_Duplicate(other, recurse);
			}
			else
			{
				kvt_new = KVT_Duplicate(other, recurse);
			}
			KVT_Replace(result, item, kvt_new);
		}
		else
		{
			kvt_new = KVT_Duplicate(other, recurse);
			if (append == NULL)
			{
				append = kvt_new;
				current = kvt_new;
			}
			else
			{
				current->next = kvt_new;
				kvt_new->prev = current;
				current = kvt_new;
			}
		}
		other = other->next;
	}
	if (result->value.child && append)
	{
		result->value.child->prev->next = append->value.child; // use `prev` to access last element without looping
		append->value.child->prev = result->value.child->prev;
		result->value.child->prev = append->value.child->prev;
	}
	return (result);
}
