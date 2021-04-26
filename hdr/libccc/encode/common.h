/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/encode/common.h                   |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_ENCODE_COMMON_H
#define __LIBCCC_ENCODE_COMMON_H
/*!@group{libccc_encode_common}
** @{
**	This header defines a dynamic runtime object type, similar to objects in JS.
**	- JSON spec: https://www.json.org/json-en.html
**
**	In particular, most of the code exposed from this header comes from cJSON:
**	- https://github.com/DaveGamble/cJSON
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"
#include "libccc/char.h"

HEADER_CPP


/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! An integer type which works as a bitflag enum, used to express a dynamiclly-typed value's type at runtime
typedef t_sint		t_dynamic;

//! These constants are the enum items/bitflags for the `t_dynamic` dynamic-type enum
//!@{
#define DYNAMIC_TYPE_INVALID	(t_dynamic)(0)		//!< value stored is invalid
#define DYNAMIC_TYPE_NULL		(t_dynamic)(1 << 0)	//!< no value stored
#define DYNAMIC_TYPE_BOOLEAN	(t_dynamic)(1 << 1)	//!< value stored as boolean: #t_bool
#define DYNAMIC_TYPE_INTEGER	(t_dynamic)(1 << 2)	//!< value stored as integer: #t_s64
#define DYNAMIC_TYPE_FLOAT		(t_dynamic)(1 << 3)	//!< value stored as floating-point number: #t_f64
#define DYNAMIC_TYPE_STRING		(t_dynamic)(1 << 4)	//!< value stored as string
#define DYNAMIC_TYPE_ARRAY		(t_dynamic)(1 << 5)	//!< value stored as array of values (no keys)
#define DYNAMIC_TYPE_OBJECT		(t_dynamic)(1 << 6)	//!< value stored as dict of values (with keys)
#define DYNAMIC_TYPE_RAW		(t_dynamic)(1 << 7)	//!< value stored as raw string (language-specific syntax)

#define DYNAMIC_TYPE_ISREFERENCE	(t_dynamic)(1 << 8)	//!< If this bit is set, the `value` is not to be freed
//!@}

//! The bitmask expressing the 'type enum' portion of a `t_dynamic` type specifier
#define DYNAMIC_TYPE_MASK	(0xFF)



//! A general key-value tree struct, used to model data for several file formats: INI, KVT, TOML, YAML, XML, etc
/*!
**	This struct can be used to store any kind of data, much like a general
**	extensible data file format: think INI, JSON, TOML, YAML, XML, etc.
**	The abbreviation "KVT" is used throughout the code to avoid writing `key_value_tree`, which is rather long.
**	In general, you should not use this struct directly, unless you wish to implement a new file format spec.
*/
typedef struct kvt
{
	struct kvt*	next;	//!< linked-list pointers to neighboring items
	struct kvt*	prev;	//!< linked-list pointers to neighboring items

	t_char*		key;	//!< The item's key string, if this item is the child of, or is in the list of subitems of, an object.
	t_dynamic	type;	//!< The type of the item: uses the `TOML_TYPE_*` macros defined above.
	union dynamic
	{
		t_bool		boolean;
		t_s64		integer;
		t_f64		number;
		t_char*		string;
		struct kvt*	child;
	}			value;	//!< The item's stored value (can be of any type)
}		s_kvt;



//! This union type can express a value of any major data type, see #t_dynamic
typedef union dynamic	u_dynamic;



#define foreach_s_kvt(_TYPE_, _VAR_, _KVT_)		foreach (_TYPE_, _VAR_, s_kvt, _KVT_)

