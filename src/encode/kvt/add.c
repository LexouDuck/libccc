
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"



// Utility for handling references.
static s_kvt* create_reference(s_kvt const* item)
{
	s_kvt* reference = NULL;
	if (item == NULL)
		return (NULL);
	reference = KVT_Item();
	if (reference == NULL)
		return (NULL);
	Memory_Copy(reference, item, sizeof(s_kvt));
	reference->key = NULL;
	reference->type |= DYNAMIC_TYPE_ISREFERENCE;
	reference->next = reference->prev = NULL;
	return (reference);
}



static
e_error_kvt	add_item_to_array(s_kvt* array, s_kvt* item)
{
	s_kvt* child = NULL;

	if ((item == NULL) || (array == NULL) || (array == item))
		return (KVT_SetError(ERROR_KVT_INVALIDARGS));

	child = array->value.child;
	// To find the last item in array quickly, we use prev in array
	if (child == NULL)
	{
		// list is empty, start new one
		array->value.child = item;
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
			array->value.child->prev = item;
		}
	}
	return (OK);
}



static
e_error_kvt add_item_to_object(s_kvt* object, t_char const* key, s_kvt* const item)
{
	t_char* new_key = NULL;
	t_sint new_type = DYNAMIC_TYPE_INVALID;

	if ((object == NULL) || (key == NULL) || (item == NULL) || (object == item))
		return (KVT_SetError(ERROR_KVT_INVALIDARGS));
	new_key = (t_char*)String_Duplicate((t_char const*)key);
	if (new_key == NULL)
		return (KVT_SetError(ERROR_KVT_ALLOCATIONFAILURE));

	if (item->key != NULL)
	{
		Memory_Free(item->key);
	}
	item->key = new_key;
	item->type = new_type;
	return (KVT_AddToArray_Item(object, item));
}



e_error_kvt	KVT_AddToArray_Item(s_kvt* array, s_kvt* item)
{
	return (add_item_to_array(array, item));
}

e_error_kvt	KVT_AddToArray_ItemReference(s_kvt* array, s_kvt* item)
{
	if (array == NULL)
		return (KVT_SetError(ERROR_KVT_INVALIDARGS));
	return (add_item_to_array(array, create_reference(item)));
}



e_error_kvt	KVT_AddToObject_Item(s_kvt* object, t_char const* key, s_kvt* item)
{
	return (add_item_to_object(object, key, item));
}

e_error_kvt	KVT_AddToObject_ItemReference(s_kvt* object, t_char const* key, s_kvt* item)
{
	if ((object == NULL) || (key == NULL))
		return (KVT_SetError(ERROR_KVT_INVALIDARGS));
	return (add_item_to_object(object, key, create_reference(item)));
}



s_kvt*	KVT_AddToObject_Null(s_kvt* object, t_char const* key)
{
	s_kvt* item_null = KVT_CreateNull();
	if (add_item_to_object(object, key, item_null))
		return (item_null);
	KVT_Delete(item_null);
	return (NULL);
}

s_kvt*	KVT_AddToObject_Boolean(s_kvt* object, t_char const* key, t_bool value)
{
	s_kvt* item_bool = KVT_CreateBoolean(value);
	if (add_item_to_object(object, key, item_bool))
		return (item_bool);
	KVT_Delete(item_bool);
	return (NULL);
}

s_kvt*	KVT_AddToObject_Integer(s_kvt* object, t_char const* key, t_s64 value)
{
	s_kvt* item_number = KVT_CreateInteger(value);
	if (add_item_to_object(object, key, item_number))
		return (item_number);
	KVT_Delete(item_number);
	return (NULL);
}

s_kvt*	KVT_AddToObject_Float(s_kvt* object, t_char const* key, t_f64 value)
{
	s_kvt* item_number = KVT_CreateFloat(value);
	if (add_item_to_object(object, key, item_number))
		return (item_number);
	KVT_Delete(item_number);
	return (NULL);
}

s_kvt*	KVT_AddToObject_String(s_kvt* object, t_char const* key, t_char const* string)
{
	s_kvt* item_string = KVT_CreateString(string);
	if (add_item_to_object(object, key, item_string))
		return (item_string);
	KVT_Delete(item_string);
	return (NULL);
}

s_kvt*	KVT_AddToObject_Raw(s_kvt* object, t_char const* key, t_char const* raw)
{
	s_kvt* item_raw = KVT_CreateRaw(raw);
	if (add_item_to_object(object, key, item_raw))
		return (item_raw);
	KVT_Delete(item_raw);
	return (NULL);
}

s_kvt*	KVT_AddToObject_Object(s_kvt* object, t_char const* key)
{
	s_kvt* item_object = KVT_CreateObject();
	if (add_item_to_object(object, key, item_object))
		return (item_object);
	KVT_Delete(item_object);
	return (NULL);
}

s_kvt*	KVT_AddToObject_Array(s_kvt* object, t_char const* key)
{
	s_kvt* item_array = KVT_CreateArray();
	if (add_item_to_object(object, key, item_array))
		return (item_array);
	KVT_Delete(item_array);
	return (NULL);
}
