/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/array/json.h                      |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_ARRAY_JSON_H
#define __LIBCCC_ARRAY_JSON_H
/*!@group{libccc_array_json}
** @{
**	This header defines a dynamic runtime object type, similar to objects in JS.
**	In particular, most of the code exposed from this header comes from s_json:
**	https://github.com/DaveGamble/s_json
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

/*!
**	s_json Types enum/bitflag
*/
typedef t_sint		t_json_type;

#define JSON_TYPE_INVALID	(t_json_type)(0)
#define JSON_TYPE_FALSE		(t_json_type)(1 << 0)
#define JSON_TYPE_TRUE		(t_json_type)(1 << 1)
#define JSON_TYPE_NULL		(t_json_type)(1 << 2)
#define JSON_TYPE_NUMBER	(t_json_type)(1 << 3)
#define JSON_TYPE_STRING	(t_json_type)(1 << 4)
#define JSON_TYPE_ARRAY		(t_json_type)(1 << 5)
#define JSON_TYPE_OBJECT	(t_json_type)(1 << 6)
#define JSON_TYPE_RAW		(t_json_type)(1 << 7) // raw json

#define JSON_TYPE_ISREFERENCE	(t_json_type)(1 << 8)
#define JSON_TYPE_CONSTSTRING	(t_json_type)(1 << 9)



/*!
**	The s_json structure: nest-able, list-able, etc
*/
typedef struct	json
{
	struct json*	next;	//!< linked-list pointers to neighboring items
	struct json*	prev;	//!< linked-list pointers to neighboring items

	struct json*	child;	//!< An array or object item will have a child pointer pointing to a chain of the items in the array/object.

	t_json_type	type;		//!< The type of the item: uses the `JSON_TYPE_*` macros defined above.

	t_char*		key;		//!< The item's name string, if this item is the child of, or is in the list of subitems of an object.

	t_char*		value_string;	//!< The item's string, if `type == JSON_TYPE_STRING || type == JSON_TYPE_RAW`
	t_f64		value_double;	//!< The item's number, if `type == JSON_TYPE_NUMBER`
}				s_json;

/*!
**	Limits how deeply nested arrays/objects can be before s_json rejects to parse them.
**	This is to prevent stack overflows.
*/
#ifndef JSON_NESTING_LIMIT
#define JSON_NESTING_LIMIT 1000
#endif



#define foreach_s_json(_TYPE_, _VAR_, _JSON_)		foreach (_TYPE_, _VAR_, s_json, _JSON_)

#define foreach_s_json_init(		_TYPE_, _VAR_, _JSON_)	s_json const* _VAR_##_i = (_JSON_ != NULL ? (_JSON_)->child : NULL);
#define foreach_s_json_exit(		_TYPE_, _VAR_, _JSON_)	if (_JSON_ != NULL)
#define foreach_s_json_loop_init(	_TYPE_, _VAR_, _JSON_)	_TYPE_ _VAR_ = (_TYPE_)_VAR_##_i
#define foreach_s_json_loop_exit(	_TYPE_, _VAR_, _JSON_)	(_VAR_##_i != NULL)
#define foreach_s_json_loop_incr(	_TYPE_, _VAR_, _JSON_)	_VAR_##_i = _VAR_##_i->next
#define foreach_s_json_loop_setv(	_TYPE_, _VAR_, _JSON_)	_VAR_ = (_VAR_##_i == NULL ? _VAR_ : (_TYPE_)_VAR_##_i)
/*
#define foreach_s_json_init(		TYPE, VAR, JSON)	foreach_s_json_init_1(TYPE, VAR, JSON); foreach_s_json_init_2(TYPE, VAR, JSON);
#define foreach_s_json_init_1(		TYPE, VAR, JSON)	t_size VAR##_i = 0
#define foreach_s_json_init_2(		TYPE, VAR, JSON)	s_json* VAR = (JSON)
#define foreach_s_json_exit(		TYPE, VAR, JSON)	if (JSON)
#define foreach_s_json_loop_init(	TYPE, VAR, JSON)	VAR = (JSON != NULL) ? (JSON)->child : NULL
#define foreach_s_json_loop_exit(	TYPE, VAR, JSON)	VAR != NULL
#define foreach_s_json_loop_incr(	TYPE, VAR, JSON)	++VAR##_i, VAR = VAR->next
*/