#define foreach_s_kvt_init(		_TYPE_, _VAR_, _KVT_)	s_kvt const* _VAR_##_i = (_KVT_ != NULL ? (_KVT_)->value.child : NULL);
#define foreach_s_kvt_exit(		_TYPE_, _VAR_, _KVT_)	if ((_KVT_ != NULL) && (KVT_IsArray(_KVT_) || KVT_IsObject(_KVT_)))
#define foreach_s_kvt_loop_init(_TYPE_, _VAR_, _KVT_)	_TYPE_ _VAR_ = (_TYPE_)_VAR_##_i
#define foreach_s_kvt_loop_exit(_TYPE_, _VAR_, _KVT_)	(_VAR_##_i != NULL)
#define foreach_s_kvt_loop_incr(_TYPE_, _VAR_, _KVT_)	_VAR_##_i = _VAR_##_i->next
#define foreach_s_kvt_loop_setv(_TYPE_, _VAR_, _KVT_)	_VAR_ = (_VAR_##_i == NULL ? _VAR_ : (_TYPE_)_VAR_##_i)



/*!
**	Limits how deeply nested arrays/objects can be before KVT rejects to parse them.
**	The existence of this macro serves to prevent stack overflows.
*/
#ifndef KVT_NESTING_LIMIT
#define KVT_NESTING_LIMIT 1000
#endif



//! The 'errno' type for KVT data structure handling
typedef enum error_kvt
{
	ERROR_KVT_OK = 0,
	ERROR_KVT_PARSING,
	ERROR_KVT_INVALIDARGS,
	ERROR_KVT_ALLOCATIONFAILURE,
	ERROR_KVT_OBJECTKEYNOTFOUND,
	ERROR_KVT_INCORRECTTYPE,
	ERROR_KVT_INDEXTOOLARGE,
	ERROR_KVT_ENUMTOOLARGE,
	ERROR_KVT_ISREFERENCE,
}		e_error_kvt;



/*
** ************************************************************************** *|
**                             Basic KVT Operations                           *|
** ************************************************************************** *|
*/

//! Allocated one single KVT struct
s_kvt*	KVT_Item(void);



//! Duplicates a KVT object.
/*!
**	Duplicate will create a new, identical s_kvt item to the one you pass, in new memory that will
**	need to be released. With `recurse != FALSE`, it will duplicate any children connected to the item.
**	The item->next and ->prev pointers are always zero on return from Duplicate.
*/
s_kvt*	KVT_Duplicate(s_kvt const* item, t_bool recurse);



//! Recursively compare two s_kvt items for equality.
/*!
**	If either a or b is NULL or invalid, they will be considered unequal.
**	case_sensitive determines if object keys are treated case sensitive (1) or case insensitive (0).
*/
t_bool	KVT_Equals(s_kvt const* a, s_kvt const* b, t_bool case_sensitive);



//! Creates a new KVT object by concatenating two existing ones
/*!
**	TODO document
*/
s_kvt*	KVT_Concat(s_kvt const* a, s_kvt const* b);



//! The "get error" function, to be used after getting an unsatisfactory result return.
/*!
**	This function can be used for analysing failed parses.
**	This returns a pointer to the parse error location in the given KVT string.
**	You'll probably need to look a few chars back to make sense of it.
**	Defined when KVT_Parse() returns 0.
**	Otherwise, NULL when KVT_Parse() succeeds.
*/
e_error_kvt		KVT_GetError(void);
//! Sets the current 'errno' global
e_error_kvt		KVT_SetError(e_error_kvt error);
//! Returns the (string literal) error message corresponding to the given `error` number
t_char const*	KVT_GetErrorString(e_error_kvt error);
//! Returns a specific error message corresponding to the latest error
t_char*			KVT_GetErrorMessage(void);



/*
** ************************************************************************** *|
**                            KVT "create" Operations                         *|
** ************************************************************************** *|
*/

//! These functions create an `s_kvt` item of the appropriate type.
//!@{
s_kvt*	KVT_CreateNull(void);
s_kvt*	KVT_CreateBoolean(t_bool value);
s_kvt*	KVT_CreateInteger(t_s64 value);
s_kvt*	KVT_CreateFloat(t_f64 value);
s_kvt*	KVT_CreateString(t_char const* value);
s_kvt*	KVT_CreateArray(void);
s_kvt*	KVT_CreateObject(void);
s_kvt*	KVT_CreateRaw(t_char const* raw);
//!@}



