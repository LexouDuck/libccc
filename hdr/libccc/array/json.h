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

#define JSON_Invalid	(t_json_type)(0)
#define JSON_False	(t_json_type)(1 << 0)
#define JSON_True	(t_json_type)(1 << 1)
#define JSON_NULL	(t_json_type)(1 << 2)
#define JSON_Number	(t_json_type)(1 << 3)
#define JSON_String	(t_json_type)(1 << 4)
#define JSON_Array	(t_json_type)(1 << 5)
#define JSON_Object	(t_json_type)(1 << 6)
#define JSON_Raw	(t_json_type)(1 << 7) // raw json

#define JSON_IsReference	(t_json_type)(1 << 8)
#define JSON_StringIsConst	(t_json_type)(1 << 9)



/*!
**	The s_json structure: nest-able, list-able, etc
*/
typedef struct	s_json
{
	struct s_json*	next;	//!< linked-list pointers to neighboring items
	struct s_json*	prev;	//!< linked-list pointers to neighboring items

	struct s_json*	child;	//!< An array or object item will have a child pointer pointing to a chain of the items in the array/object.

	t_json_type	type;		//!< The type of the item, as above.

	t_char*		string;		//!< The item's name string, if this item is the child of, or is in the list of subitems of an object.

	t_char*		value_string;//!< The item's string, if type==JSON_String  and type == JSON_Raw
	t_f64		value_double;//!< The item's number, if type==JSON_Number
}				s_json;

/*!
**	Limits how deeply nested arrays/objects can be before s_json rejects to parse them.
**	This is to prevent stack overflows.
*/
#ifndef JSON_NESTING_LIMIT
#define JSON_NESTING_LIMIT 1000
#endif



#define foreach_s_json_init(		TYPE, VAR, JSON)	foreach_s_json_init_1(TYPE, VAR, JSON); foreach_s_json_init_2(TYPE, VAR, JSON);
#define foreach_s_json_init_1(		TYPE, VAR, JSON)	t_size VAR##_i = 0
#define foreach_s_json_init_2(		TYPE, VAR, JSON)	s_json* VAR = (JSON)
#define foreach_s_json_exit(		TYPE, VAR, JSON)	if (JSON)
#define foreach_s_json_loop_init(	TYPE, VAR, JSON)	VAR = (JSON != NULL) ? (JSON)->child : NULL
#define foreach_s_json_loop_exit(	TYPE, VAR, JSON)	VAR != NULL
#define foreach_s_json_loop_incr(	TYPE, VAR, JSON)	++VAR##_i, VAR = VAR->next



/*
** ************************************************************************** *|
**                             Basic JSON Operations                          *|
** ************************************************************************** *|
*/

/* Memory Management: the caller is always responsible to free the results from all variants of JSON_Parse (with JSON_Delete) and JSON_Print (with stdlib free, JSON_Hooks.free_fn, or JSON_free as appropriate). The exception is JSON_PrintPreallocated, where the caller has full responsibility of the buffer. */
/* Supply a block of JSON, and this returns a s_json object you can interrogate. */
s_json*	JSON_Parse(const t_char* value);
s_json*	JSON_ParseWithLength(const t_char* value, t_size buffer_length);
/* ParseWithOpts allows you to require (and check) that the JSON is null terminated, and to retrieve the pointer to the final byte parsed. */
/* If you supply a ptr in return_parse_end and parsing fails, then return_parse_end will contain a pointer to the error so will match JSON_GetErrorPtr(). */
s_json*	JSON_ParseWithOpts(const t_char* value, const t_char* *return_parse_end, t_bool require_null_terminated);
s_json*	JSON_ParseWithLengthOpts(const t_char* value, t_size buffer_length, const t_char* *return_parse_end, t_bool require_null_terminated);

