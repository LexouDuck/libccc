/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/encode/toml.h                     |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_ENCODE_TOML_H
#define __LIBCCC_ENCODE_TOML_H
/*!@group{libccc_encode_toml}
** @{
**	This header defines a simple API to manipulate TOML and/or INI files.
**	- TOML spec: https://toml.io/en/v1.0.0#spec
**	- INI files: https://en.wikipedia.org/wiki/INI_file
**
**	This API is made to be compatible with both the TOML file spec and the INI file spec.
**	So, this means a couple of things in particular:
**	- (TOML/INI) All whitespace characters are handled (including the rare form-feed and vertical-tab chars)
**	- (TOML/INI) There cannot be any name conflicts between keys or sections names within a given scope.
**	- (TOML/INI) Comments can be started with either a ';' char or a '#' (when not inside a quoted string)
**	- (TOML) Sections can be nested
**	- (TOML) Key strings can be quoted, to allow for more characters than a token `[A-Za-z0-9_-]`
**	- (TOML) Strings with whitespace should always be quoted`, triple double-quotes for multi-line strings
**	- (TOML) Strings can be single-quoted, this makes a literal verbatim string (no character escaping)
**	- (TOML) All types are supported, except for dates (which must be stored as string or integer)
**	- (TOML) All numeric literal notations are accepted ("0x" = hexadecimal, "0o" = octal, "0b" = binary)
**	- Arrays can be written using curly braces '{' and '}', to avoid confusion with sections
**	- Unlike regular TOML, this API can behave in a case-sensitive fashion, if needed
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
**	TOML value data ypes enum/bitflag
*/
typedef t_sint		t_toml_type;

#define TOML_TYPE_INVALID	(t_toml_type)(0)
#define TOML_TYPE_NULL		(t_toml_type)(1 << 0)
#define TOML_TYPE_BOOLEAN	(t_toml_type)(1 << 1)
#define TOML_TYPE_INTEGER	(t_toml_type)(1 << 2)
#define TOML_TYPE_FLOAT		(t_toml_type)(1 << 3)
#define TOML_TYPE_STRING	(t_toml_type)(1 << 4)
#define TOML_TYPE_ARRAY		(t_toml_type)(1 << 5)
#define TOML_TYPE_OBJECT	(t_toml_type)(1 << 6)
#define TOML_TYPE_RAW		(t_toml_type)(1 << 7) // raw toml

#define TOML_TYPE_MASK	(0xFF)

#define TOML_TYPE_ISREFERENCE	(t_toml_type)(1 << 8)
#define TOML_TYPE_CONSTSTRING	(t_toml_type)(1 << 9)

typedef struct	toml	s_toml;

//! This union type can express a value of any (TOML-compatible) data type
typedef union toml_value
{
	t_bool	boolean;
	t_s64	integer;
	t_f64	floating;
	t_char*	string;
	s_toml*	child;
}		u_toml_value;

/*!
**	The s_toml structure: nest-able, list-able, etc
*/
typedef struct	toml
{
	struct toml*	next;	//!< linked-list pointers to neighboring items
	struct toml*	prev;	//!< linked-list pointers to neighboring items

	t_char*			key;	//!< The item's name string, if this item is the child of, or is in the list of subitems of an object.
	t_toml_type		type;	//!< The type of the item: uses the `TOML_TYPE_*` macros defined above.
	u_toml_value	value;	//!< The item's stored value (can be of any type)
}				s_toml;

/*!
**	Limits how deeply nested arrays/objects can be before s_toml rejects to parse them.
**	This is to prevent stack overflows.
*/
#ifndef TOML_NESTING_LIMIT
#define TOML_NESTING_LIMIT 1000
#endif



#define foreach_s_toml(_TYPE_, _VAR_, _TOML_)		foreach (_TYPE_, _VAR_, s_toml, _TOML_)