/*
** ************************************************************************** *|
**                             Basic JSON Operations                          *|
** ************************************************************************** *|
*/

//! Create a new `s_json` object, parsed from a (valid) JSON string
/*!
**	Memory Management: the caller is always responsible to free the results,
**	from all variants of JSON_Parse() (by using JSON_Delete()) and JSON_Print()
**	(with stdlib free(), JSON_Hooks.free_fn(), or JSON_free() as appropriate).
**	The exception is JSON_PrintPreallocated(), where the caller has full responsibility of the buffer.
**	Supply a block of JSON, and this returns a `s_json` object you can interrogate.
*/
s_json*	JSON_Parse(t_char const* value);
//! Create a new `s_json` object, parsed from a (valid) JSON string, (only the first `buffer_length` chars are parsed)
s_json*	JSON_Parse_N(t_char const* value, t_size buffer_length);
//! Create a new `s_json` object, parsed from a (valid) JSON string
/*!
**	JSON_ParseStrict() allows you to require (and check) that the JSON is null terminated,
**	and to retrieve the pointer to the final byte parsed.
**	If you supply a ptr in return_parse_end and parsing fails, then `return_parse_end`
**	will contain a pointer to the error, such that it will match the return of JSON_GetErrorPtr().
*/
s_json*	JSON_ParseStrict(t_char const* value, t_char const* *return_parse_end, t_bool require_null_terminated);
//! Create a new `s_json` object, parsed from a (valid) JSON string, (only the first `buffer_length` chars are parsed)
s_json*	JSON_ParseStrict_N(t_char const* value, t_size buffer_length, t_char const* *return_parse_end, t_bool require_null_terminated);



//! Render a s_json entity to text for transfer/storage.
t_char*	JSON_Print(s_json const* item);
//! Render a s_json entity to text for transfer/storage without any formatting.
t_char*	JSON_PrintUnformatted(s_json const* item);
//! Render a s_json entity to text using a buffered strategy. prebuffer is a guess at the final size. guessing well reduces reallocation. fmt=0 gives unformatted, =1 gives formatted.
t_char*	JSON_PrintBuffered(s_json const* item, t_sint prebuffer, t_bool fmt);
//! Render a s_json entity to text using a buffer already allocated in memory with given length. Returns 1 on success and 0 on failure.
//! NOTE: s_json is not always 100% accurate in estimating how much memory it will use, so to be safe allocate 5 bytes more than you actually need.
t_bool	JSON_PrintPreallocated(s_json* item, t_char* buffer, t_sint const length, t_bool const format);



//! Returns the number of items in an array (or object).
t_sint	JSON_GetArraySize(s_json const* array);
//! Retrieve item number "index" from array "array". Returns NULL if unsuccessful.
s_json*	JSON_GetArrayItem(s_json const* array, t_sint index);

//! Get item "string" from object. Case insensitive.
s_json*	JSON_GetObjectItem				(s_json const* const object, t_char const* const key);
s_json*	JSON_GetObjectItem_CaseSensitive(s_json const* const object, t_char const* const key);

t_bool	JSON_HasObjectItem(s_json const* object, t_char const* key);



//! Access the contents of a JSON with a 'JSON path', ie: a format string of 'accessors' (ie: strings or numbers in brackets)
s_json*	JSON_Get(s_json const* object, char const* format_path, ...)
_FORMAT(printf, 2, 3);