/* Render a s_json entity to text for transfer/storage. */
t_char*	JSON_Print(const s_json* item);
/* Render a s_json entity to text for transfer/storage without any formatting. */
t_char*	JSON_PrintUnformatted(const s_json* item);
/* Render a s_json entity to text using a buffered strategy. prebuffer is a guess at the final size. guessing well reduces reallocation. fmt=0 gives unformatted, =1 gives formatted */
t_char*	JSON_PrintBuffered(const s_json* item, t_sint prebuffer, t_bool fmt);
/* Render a s_json entity to text using a buffer already allocated in memory with given length. Returns 1 on success and 0 on failure. */
/* NOTE: s_json is not always 100% accurate in estimating how much memory it will use, so to be safe allocate 5 bytes more than you actually need */
t_bool	JSON_PrintPreallocated(s_json* item, t_char* buffer, const t_sint length, const t_bool format);
/* Delete a s_json entity and all subentities. */
void	JSON_Delete(s_json* item);

/* Returns the number of items in an array (or object). */
t_sint	JSON_GetArraySize(const s_json* array);
/* Retrieve item number "index" from array "array". Returns NULL if unsuccessful. */
s_json*	JSON_GetArrayItem(const s_json* array, t_sint index);
/* Get item "string" from object. Case insensitive. */
s_json*	JSON_GetObjectItem(const s_json* const object, const t_char* const string);
s_json*	JSON_GetObjectItemCaseSensitive(const s_json* const object, const t_char* const string);
t_bool	JSON_HasObjectItem(const s_json* object, const t_char* string);
/* For analysing failed parses. This returns a pointer to the parse error. You'll probably need to look a few chars back to make sense of it. Defined when JSON_Parse() returns 0. 0 when JSON_Parse() succeeds. */
const t_char*	JSON_GetErrorPtr(void);

/* Check item type and return its value */
t_char*	JSON_GetStringValue(const s_json* const item);
t_f64	JSON_GetNumberValue(const s_json* const item);

/* These functions check the type of an item */
t_bool	JSON_IsInvalid	(const s_json* const item);
t_bool	JSON_IsFalse	(const s_json* const item);
t_bool	JSON_IsTrue		(const s_json* const item);
t_bool	JSON_IsBool		(const s_json* const item);
t_bool	JSON_IsNull		(const s_json* const item);
t_bool	JSON_IsNumber	(const s_json* const item);
t_bool	JSON_IsString	(const s_json* const item);
t_bool	JSON_IsArray	(const s_json* const item);
t_bool	JSON_IsObject	(const s_json* const item);
t_bool	JSON_IsRaw		(const s_json* const item);

/* These calls create a s_json item of the appropriate type. */
s_json*	JSON_CreateNull(void);
s_json*	JSON_CreateTrue(void);
s_json*	JSON_CreateFalse(void);
s_json*	JSON_CreateBool(t_bool boolean);
s_json*	JSON_CreateNumber(t_f64 num);
s_json*	JSON_CreateString(const t_char* string);
/* raw json */
s_json*	JSON_CreateRaw(const t_char* raw);
s_json*	JSON_CreateArray(void);
s_json*	JSON_CreateObject(void);

/* Create a string where valuestring references a string so
 * it will not be freed by JSON_Delete */
s_json*	JSON_CreateStringReference(const t_char* string);
/* Create an object/array that only references it's elements so
 * they will not be freed by JSON_Delete */
s_json*	JSON_CreateObjectReference(const s_json* child);
s_json*	JSON_CreateArrayReference(const s_json* child);

/* These utilities create an Array of count items.
 * The parameter count cannot be greater than the number of elements in the number array, otherwise array access will be out of bounds.*/
s_json*	JSON_CreateIntArray(const t_sint *numbers, t_sint count);
s_json*	JSON_CreateFloatArray(const t_f32 *numbers, t_sint count);
s_json*	JSON_CreateDoubleArray(const t_f64 *numbers, t_sint count);
s_json*	JSON_CreateStringArray(const t_char* const *strings, t_sint count);

/* Append item to the specified array/object. */
t_bool	JSON_AddItemToArray(s_json* array, s_json* item);
t_bool	JSON_AddItemToObject(s_json* object, const t_char* string, s_json* item);
/* Use this when string is definitely const (i.e. a literal, or as good as), and will definitely survive the s_json object.
 * WARNING: When this function was used, make sure to always check that (item->type & JSON_StringIsConst) is zero before
 * writing to `item->string` */