#define foreach_s_toml_init(		_TYPE_, _VAR_, _TOML_)	s_toml const* _VAR_##_i = (_TOML_ != NULL ? (_TOML_)->child : NULL);
#define foreach_s_toml_exit(		_TYPE_, _VAR_, _TOML_)	if (_TOML_ != NULL)
#define foreach_s_toml_loop_init(	_TYPE_, _VAR_, _TOML_)	_TYPE_ _VAR_ = (_TYPE_)_VAR_##_i
#define foreach_s_toml_loop_exit(	_TYPE_, _VAR_, _TOML_)	(_VAR_##_i != NULL)
#define foreach_s_toml_loop_incr(	_TYPE_, _VAR_, _TOML_)	_VAR_##_i = _VAR_##_i->next
#define foreach_s_toml_loop_setv(	_TYPE_, _VAR_, _TOML_)	_VAR_ = (_VAR_##_i == NULL ? _VAR_ : (_TYPE_)_VAR_##_i)
/*
#define foreach_s_toml_init(		TYPE, VAR, TOML)	foreach_s_toml_init_1(TYPE, VAR, TOML); foreach_s_toml_init_2(TYPE, VAR, TOML);
#define foreach_s_toml_init_1(		TYPE, VAR, TOML)	t_size VAR##_i = 0
#define foreach_s_toml_init_2(		TYPE, VAR, TOML)	s_toml* VAR = (TOML)
#define foreach_s_toml_exit(		TYPE, VAR, TOML)	if (TOML)
#define foreach_s_toml_loop_init(	TYPE, VAR, TOML)	VAR = (TOML != NULL) ? (TOML)->child : NULL
#define foreach_s_toml_loop_exit(	TYPE, VAR, TOML)	VAR != NULL
#define foreach_s_toml_loop_incr(	TYPE, VAR, TOML)	++VAR##_i, VAR = VAR->next
*/


/*
** ************************************************************************** *|
**                             Basic TOML Operations                          *|
** ************************************************************************** *|
*/

//! Allocated one single TOML struct
s_toml* TOML_New_Item(void);

//! Create a new `s_toml` object, parsed from a (valid) TOML string
/*!
**	Memory Management: the caller is always responsible to free the results,
**	from all variants of TOML_Parse() (by using TOML_Delete()) and TOML_Print()
**	(with stdlib free(), TOML_Hooks.free_fn(), or TOML_free() as appropriate).
**	The exception is TOML_PrintPreallocated(), where the caller has full responsibility of the buffer.
**	Supply a block of TOML, and this returns a `s_toml` object you can interrogate.
*/
s_toml*	TOML_FromString(t_char const* value);
#define TOML_Parse	TOML_FromString
#define TOML_Decode	TOML_FromString

//! Create a new `s_toml` object, parsed from a (valid) TOML string, (only the first `buffer_length` chars are parsed)
s_toml*	TOML_FromString_N(t_char const* value, t_size buffer_length);
#define TOML_Parse_N	TOML_FromString_N
#define TOML_Decode_N	TOML_FromString_N

//! Create a new `s_toml` object, parsed from a (valid) TOML string
/*!
**	TOML_ParseStrict() allows you to require (and check) that the TOML is null terminated,
**	and to retrieve the pointer to the final byte parsed.
**	If you supply a ptr in return_parse_end and parsing fails, then `return_parse_end`
**	will contain a pointer to the error, such that it will match the return of TOML_GetErrorPtr().
*/
s_toml*	TOML_FromString_Strict(t_char const* value, t_char const* *return_parse_end, t_bool require_null_terminated);
#define TOML_Parse_Strict	TOML_FromString_Strict
#define TOML_Decode_Strict	TOML_FromString_Strict

//! Create a new `s_toml` object, parsed from a (valid) TOML string, (only the first `buffer_length` chars are parsed)
s_toml*	TOML_FromString_Strict_N(t_char const* value, t_size buffer_length, t_char const* *return_parse_end, t_bool require_null_terminated);
#define TOML_Parse_Strict_N 	TOML_FromString_Strict_N
#define TOML_Decode_Strict_N	TOML_FromString_Strict_N