//! Returns the value contained within the given `item`.
t_f64	JSON_GetValue_Number(s_json const* const item);
//! Returns the value contained within the given `item`.
t_char*	JSON_GetValue_String(s_json const* const item);



//! Change the `value_number` of a JSON_TYPE_STRING object, only takes effect when type of object is JSON_TYPE_STRING.
t_f64	JSON_SetValue_Number(s_json* object, t_f64 value);
//! Change the `value_string` of a JSON_TYPE_STRING object, only takes effect when type of object is JSON_TYPE_STRING.
t_char*	JSON_SetValue_String(s_json* object, t_char* value);



//! These functions check the type of an item.
t_bool	JSON_IsInvalid	(s_json const* const item);
t_bool	JSON_IsNull		(s_json const* const item);
t_bool	JSON_IsFalse	(s_json const* const item);
t_bool	JSON_IsTrue		(s_json const* const item);
t_bool	JSON_IsBool		(s_json const* const item);
t_bool	JSON_IsNumber	(s_json const* const item);
t_bool	JSON_IsString	(s_json const* const item);
t_bool	JSON_IsArray	(s_json const* const item);
t_bool	JSON_IsObject	(s_json const* const item);
t_bool	JSON_IsRaw		(s_json const* const item);



//! These calls create a s_json item of the appropriate type.
s_json*	JSON_CreateNull(void);
s_json*	JSON_CreateTrue(void);
s_json*	JSON_CreateFalse(void);
s_json*	JSON_CreateBool(t_bool boolean);
s_json*	JSON_CreateNumber(t_f64 num);
s_json*	JSON_CreateString(t_char const* string);
s_json*	JSON_CreateRaw(t_char const* raw);
s_json*	JSON_CreateArray(void);
s_json*	JSON_CreateObject(void);

//! Create a string where `value_string` references a string, so it will not be freed by JSON_Delete()
s_json*	JSON_CreateStringReference(t_char const* string);
//! Create an array that only references it's elements, so they will not be freed by JSON_Delete()
s_json*	JSON_CreateArrayReference(s_json const* child);
//! Create an object that only references it's elements, so they will not be freed by JSON_Delete()
s_json*	JSON_CreateObjectReference(s_json const* child);

//! Create and fill a JSON array
/*!
**	These utilities create a JSON array of `count` items.
**	The given `count` cannot be greater than the number of elements in
**	the given `numbers` array, otherwise array access will be out of bounds.
*/
s_json*	JSON_CreateIntArray		(t_sint const* numbers, t_sint count);
s_json*	JSON_CreateFloatArray	(t_f32 const* numbers, t_sint count);
s_json*	JSON_CreateDoubleArray	(t_f64 const* numbers, t_sint count);
s_json*	JSON_CreateStringArray	(t_char const* const *strings, t_sint count);



//! Appends an item to the given array.
t_bool	JSON_AddToArray_Item(s_json* array, s_json* item);

//! Append reference to item to the given array.
t_bool	JSON_AddToArray_ItemReference(s_json* array, s_json* item);

//! Appends an item to the given object.
t_bool	JSON_AddToObject_Item(s_json* object, t_char const* string, s_json* item);

//! Appends an item to an object with constant string as key
/*!
**	Use this when string is definitely const (i.e. a literal, or as good as), and will definitely survive the JSON object.
**	NOTE: When this function was used, make sure to always perform the following check:
**	`(item->type & JSON_TYPE_CONSTSTRING) == 0` before writing to `item->string`.
*/
t_bool	JSON_AddToObject_ItemCS(s_json* object, t_char const* key, s_json* item);

//! Append reference to item to the given object.
t_bool	JSON_AddToObject_ItemReference(s_json* object, t_char const* key, s_json* item);

