
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_HANDLE_INCLUDE



static
s_kvt*	create_reference(s_kvt const* item)
{
	s_kvt* reference = NULL;

	HANDLE_ERROR(NULLPOINTER, (item == NULL), return (NULL);)
	reference = KVT_Item();
	HANDLE_ERROR(ALLOCFAILURE, (reference == NULL), return (NULL);)
	Memory_Copy(reference, item, sizeof(s_kvt));
	reference->key = NULL;
	reference->type |= DYNAMICTYPE_ISREFERENCE;
	reference->next = reference->prev = NULL;
	return (reference);
}



static
e_stderror	add_item_to_array(s_kvt* array, s_kvt* item)
{
	s_kvt* child = NULL;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (ERROR_NULLPOINTER);)
	HANDLE_ERROR(NULLPOINTER, (item  == NULL), return (ERROR_NULLPOINTER);)
	HANDLE_ERROR(INVALIDARGS, (array == item), return (ERROR_INVALIDARGS);)
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
e_stderror	add_item_to_object(s_kvt* object, t_char const* key, s_kvt* item)
{
	t_char* new_key = NULL;
	t_sint new_type = DYNAMICTYPE_INVALID;

	HANDLE_ERROR(NULLPOINTER, (object == NULL), return (ERROR_NULLPOINTER);)
	HANDLE_ERROR(NULLPOINTER, (key    == NULL), return (ERROR_NULLPOINTER);)
	HANDLE_ERROR(NULLPOINTER, (item   == NULL), return (ERROR_NULLPOINTER);)
	HANDLE_ERROR(INVALIDARGS, (object == item), return (ERROR_INVALIDARGS);)
	new_key = (t_char*)String_Duplicate((t_char const*)key);
	HANDLE_ERROR(ALLOCFAILURE, (new_key == NULL), return (ERROR_ALLOCFAILURE);)
	if (item->key)
		Memory_Free(item->key);
	item->key = new_key;
	item->type = new_type;
	return (KVT_AddToArray_Item(object, item));
}



e_stderror	KVT_AddToArray_Item(s_kvt* array, s_kvt* item)
{
	return (add_item_to_array(array, item));
}

e_stderror	KVT_AddToArray_ItemReference(s_kvt* array, s_kvt* item)
{
	return (add_item_to_array(array, create_reference(item)));
}



e_stderror	KVT_AddToObject_Item(s_kvt* object, t_char const* key, s_kvt* item)
{
	return (add_item_to_object(object, key, item));
}

e_stderror	KVT_AddToObject_ItemReference(s_kvt* object, t_char const* key, s_kvt* item)
{
	return (add_item_to_object(object, key, create_reference(item)));
}



s_kvt*	KVT_AddToObject_Null(s_kvt* object, t_char const* key)
{
	s_kvt* item_null = KVT_CreateNull();
	e_stderror error = add_item_to_object(object, key, item_null);
	HANDLE_ERROR(UNSPECIFIED, (error),
		KVT_Delete(item_null);
		return (NULL);)
	return (item_null);
}

s_kvt*	KVT_AddToObject_Boolean(s_kvt* object, t_char const* key, t_bool value)
{
	s_kvt* item_bool = KVT_CreateBoolean(value);
	e_stderror error = add_item_to_object(object, key, item_bool);
	HANDLE_ERROR(UNSPECIFIED, (error),
		KVT_Delete(item_bool);
		return (NULL);)
	return (item_bool);
}

s_kvt*	KVT_AddToObject_Integer(s_kvt* object, t_char const* key, t_s64 value)
{
	s_kvt* item_number = KVT_CreateInteger(value);
	e_stderror error = add_item_to_object(object, key, item_number);
	HANDLE_ERROR(UNSPECIFIED, (error),
		KVT_Delete(item_number);
		return (NULL);)
	return (item_number);
}

s_kvt*	KVT_AddToObject_Float(s_kvt* object, t_char const* key, t_f64 value)
{
	s_kvt* item_number = KVT_CreateFloat(value);
	e_stderror error = add_item_to_object(object, key, item_number);
	HANDLE_ERROR(UNSPECIFIED, (error),
		KVT_Delete(item_number);
		return (NULL);)
	return (item_number);
}

s_kvt*	KVT_AddToObject_String(s_kvt* object, t_char const* key, t_char const* string)
{
	s_kvt* item_string = KVT_CreateString(string);
	e_stderror error = add_item_to_object(object, key, item_string);
	HANDLE_ERROR(UNSPECIFIED, (error),
		KVT_Delete(item_string);
		return (NULL);)
	return (item_string);
}

s_kvt*	KVT_AddToObject_Raw(s_kvt* object, t_char const* key, t_char const* raw)
{
	s_kvt* item_raw = KVT_CreateRaw(raw);
	e_stderror error = add_item_to_object(object, key, item_raw);
	HANDLE_ERROR(UNSPECIFIED, (error),
		KVT_Delete(item_raw);
		return (NULL);)
	return (item_raw);
}

s_kvt*	KVT_AddToObject_Object(s_kvt* object, t_char const* key)
{
	s_kvt* item_object = KVT_CreateObject();
	e_stderror error = add_item_to_object(object, key, item_object);
	HANDLE_ERROR(UNSPECIFIED, (error),
		KVT_Delete(item_object);
		return (NULL);)
	return (item_object);
}

s_kvt*	KVT_AddToObject_Array(s_kvt* object, t_char const* key)
{
	s_kvt* item_array = KVT_CreateArray();
	e_stderror error = add_item_to_object(object, key, item_array);
	HANDLE_ERROR(UNSPECIFIED, (error),
		KVT_Delete(item_array);
		return (NULL);)
	return (item_array);
}