//! Create a string where `value_string` references a string, so it will not be freed by KVT_Delete()
s_kvt*	KVT_CreateStringReference(t_char const* string);
//! Create an array that only references it's elements, so they will not be freed by KVT_Delete()
s_kvt*	KVT_CreateArrayReference(s_kvt const* child);
//! Create an object that only references it's elements, so they will not be freed by KVT_Delete()
s_kvt*	KVT_CreateObjectReference(s_kvt const* child);

//! Create and fill a KVT array
/*!
**	These utilities create a KVT array of `count` items.
**	The given `count` cannot be greater than the number of elements in
**	the given `numbers` array, otherwise array access will be out of bounds.
*/
//!@{
s_kvt*	KVT_CreateArray_Boolean	(t_bool const*	booleans, t_sint count);

s_kvt*	KVT_CreateArray_UInt	(t_uint const*	numbers, t_sint count);
s_kvt*	KVT_CreateArray_U8		(t_u8 const*	numbers, t_sint count);
s_kvt*	KVT_CreateArray_U16		(t_u16 const*	numbers, t_sint count);
s_kvt*	KVT_CreateArray_U32		(t_u32 const*	numbers, t_sint count);
s_kvt*	KVT_CreateArray_U64		(t_u64 const*	numbers, t_sint count);
#ifdef __int128
s_kvt*	KVT_CreateArray_U128	(t_u128 const*	numbers, t_sint count);
#endif

s_kvt*	KVT_CreateArray_SInt	(t_sint const*	numbers, t_sint count);
s_kvt*	KVT_CreateArray_S8		(t_s8 const*	numbers, t_sint count);
s_kvt*	KVT_CreateArray_S16		(t_s16 const*	numbers, t_sint count);
s_kvt*	KVT_CreateArray_S32		(t_s32 const*	numbers, t_sint count);
s_kvt*	KVT_CreateArray_S64		(t_s64 const*	numbers, t_sint count);
#ifdef __int128
s_kvt*	KVT_CreateArray_S128	(t_s128 const*	numbers, t_sint count);
#endif

s_kvt*	KVT_CreateArray_Float	(t_float const*	numbers, t_sint count);
s_kvt*	KVT_CreateArray_F32		(t_f32 const*	numbers, t_sint count);
s_kvt*	KVT_CreateArray_F64		(t_f64 const*	numbers, t_sint count);
#ifdef __float80
s_kvt*	KVT_CreateArray_F80		(t_f80 const*	numbers, t_sint count);
#endif
#ifdef __float128
s_kvt*	KVT_CreateArray_F128	(t_f128 const*	numbers, t_sint count);
#endif

s_kvt*	KVT_CreateArray_String	(t_char const* const* strings, t_sint count);
//!@}



/*
** ************************************************************************** *|
**                             KVT "get" Operations                           *|
** ************************************************************************** *|
*/

//! Returns the amount of items in an array (or object).
t_sint	KVT_GetArrayLength(s_kvt const* array);

//! Retrieve item number "index" from array "array". Returns NULL if unsuccessful.
s_kvt*	KVT_GetArrayItem(s_kvt const* array, t_sint index);



//! Get the item with the given `key` from the given `object`.
#define KVT_GetObjectItem \
		KVT_GetObjectItem_IgnoreCase
s_kvt*	KVT_GetObjectItem_IgnoreCase	(s_kvt const* object, t_char const* key);	//!< (case-insensitive)
s_kvt*	KVT_GetObjectItem_CaseSensitive	(s_kvt const* object, t_char const* key);	//!< (case-sensitive)

//! Returns `TRUE` if the given `object` contains an item with the given `key`.
#define KVT_HasObjectItem \
		KVT_HasObjectItem_IgnoreCase