#define TOML_ToString	TOML_ToString_Pretty
#define TOML_Print		TOML_ToString_Pretty
//! Render a s_toml entity to text for transfer/storage (with 'pretty' formatting).
t_char*	TOML_ToString_Pretty(s_toml const* item);
#define TOML_Print_Pretty	TOML_ToString_Pretty
//! Render a s_toml entity to text for transfer/storage, without any formatting/whitespace
t_char*	TOML_ToString_Minify(s_toml const* item);
#define TOML_Print_Minify	TOML_ToString_Minify
//! Render a s_toml entity to text using a buffered strategy.
/*!
**	prebuffer is a guess at the final size. guessing well reduces reallocation. fmt=0 gives unformatted, =1 gives formatted.
*/
t_char*	TOML_ToString_Buffered(s_toml const* item, t_sint prebuffer, t_bool fmt);
#define TOML_Print_Buffered	TOML_ToString_Buffered
//! Render a `s_toml` entity to text using a buffer already allocated in memory with given length.
/*!
**	@returns 1(TRUE) on success and 0(FALSE) on failure.
**	NOTE: s_toml is not always 100% accurate in estimating how much memory it will use, so to be safe allocate 5 bytes more than you actually need.
*/
t_bool	TOML_ToString_Preallocated(s_toml* item, t_char* buffer, t_sint const length, t_bool const format);
#define TOML_Print_Preallocated	TOML_ToString_Preallocated



//! Returns the amount of items in an array (or object).
t_sint	TOML_GetArrayLength(s_toml const* array);

//! Retrieve item number "index" from array "array". Returns NULL if unsuccessful.
s_toml*	TOML_GetArrayItem(s_toml const* array, t_sint index);

//! Get the item with the given `key` from the given `object` (case-insensitive).
s_toml*	TOML_GetObjectItem				(s_toml const* const object, t_char const* const key);
//! Get the item with the given `key` from the given `object` (case-sensitive).
s_toml*	TOML_GetObjectItem_CaseSensitive(s_toml const* const object, t_char const* const key);

t_bool	TOML_HasObjectItem(s_toml const* object, t_char const* key);



//! Access the contents of a TOML with a 'TOML path', ie: a format string of 'accessors' (ie: strings or numbers in brackets)
/*!
**	@param	object		The TOML object to get an item from
**	@param	format_path	The format string with an accessor pattern (example: `TOML_Get(toml, "[\"subarray\"][3][\"name\"]")`)
**	@param	...			The variadic arguments list which goes along with `format_path` (works like printf)
**	@returns the TOML object gotten from the given accessor path, or NULL if the path or TOML was invalid.
*/
s_toml*	TOML_Get(s_toml const* object, t_char const* format_path, ...)
_FORMAT(printf, 2, 3);

//! Returns the number value contained within the given `item`, or `NAN` if type is not #TOML_TYPE_NUMBER.
t_f64	TOML_GetValue_Number(s_toml const* const item);
//! Returns the string value contained within the given `item`, or `NULL` if type is not #TOML_TYPE_STRING.
t_char*	TOML_GetValue_String(s_toml const* const item);



//! Change the `value_number` of a TOML_TYPE_STRING object, only takes effect when type of object is TOML_TYPE_STRING.
t_f64	TOML_SetValue_Number(s_toml* object, t_f64 value);
//! Change the `value_string` of a TOML_TYPE_STRING object, only takes effect when type of object is TOML_TYPE_STRING.
t_char*	TOML_SetValue_String(s_toml* object, t_char* value);



