
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
	{
		KVT_SetError(ERROR_KVT_INVALIDARGS);
		return (NULL);
	}
	reference = KVT_Item();
	if (reference == NULL)
	{
		KVT_SetError(ERROR_KVT_ALLOCATIONFAILURE);
		return (NULL);
	}
	Memory_Copy(reference, item, sizeof(s_kvt));
	reference->key = NULL;
	reference->type |= DYNAMICTYPE_ISREFERENCE;
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
	t_sint new_type = DYNAMICTYPE_INVALID;

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
	e_error_kvt error = add_item_to_object(object, key, item_null);
	if (error)
	{
		KVT_SetError(error);
		KVT_Delete(item_null);
		return (NULL);
	}
	return (item_null);
}

s_kvt*	KVT_AddToObject_Boolean(s_kvt* object, t_char const* key, t_bool value)
{
	s_kvt* item_bool = KVT_CreateBoolean(value);
	e_error_kvt error = add_item_to_object(object, key, item_bool);
	if (error)
	{
		KVT_SetError(error);
		KVT_Delete(item_bool);
		return (NULL);
	}
	return (item_bool);
}

s_kvt*	KVT_AddToObject_Integer(s_kvt* object, t_char const* key, t_s64 value)
{
	s_kvt* item_number = KVT_CreateInteger(value);
	e_error_kvt error = add_item_to_object(object, key, item_number);
	if (error)
	{
		KVT_SetError(error);
		KVT_Delete(item_number);
		return (NULL);
	}
	return (item_number);
}

s_kvt*	KVT_AddToObject_Float(s_kvt* object, t_char const* key, t_f64 value)
{
	s_kvt* item_number = KVT_CreateFloat(value);
	e_error_kvt error = add_item_to_object(object, key, item_number);
	if (error)
	{
		KVT_SetError(error);
		KVT_Delete(item_number);
		return (NULL);
	}
	return (item_number);
}

s_kvt*	KVT_AddToObject_String(s_kvt* object, t_char const* key, t_char const* string)
{
	s_kvt* item_string = KVT_CreateString(string);
	e_error_kvt error = add_item_to_object(object, key, item_string);
	if (error)
	{
		KVT_SetError(error);
		KVT_Delete(item_string);
		return (NULL);
	}
	return (item_string);
}

s_kvt*	KVT_AddToObject_Raw(s_kvt* object, t_char const* key, t_char const* raw)
{
	s_kvt* item_raw = KVT_CreateRaw(raw);
	e_error_kvt error = add_item_to_object(object, key, item_raw);
	if (error)
	{
		KVT_SetError(error);
		KVT_Delete(item_raw);
		return (NULL);
	}
	return (item_raw);
}

s_kvt*	KVT_AddToObject_Object(s_kvt* object, t_char const* key)
{
	s_kvt* item_object = KVT_CreateObject();
	e_error_kvt error = add_item_to_object(object, key, item_object);
	if (error)
	{
		KVT_SetError(error);
		KVT_Delete(item_object);
		return (NULL);
	}
	return (item_object);
}

s_kvt*	KVT_AddToObject_Array(s_kvt* object, t_char const* key)
{
	s_kvt* item_array = KVT_CreateArray();
	e_error_kvt error = add_item_to_object(object, key, item_array);
	if (error)
	{
		KVT_SetError(error);
		KVT_Delete(item_array);
		return (NULL);
	}
	return (item_array);
}