t_bool	KVT_HasObjectItem_IgnoreCase	(s_kvt const* object, t_char const* key);	//!< (case-insensitive)
t_bool	KVT_HasObjectItem_CaseSensitive	(s_kvt const* object, t_char const* key);	//!< (case-sensitive)



//! Access the contents of a KVT with a 'KVT path', ie: a format string of 'accessors' (ie: strings or numbers in brackets)
/*!
**	@param	object		The KVT object to get an item from
**	@param	format_path	The format string with an accessor pattern (example: `KVT_Get(json, "[\"subarray\"][3][\"name\"]")`)
**	@param	...			The variadic arguments list which goes along with `format_path` (works like printf)
**	@returns the KVT object gotten from the given accessor path, or NULL if the path or KVT was invalid.
*/
s_kvt*	KVT_Get(s_kvt const* object, t_char const* format_path, ...)
_FORMAT(printf, 2, 3);

//! Returns the boolean value contained within the given `item`, or `FALSE` if type is not #KVT_TYPE_BOOLEAN.
t_bool	KVT_GetValue_Boolean(s_kvt const* item);
//! Returns the integer value contained within the given `item`, or `0` if type is not #KVT_TYPE_INTEGER.
t_s64	KVT_GetValue_Integer(s_kvt const* item);
//! Returns the number value contained within the given `item`, or `NAN` if type is not #KVT_TYPE_FLOAT.
t_f64	KVT_GetValue_Float	(s_kvt const* item);
//! Returns the string value contained within the given `item`, or `NULL` if type is not #KVT_TYPE_STRING.
t_char*	KVT_GetValue_String	(s_kvt const* item);



/*
** ************************************************************************** *|
**                             KVT "set" Operations                           *|
** ************************************************************************** *|
*/

//! Change the `value` of a #KVT_TYPE_BOOLEAN object, only takes effect when `object->type == KVT_TYPE_BOOLEAN`.
e_error_kvt	KVT_SetValue_Boolean(s_kvt* object, t_bool value);
//! Change the `value` of a #KVT_TYPE_INTEGER object, only takes effect when `object->type == KVT_TYPE_INTEGER`.
e_error_kvt	KVT_SetValue_Integer(s_kvt* object, t_s64 value);
//! Change the `value` of a #KVT_TYPE_FLOAT object, only takes effect when `object->type == KVT_TYPE_FLOAT`.
e_error_kvt	KVT_SetValue_Float	(s_kvt* object, t_f64 value);
//! Change the `value` of a #KVT_TYPE_STRING object, only takes effect when `object->type == KVT_TYPE_STRING`.
e_error_kvt	KVT_SetValue_String	(s_kvt* object, t_char* value);



//! Appends the given `item` to the given `array`.
e_error_kvt	KVT_AddToArray_Item(s_kvt* array, s_kvt* item);

//! Append a reference to `item` to the given `array`.
e_error_kvt	KVT_AddToArray_ItemReference(s_kvt* array, s_kvt* item);



//! Appends the given `item` to the given `object`, with the given `key`.
e_error_kvt	KVT_AddToObject_Item(s_kvt* object, t_char const* key, s_kvt* item);

//! Append reference to item to the given object.
e_error_kvt	KVT_AddToObject_ItemReference(s_kvt* object, t_char const* key, s_kvt* item);



/*!
**	Helper functions for creating and adding items to an object at the same time.
**	They return the added item or NULL on failure.
*/
//!@{
s_kvt*	KVT_AddToObject_Null	(s_kvt* object, t_char const* key);
s_kvt*	KVT_AddToObject_Boolean	(s_kvt* object, t_char const* key, t_bool value);
s_kvt*	KVT_AddToObject_Integer	(s_kvt* object, t_char const* key, t_s64 value);
s_kvt*	KVT_AddToObject_Float	(s_kvt* object, t_char const* key, t_f64 value);
s_kvt*	KVT_AddToObject_String	(s_kvt* object, t_char const* key, t_char const* value);
s_kvt*	KVT_AddToObject_Object	(s_kvt* object, t_char const* key);
s_kvt*	KVT_AddToObject_Array	(s_kvt* object, t_char const* key);
s_kvt*	KVT_AddToObject_Raw		(s_kvt* object, t_char const* key, t_char const* raw);
//!@}



