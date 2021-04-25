
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"



// Add item to array/object.
t_bool	KVT_AddToArray_Item(s_kvt* array, s_kvt* item)
{
	s_kvt* child = NULL;

	if ((item == NULL) || (array == NULL) || (array == item))
		return (FALSE);

	child = array->child;
	// To find the last item in array quickly, we use prev in array
	if (child == NULL)
	{
		// list is empty, start new one
		array->child = item;
		item->prev = item;
		item->next = NULL;
	}
	else
	{
		// append to the end
		if (child->prev)
		{
			child->prev->next = item;
			item->prev = child->prev;
			array->child->prev = item;
		}
	}
	return (TRUE);
}



// Utility for handling references.
static s_kvt* create_reference(s_kvt const* item)
{
	s_kvt* reference = NULL;
	if (item == NULL)
		return (NULL);
	reference = KVT_New_Item();
	if (reference == NULL)
		return (NULL);
	Memory_Copy(reference, item, sizeof(s_kvt));
	reference->key = NULL;
	reference->type |= KVT_TYPE_ISREFERENCE;
	reference->next = reference->prev = NULL;
	return (reference);
}



static t_bool add_item_to_object(s_kvt* const object, t_char const* const key, s_kvt* const item, const t_bool constant_key)
{
	t_char* new_key = NULL;
	t_sint new_type = KVT_TYPE_INVALID;

	if ((object == NULL) || (key == NULL) || (item == NULL) || (object == item))
		return (FALSE);
	if (constant_key)
	{
		new_key = (t_char*)key;
		new_type = item->type | KVT_TYPE_CONSTSTRING;
	}
	else
	{
		new_key = (t_char*)String_Duplicate((t_char const*)key);
		if (new_key == NULL)
			return (FALSE);
		new_type = item->type & ~KVT_TYPE_CONSTSTRING;
	}

	if (!(item->type & KVT_TYPE_CONSTSTRING) && (item->key != NULL))
	{
		Memory_Free(item->key);
	}
	item->key = new_key;
	item->type = new_type;
	return (KVT_AddToArray_Item(object, item));
}

t_bool	KVT_AddToObject_Item(s_kvt* object, t_char const* key, s_kvt* item)
{
	return (add_item_to_object(object, key, item, FALSE));
}

t_bool	KVT_AddToObject_ItemCS(s_kvt* object, t_char const* key, s_kvt* item)
{
	return (add_item_to_object(object, key, item, TRUE));
}

t_bool	KVT_AddToArray_ItemReference(s_kvt* array, s_kvt* item)
{
	if (array == NULL)
		return (FALSE);
	return (KVT_AddToArray_Item(array, create_reference(item)));
}

t_bool	KVT_AddToObject_ItemReference(s_kvt* object, t_char const* key, s_kvt* item)
{
	if ((object == NULL) || (key == NULL))
		return (FALSE);
	return (add_item_to_object(object, key, create_reference(item), FALSE));
}

s_kvt*	KVT_AddToObject_Null(s_kvt* const object, t_char const* const name)
{
	s_kvt* item_null = KVT_CreateNull();
	if (add_item_to_object(object, name, item_null, FALSE))
		return (item_null);
	KVT_Delete(item_null);
	return (NULL);
}

s_kvt*	KVT_AddToObject_True(s_kvt* const object, t_char const* const name)
{
	s_kvt* item_true = KVT_CreateTrue();
	if (add_item_to_object(object, name, item_true, FALSE))
		return (item_true);
	KVT_Delete(item_true);
	return (NULL);
}

s_kvt*	KVT_AddToObject_False(s_kvt* const object, t_char const* const name)
{
	s_kvt* item_false = KVT_CreateFalse();
	if (add_item_to_object(object, name, item_false, FALSE))
		return (item_false);
	KVT_Delete(item_false);
	return (NULL);
}

s_kvt*	KVT_AddToObject_Bool(s_kvt* const object, t_char const* const name, const t_bool boolean)
{
	s_kvt* item_bool = KVT_CreateBool(boolean);
	if (add_item_to_object(object, name, item_bool, FALSE))
		return (item_bool);
	KVT_Delete(item_bool);
	return (NULL);
}

s_kvt*	KVT_AddToObject_Number(s_kvt* const object, t_char const* const name, const t_f64 number)
{
	s_kvt* item_number = KVT_CreateNumber(number);
	if (add_item_to_object(object, name, item_number, FALSE))
		return (item_number);
	KVT_Delete(item_number);
	return (NULL);
}

s_kvt*	KVT_AddToObject_String(s_kvt* const object, t_char const* const name, t_char const* const string)
{
	s_kvt* item_string = KVT_CreateString(string);
	if (add_item_to_object(object, name, item_string, FALSE))
		return (item_string);
	KVT_Delete(item_string);
	return (NULL);
}

s_kvt*	KVT_AddToObject_Raw(s_kvt* const object, t_char const* const name, t_char const* const raw)
{
	s_kvt* item_raw = KVT_CreateRaw(raw);
	if (add_item_to_object(object, name, item_raw, FALSE))
		return (item_raw);
	KVT_Delete(item_raw);
	return (NULL);
}

s_kvt*	KVT_AddToObject_Object(s_kvt* const object, t_char const* const name)
{
	s_kvt* item_object = KVT_CreateObject();
	if (add_item_to_object(object, name, item_object, FALSE))
		return (item_object);
	KVT_Delete(item_object);
	return (NULL);
}

s_kvt*	KVT_AddToObject_Array(s_kvt* const object, t_char const* const name)
{
	s_kvt* item_array = KVT_CreateArray();
	if (add_item_to_object(object, name, item_array, FALSE))
		return (item_array);
	KVT_Delete(item_array);
	return (NULL);
}