t_bool	JSON_AddItemToObjectCS(s_json* object, const t_char* string, s_json* item);
/* Append reference to item to the specified array/object. Use this when you want to add an existing s_json to a new s_json, but don't want to corrupt your existing s_json. */
t_bool	JSON_AddItemReferenceToArray(s_json* array, s_json* item);
t_bool	JSON_AddItemReferenceToObject(s_json* object, const t_char* string, s_json* item);

/* Remove/Detach items from Arrays/Objects. */
s_json*	JSON_DetachItemViaPointer(s_json* parent, s_json* const item);
s_json*	JSON_DetachItemFromArray(s_json* array, t_sint which);
void	JSON_DeleteItemFromArray(s_json* array, t_sint which);
s_json*	JSON_DetachItemFromObject(s_json* object, const t_char* string);
s_json*	JSON_DetachItemFromObjectCaseSensitive(s_json* object, const t_char* string);
void	JSON_DeleteItemFromObject(s_json* object, const t_char* string);
void	JSON_DeleteItemFromObjectCaseSensitive(s_json* object, const t_char* string);

/* Update array items. */
t_bool	JSON_InsertItemInArray(s_json* array, t_sint which, s_json* newitem); /* Shifts pre-existing items to the right. */
t_bool	JSON_ReplaceItemViaPointer(s_json* const parent, s_json* const item, s_json* replacement);
t_bool	JSON_ReplaceItemInArray(s_json* array, t_sint which, s_json* newitem);
t_bool	JSON_ReplaceItemInObject(s_json* object,const t_char* string,s_json* newitem);
t_bool	JSON_ReplaceItemInObjectCaseSensitive(s_json* object,const t_char* string,s_json* newitem);

/* Duplicate a s_json item */
s_json*	JSON_Duplicate(const s_json* item, t_bool recurse);
/* Duplicate will create a new, identical s_json item to the one you pass, in new memory that will
 * need to be released. With recurse!=0, it will duplicate any children connected to the item.
 * The item->next and ->prev pointers are always zero on return from Duplicate. */
/* Recursively compare two s_json items for equality. If either a or b is NULL or invalid, they will be considered unequal.
 * case_sensitive determines if object keys are treated case sensitive (1) or case insensitive (0) */
t_bool	JSON_Compare(const s_json* const a, const s_json* const b, const t_bool case_sensitive);

/* Minify a strings, remove blank characters(such as ' ', '\t', '\r', '\n') from strings.
 * The input pointer json cannot point to a read-only address area, such as a string constant, 
 * but should point to a readable and writable adress area. */
void	JSON_Minify(t_char* json);

/* Helper functions for creating and adding items to an object at the same time.
 * They return the added item or NULL on failure. */
s_json*	JSON_AddNullToObject(s_json* const object, const t_char* const name);
s_json*	JSON_AddTrueToObject(s_json* const object, const t_char* const name);
s_json*	JSON_AddFalseToObject(s_json* const object, const t_char* const name);
s_json*	JSON_AddBoolToObject(s_json* const object, const t_char* const name, const t_bool boolean);
s_json*	JSON_AddNumberToObject(s_json* const object, const t_char* const name, const t_f64 number);
s_json*	JSON_AddStringToObject(s_json* const object, const t_char* const name, const t_char* const string);
s_json*	JSON_AddRawToObject(s_json* const object, const t_char* const name, const t_char* const raw);
s_json*	JSON_AddObjectToObject(s_json* const object, const t_char* const name);
s_json*	JSON_AddArrayToObject(s_json* const object, const t_char* const name);



/* helper for the JSON_SetNumberValue macro */
t_f64	JSON_SetValue_Number(s_json* object, t_f64 number);
/* Change the valuestring of a JSON_String object, only takes effect when type of object is JSON_String */
t_char*	JSON_SetValue_String(s_json* object, const t_char* valuestring);



/*! @} */
HEADER_END
#endif