//! These functions check the type of an item.
//!@{
t_bool	TOML_IsInvalid	(s_toml const* const item);
t_bool	TOML_IsNull		(s_toml const* const item);
t_bool	TOML_IsFalse	(s_toml const* const item);
t_bool	TOML_IsTrue		(s_toml const* const item);
t_bool	TOML_IsBool		(s_toml const* const item);
t_bool	TOML_IsNumber	(s_toml const* const item);
t_bool	TOML_IsString	(s_toml const* const item);
t_bool	TOML_IsArray	(s_toml const* const item);
t_bool	TOML_IsObject	(s_toml const* const item);
t_bool	TOML_IsRaw		(s_toml const* const item);
//!@}



//! These calls create a s_toml item of the appropriate type.
//!@{
s_toml*	TOML_CreateNull(void);
s_toml*	TOML_CreateTrue(void);
s_toml*	TOML_CreateFalse(void);
s_toml*	TOML_CreateBool(t_bool boolean);
s_toml*	TOML_CreateNumber(t_f64 num);
s_toml*	TOML_CreateString(t_char const* string);
s_toml*	TOML_CreateRaw(t_char const* raw);
s_toml*	TOML_CreateArray(void);
s_toml*	TOML_CreateObject(void);
//!@}

//! Create a string where `value_string` references a string, so it will not be freed by TOML_Delete()
s_toml*	TOML_CreateStringReference(t_char const* string);
//! Create an array that only references it's elements, so they will not be freed by TOML_Delete()
s_toml*	TOML_CreateArrayReference(s_toml const* child);
//! Create an object that only references it's elements, so they will not be freed by TOML_Delete()
s_toml*	TOML_CreateObjectReference(s_toml const* child);

//! Create and fill a TOML array
/*!
**	These utilities create a TOML array of `count` items.
**	The given `count` cannot be greater than the number of elements in
**	the given `numbers` array, otherwise array access will be out of bounds.
*/
//!@{
s_toml*	TOML_CreateIntArray		(t_sint const* numbers, t_sint count);
s_toml*	TOML_CreateFloatArray	(t_f32 const* numbers, t_sint count);
s_toml*	TOML_CreateDoubleArray	(t_f64 const* numbers, t_sint count);
s_toml*	TOML_CreateStringArray	(t_char const* const *strings, t_sint count);
//!@}



//! Appends the given `item` to the given `array`.
t_bool	TOML_AddToArray_Item(s_toml* array, s_toml* item);

//! Append a reference to `item` to the given `array`.
t_bool	TOML_AddToArray_ItemReference(s_toml* array, s_toml* item);

//! Appends the given `item` to the given `object`, with the given `key`.
t_bool	TOML_AddToObject_Item(s_toml* object, t_char const* key, s_toml* item);

//! Append reference to item to the given object.
t_bool	TOML_AddToObject_ItemReference(s_toml* object, t_char const* key, s_toml* item);

//! Appends the given `item` to an object with constant string as key
/*!
**	Use this when string is definitely const (i.e. a literal, or as good as), and will definitely survive the TOML object.
**	NOTE: When this function was used, make sure to always perform the following check:
**	`(item->type & TOML_TYPE_CONSTSTRING) == 0` before writing to `item->string`.
*/
t_bool	TOML_AddToObject_ItemCS(s_toml* object, t_char const* key, s_toml* item);

/*!
**	Helper functions for creating and adding items to an object at the same time.
**	They return the added item or NULL on failure.
*/
//!@{
s_toml*	TOML_AddToObject_Null	(s_toml* const object, t_char const* key);
s_toml*	TOML_AddToObject_True	(s_toml* const object, t_char const* key);
s_toml*	TOML_AddToObject_False	(s_toml* const object, t_char const* key);
s_toml*	TOML_AddToObject_Bool	(s_toml* const object, t_char const* key, t_bool boolean);
s_toml*	TOML_AddToObject_Number	(s_toml* const object, t_char const* key, t_f64 number);
s_toml*	TOML_AddToObject_String	(s_toml* const object, t_char const* key, t_char const* string);
s_toml*	TOML_AddToObject_Raw	(s_toml* const object, t_char const* key, t_char const* raw);
s_toml*	TOML_AddToObject_Object	(s_toml* const object, t_char const* key);
s_toml*	TOML_AddToObject_Array	(s_toml* const object, t_char const* key);
//!@}



