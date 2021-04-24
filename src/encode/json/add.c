
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/encode/json.h"



// Add item to array/object.
t_bool	JSON_AddToArray_Item(s_json* array, s_json* item)
{
	s_json* child = NULL;

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
static s_json* create_reference(s_json const* item)
{
	s_json* reference = NULL;
	if (item == NULL)
		return (NULL);
	reference = JSON_New_Item();
	if (reference == NULL)
		return (NULL);
	Memory_Copy(reference, item, sizeof(s_json));
	reference->key = NULL;
	reference->type |= JSON_TYPE_ISREFERENCE;
	reference->next = reference->prev = NULL;
	return (reference);
}



static t_bool add_item_to_object(s_json* const object, t_char const* const key, s_json* const item, const t_bool constant_key)
{
	t_char* new_key = NULL;
	t_sint new_type = JSON_TYPE_INVALID;

	if ((object == NULL) || (key == NULL) || (item == NULL) || (object == item))
		return (FALSE);
	if (constant_key)
	{
		new_key = (t_char*)key;
		new_type = item->type | JSON_TYPE_CONSTSTRING;
	}
	else
	{
		new_key = (t_char*)String_Duplicate((t_char const*)key);
		if (new_key == NULL)
			return (FALSE);
		new_type = item->type & ~JSON_TYPE_CONSTSTRING;
	}

	if (!(item->type & JSON_TYPE_CONSTSTRING) && (item->key != NULL))
	{
		Memory_Free(item->key);
	}
	item->key = new_key;
	item->type = new_type;
	return (JSON_AddToArray_Item(object, item));
}

t_bool	JSON_AddToObject_Item(s_json* object, t_char const* key, s_json* item)
{
	return (add_item_to_object(object, key, item, FALSE));
}

t_bool	JSON_AddToObject_ItemCS(s_json* object, t_char const* key, s_json* item)
{
	return (add_item_to_object(object, key, item, TRUE));
}

t_bool	JSON_AddToArray_ItemReference(s_json* array, s_json* item)
{
	if (array == NULL)
		return (FALSE);
	return (JSON_AddToArray_Item(array, create_reference(item)));
}

t_bool	JSON_AddToObject_ItemReference(s_json* object, t_char const* key, s_json* item)
{
	if ((object == NULL) || (key == NULL))
		return (FALSE);
	return (add_item_to_object(object, key, create_reference(item), FALSE));
}

s_json*	JSON_AddToObject_Null(s_json* const object, t_char const* const name)
{
	s_json* item_null = JSON_CreateNull();
	if (add_item_to_object(object, name, item_null, FALSE))
		return (item_null);
	JSON_Delete(item_null);
	return (NULL);
}

s_json*	JSON_AddToObject_True(s_json* const object, t_char const* const name)
{
	s_json* item_true = JSON_CreateTrue();
	if (add_item_to_object(object, name, item_true, FALSE))
		return (item_true);
	JSON_Delete(item_true);
	return (NULL);
}

s_json*	JSON_AddToObject_False(s_json* const object, t_char const* const name)
{
	s_json* item_false = JSON_CreateFalse();
	if (add_item_to_object(object, name, item_false, FALSE))
		return (item_false);
	JSON_Delete(item_false);
	return (NULL);
}

s_json*	JSON_AddToObject_Bool(s_json* const object, t_char const* const name, const t_bool boolean)
{
	s_json* item_bool = JSON_CreateBool(boolean);
	if (add_item_to_object(object, name, item_bool, FALSE))
		return (item_bool);
	JSON_Delete(item_bool);
	return (NULL);
}

s_json*	JSON_AddToObject_Number(s_json* const object, t_char const* const name, const t_f64 number)
{
	s_json* item_number = JSON_CreateNumber(number);
	if (add_item_to_object(object, name, item_number, FALSE))
		return (item_number);
	JSON_Delete(item_number);
	return (NULL);
}

s_json*	JSON_AddToObject_String(s_json* const object, t_char const* const name, t_char const* const string)
{
	s_json* item_string = JSON_CreateString(string);
	if (add_item_to_object(object, name, item_string, FALSE))
		return (item_string);
	JSON_Delete(item_string);
	return (NULL);
}

s_json*	JSON_AddToObject_Raw(s_json* const object, t_char const* const name, t_char const* const raw)
{
	s_json* item_raw = JSON_CreateRaw(raw);
	if (add_item_to_object(object, name, item_raw, FALSE))
		return (item_raw);
	JSON_Delete(item_raw);
	return (NULL);
}

s_json*	JSON_AddToObject_Object(s_json* const object, t_char const* const name)
{
	s_json* item_object = JSON_CreateObject();
	if (add_item_to_object(object, name, item_object, FALSE))
		return (item_object);
	JSON_Delete(item_object);
	return (NULL);
}

s_json*	JSON_AddToObject_Array(s_json* const object, t_char const* const name)
{
	s_json* item_array = JSON_CreateArray();
	if (add_item_to_object(object, name, item_array, FALSE))
		return (item_array);
	JSON_Delete(item_array);
	return (NULL);
}
