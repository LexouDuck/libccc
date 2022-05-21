
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



static
s_kvt*	KVT_AddTo_CreateReference(s_kvt const* item)
{
	s_kvt* reference = NULL;

	if CCCERROR((item == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	reference = KVT_Item();
	if CCCERROR((reference == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	Memory_Copy(reference, item, sizeof(s_kvt));
	reference->key = NULL;
	reference->type |= DYNAMICTYPE_ISREFERENCE;
	reference->next = reference->prev = NULL;
	return (reference);
}



static
e_cccerror	KVT_AddToArray(s_kvt* array, s_kvt* item)
{
	s_kvt* child = NULL;

	if CCCERROR((array == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR_NULLPOINTER);
	if CCCERROR((item  == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR_NULLPOINTER);
	if CCCERROR((array == item), ERROR_INVALIDARGS, "cannot add array to itself")
		return (ERROR_INVALIDARGS);
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
	return (ERROR_NONE);
}



static
e_cccerror	KVT_AddToObject(s_kvt* object, t_char const* key, s_kvt* item)
{
	t_char* new_key = NULL;

	if CCCERROR((object == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR_NULLPOINTER);
	if CCCERROR((key    == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR_NULLPOINTER);
	if CCCERROR((item   == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR_NULLPOINTER);
	if CCCERROR((object == item), ERROR_INVALIDARGS, "cannot add object to itself")
		return (ERROR_INVALIDARGS);
	new_key = (t_char*)String_Duplicate((t_char const*)key);
	if CCCERROR((new_key == NULL), ERROR_ALLOCFAILURE, NULL)
		return (ERROR_ALLOCFAILURE);
	if (item->key)
		Memory_Free(item->key);
	item->key = new_key;
	return (KVT_AddToArray_Item(object, item));
}



e_cccerror	KVT_AddToArray_Item(s_kvt* array, s_kvt* item)
{
	return (KVT_AddToArray(array, item));
}

e_cccerror	KVT_AddToArray_ItemReference(s_kvt* array, s_kvt* item)
{
	return (KVT_AddToArray(array, KVT_AddTo_CreateReference(item)));
}



e_cccerror	KVT_AddToObject_Item(s_kvt* object, t_char const* key, s_kvt* item)
{
	return (KVT_AddToObject(object, key, item));
}

e_cccerror	KVT_AddToObject_ItemReference(s_kvt* object, t_char const* key, s_kvt* item)
{
	return (KVT_AddToObject(object, key, KVT_AddTo_CreateReference(item)));
}



s_kvt*	KVT_AddToObject_Null(s_kvt* object, t_char const* key)
{
	s_kvt* item_null = KVT_CreateNull();
	e_cccerror error = KVT_AddToObject(object, key, item_null);
	if CCCERROR((error), ERROR_UNSPECIFIED, 
		"could not add null-type value to object, with key=\"%s\"", key)
	KVT_Delete(item_null);
		return (NULL);
	return (item_null);
}

s_kvt*	KVT_AddToObject_Boolean(s_kvt* object, t_char const* key, t_bool value)
{
	s_kvt* item_bool = KVT_CreateBoolean(value);
	e_cccerror error = KVT_AddToObject(object, key, item_bool);
	if CCCERROR((error), ERROR_UNSPECIFIED, 
		"could not add boolean-type value to object, with key=\"%s\"", key)
	KVT_Delete(item_bool);
		return (NULL);
	return (item_bool);
}

s_kvt*	KVT_AddToObject_Integer(s_kvt* object, t_char const* key, t_s64 value)
{
	s_kvt* item_number = KVT_CreateInteger(value);
	e_cccerror error = KVT_AddToObject(object, key, item_number);
	if CCCERROR((error), ERROR_UNSPECIFIED, 
		"could not add integer-type value to object, with key=\"%s\"", key)
	KVT_Delete(item_number);
		return (NULL);
	return (item_number);
}

s_kvt*	KVT_AddToObject_Float(s_kvt* object, t_char const* key, t_f64 value)
{
	s_kvt* item_number = KVT_CreateFloat(value);
	e_cccerror error = KVT_AddToObject(object, key, item_number);
	if CCCERROR((error), ERROR_UNSPECIFIED, 
		"could not add float-type value to object, with key=\"%s\"", key)
	KVT_Delete(item_number);
		return (NULL);
	return (item_number);
}

s_kvt*	KVT_AddToObject_String(s_kvt* object, t_char const* key, t_char const* string)
{
	s_kvt* item_string = KVT_CreateString(string);
	e_cccerror error = KVT_AddToObject(object, key, item_string);
	if CCCERROR((error), ERROR_UNSPECIFIED, 
		"could not add string-type value to object, with key=\"%s\"", key)
	KVT_Delete(item_string);
		return (NULL);
	return (item_string);
}

s_kvt*	KVT_AddToObject_Raw(s_kvt* object, t_char const* key, t_char const* raw)
{
	s_kvt* item_raw = KVT_CreateRaw(raw);
	e_cccerror error = KVT_AddToObject(object, key, item_raw);
	if CCCERROR((error), ERROR_UNSPECIFIED, 
		"could not add raw-type value to object, with key=\"%s\"", key)
	KVT_Delete(item_raw);
		return (NULL);
	return (item_raw);
}

s_kvt*	KVT_AddToObject_Object(s_kvt* object, t_char const* key)
{
	s_kvt* item_object = KVT_CreateObject();
	e_cccerror error = KVT_AddToObject(object, key, item_object);
	if CCCERROR((error), ERROR_UNSPECIFIED, 
		"could not add object-type value to object, with key=\"%s\"", key)
	KVT_Delete(item_object);
		return (NULL);
	return (item_object);
}

s_kvt*	KVT_AddToObject_Array(s_kvt* object, t_char const* key)
{
	s_kvt* item_array = KVT_CreateArray();
	e_cccerror error = KVT_AddToObject(object, key, item_array);
	if CCCERROR((error), ERROR_UNSPECIFIED, 
		"could not add array-type value to object, with key=\"%s\"", key)
	KVT_Delete(item_array);
		return (NULL);
	return (item_array);
}