//! Shifts pre-existing items to the right.
t_bool	TOML_InsertItemInArray(s_toml* array, t_sint index, s_toml* newitem);



//! Delete a s_toml entity and all subentities.
void	TOML_Delete(s_toml* item);

//! Deletes the item at the given `index` from the given `array`.
void	TOML_DeleteItemFromArray				(s_toml* array, t_sint index);
//! Deletes the item with the given `key` from the given `object`.
void	TOML_DeleteItemFromObject				(s_toml* object, t_char const* key);
void	TOML_DeleteItemFromObject_CaseSensitive	(s_toml* object, t_char const* key);



//! Removes (without deleting) the given `item` from the given `parent` object.
s_toml*	TOML_DetachItem(s_toml* parent, s_toml* const item);
//! Removes (without deleting) the given `item` from the given `array`.
s_toml*	TOML_DetachItemFromArray				(s_toml* array, t_sint index);
//! Removes (without deleting) the given `item` from the given `object`.
s_toml*	TOML_DetachItemFromObject				(s_toml* object, t_char const* key);
s_toml*	TOML_DetachItemFromObject_CaseSensitive	(s_toml* object, t_char const* key);


//! Replaces the given `item` from the given `parent` object, with the given `newitem`.
t_bool	TOML_ReplaceItem(s_toml* parent, s_toml* item, s_toml* newitem);
//! Replaces the given `item` from the given `array`, with the given `newitem`.
t_bool	TOML_ReplaceItemInArray					(s_toml* array, t_sint index, s_toml* newitem);
//! Replaces the given `item` from the given `object`, with the given `newitem` (case-insensitive).
t_bool	TOML_ReplaceItemInObject				(s_toml* object, t_char const* key, s_toml* newitem);
//! Replaces the given `item` from the given `object`, with the given `newitem` (case-sensitive).
t_bool	TOML_ReplaceItemInObject_CaseSensitive	(s_toml* object, t_char const* key, s_toml* newitem);



//! Duplicates a TOML object.
/*!
**	Duplicate will create a new, identical s_toml item to the one you pass, in new memory that will
**	need to be released. With `recurse != FALSE`, it will duplicate any children connected to the item.
**	The item->next and ->prev pointers are always zero on return from Duplicate.
*/
s_toml*	TOML_Duplicate(s_toml const* item, t_bool recurse);



//! Recursively compare two s_toml items for equality.
/*!
**	If either a or b is NULL or invalid, they will be considered unequal.
**	case_sensitive determines if object keys are treated case sensitive (1) or case insensitive (0).
*/
t_bool	TOML_Equals(s_toml const* a, s_toml const* b, t_bool const case_sensitive);



//! Creates a new TOML object by concatenating two existing ones
s_toml*	TOML_Concat(s_toml const* a, s_toml const* b);



//! Minify a TOML string, to make it more lightweight: removes all whitespace characters
/*!
**	Minify a TOML, removing blank characters (such as ' ', '\t', '\r', '\n') from strings.
**	The input pointer toml cannot point to a read-only address area, such as a string constant, 
**	but should point to a readable and writable address area.
*/
void	TOML_Minify(t_char* toml); //!< TODO rename to TOML_Minify_InPlace(), and add TOML_Minify(), which would allocate



//! The "get error" function, to be used after getting an unsatisfactory result return
/*!
**	This function can be used for analysing failed parses.
**	This returns a pointer to the parse error location in the given TOML string.
**	You'll probably need to look a few chars back to make sense of it.
**	Defined when TOML_Parse() returns 0.
**	Otherwise, NULL when TOML_Parse() succeeds.
*/
t_char const*	TOML_GetErrorPtr(void);



/*! @} */
HEADER_END
#endif