/*
** ************************************************************************** *|
**                             KVT Check Operations                           *|
** ************************************************************************** *|
*/

//! These functions are used to check the type of an item.
//!@{
t_bool	KVT_IsInvalid	(s_kvt const* item);
t_bool	KVT_IsNull		(s_kvt const* item);
t_bool	KVT_IsBoolean	(s_kvt const* item);
t_bool	KVT_IsInteger	(s_kvt const* item);
t_bool	KVT_IsFloat		(s_kvt const* item);
t_bool	KVT_IsString	(s_kvt const* item);
t_bool	KVT_IsArray		(s_kvt const* item);
t_bool	KVT_IsObject	(s_kvt const* item);
t_bool	KVT_IsRaw		(s_kvt const* item);
//!@}



// TODO add "check for name conflicts" function



/*
** ************************************************************************** *|
**                             KVT Other Operations                           *|
** ************************************************************************** *|
*/

//! Removes (without deleting) the given `item` from the given `parent` object.
s_kvt*		KVT_Detach(s_kvt* parent, s_kvt* item);

//! Delete a s_kvt entity and all subentities.
e_error_kvt	KVT_Delete(s_kvt* item);

//! Replaces the given `item` from the given `parent` object, with the given `newitem`.
e_error_kvt	KVT_Replace(s_kvt* parent, s_kvt* item, s_kvt* newitem);



//! Deletes the item at the given `index` from the given `array`.
e_error_kvt	KVT_Delete_FromArray(s_kvt* array, t_sint index);

//! Removes (without deleting) the given `item` from the given `array`.
s_kvt*		KVT_Detach_FromArray(s_kvt* array, t_sint index);

//! Replaces the given `item` from the given `array`, with the given `newitem`.
e_error_kvt	KVT_Replace_InArray(s_kvt* array, t_sint index, s_kvt* newitem);

//! Inserts the given `newitem` in the givne `array`, shifting pre-existing items to the right.
e_error_kvt	KVT_Insert_InArray(s_kvt* array, t_sint index, s_kvt* newitem);



//! Deletes the item with the given `key` from the given `object`.
//!@{
#define 	KVT_Delete_FromObject \
			KVT_Delete_FromObject_IgnoreCase
e_error_kvt	KVT_Delete_FromObject_IgnoreCase	(s_kvt* object, t_char const* key); //!< (case-insensitive)
e_error_kvt	KVT_Delete_FromObject_CaseSensitive	(s_kvt* object, t_char const* key); //!< (case-sensitive)
//!@}

//! Removes (without deleting) the given `item` from the given `object`.
//!@{
#define 	KVT_Detach_FromObject \
			KVT_Detach_FromObject_IgnoreCase
s_kvt*		KVT_Detach_FromObject_IgnoreCase	(s_kvt* object, t_char const* key); //!< (case-insensitive)
s_kvt*		KVT_Detach_FromObject_CaseSensitive	(s_kvt* object, t_char const* key); //!< (case-sensitive)
//!@}

//! Replaces the given `item` from the given `object`, with the given `newitem`
//!@{
#define 	KVT_Replace_InObject \
			KVT_Replace_InObject_IgnoreCase
e_error_kvt	KVT_Replace_InObject_IgnoreCase		(s_kvt* object, t_char const* key, s_kvt* newitem); //!< (case-insensitive)
e_error_kvt	KVT_Replace_InObject_CaseSensitive	(s_kvt* object, t_char const* key, s_kvt* newitem); //!< (case-sensitive)
//!@}



/*! @} */
HEADER_END
#endif