/*!
**	Helper functions for creating and adding items to an object at the same time.
**	They return the added item or NULL on failure.
*/
s_json*	JSON_AddToObject_Null	(s_json* const object, t_char const* key);
s_json*	JSON_AddToObject_True	(s_json* const object, t_char const* key);
s_json*	JSON_AddToObject_False	(s_json* const object, t_char const* key);
s_json*	JSON_AddToObject_Bool	(s_json* const object, t_char const* key, t_bool boolean);
s_json*	JSON_AddToObject_Number	(s_json* const object, t_char const* key, t_f64 number);
s_json*	JSON_AddToObject_String	(s_json* const object, t_char const* key, t_char const* string);
s_json*	JSON_AddToObject_Raw	(s_json* const object, t_char const* key, t_char const* raw);
s_json*	JSON_AddToObject_Object	(s_json* const object, t_char const* key);
s_json*	JSON_AddToObject_Array	(s_json* const object, t_char const* key);



//! Shifts pre-existing items to the right.
t_bool	JSON_InsertItemInArray(s_json* array, t_sint index, s_json* newitem);



//! Delete a s_json entity and all subentities.
void	JSON_Delete(s_json* item);

//! Deletes the item at the given `index` from the given `array`.
void	JSON_DeleteItemFromArray				(s_json* array, t_sint index);
//! Deletes the item with the given `key` from the given `object`.
void	JSON_DeleteItemFromObject				(s_json* object, t_char const* key);
void	JSON_DeleteItemFromObject_CaseSensitive	(s_json* object, t_char const* key);



//! Removes (without deleting) the given `item` from the given `parent` object.
s_json*	JSON_DetachItem(s_json* parent, s_json* const item);
//! Removes (without deleting) the given `item` from the given `array`.
s_json*	JSON_DetachItemFromArray				(s_json* array, t_sint index);
//! Removes (without deleting) the given `item` from the given `object`.
s_json*	JSON_DetachItemFromObject				(s_json* object, t_char const* key);
s_json*	JSON_DetachItemFromObject_CaseSensitive	(s_json* object, t_char const* key);


//! Replaces the given `item` from the given `parent` object, with the given `newitem`.
t_bool	JSON_ReplaceItem(s_json* parent, s_json* item, s_json* newitem);
//! Replaces the given `item` from the given `array`, with the given `newitem`.
t_bool	JSON_ReplaceItemInArray					(s_json* array, t_sint index, s_json* newitem);
//! Replaces the given `item` from the given `object`, with the given `newitem`.
t_bool	JSON_ReplaceItemInObject				(s_json* object, t_char const* key, s_json* newitem);
t_bool	JSON_ReplaceItemInObject_CaseSensitive	(s_json* object, t_char const* key, s_json* newitem);



//! Duplicates a JSON object.
/*!
**	Duplicate will create a new, identical s_json item to the one you pass, in new memory that will
**	need to be released. With recurse!=0, it will duplicate any children connected to the item.
**	The item->next and ->prev pointers are always zero on return from Duplicate.
*/
s_json*	JSON_Duplicate(s_json const* item, t_bool recurse);



//! Recursively compare two s_json items for equality.
/*!
**	If either a or b is NULL or invalid, they will be considered unequal.
**	case_sensitive determines if object keys are treated case sensitive (1) or case insensitive (0).
*/
t_bool	JSON_Equals(s_json const* const a, s_json const* const b, t_bool const case_sensitive);



//! Minify a JSON string, to make it more lightweight: removes all whitespace characters
/*!
**	Minify a JSON, removing blank characters (such as ' ', '\t', '\r', '\n') from strings.
**	The input pointer json cannot point to a read-only address area, such as a string constant, 
**	but should point to a readable and writable adress area.
*/
void	JSON_Minify(t_char* json);



//! The error message function
/*!
**	For analysing failed parses.
**	This returns a pointer to the parse error.
**	You'll probably need to look a few chars back to make sense of it.
**	Defined when JSON_Parse() returns 0. 0 when JSON_Parse() succeeds.
*/
t_char const*	JSON_GetErrorPtr(void);



/*! @} */
HEADER_END
#endif
