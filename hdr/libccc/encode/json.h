/*============================================================================*\
||                                            ______________________________  ||
||  libccc/encode/json.h                     |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_ENCODE_JSON_H
#define __LIBCCC_ENCODE_JSON_H
/*!@group{libccc_encode_json,41,libccc/encode/json.h}
**
**	This header defines a dynamic runtime object type, similar to objects in JS.
**	- JSON spec: https://www.json.org/json-en.html
**
**	In particular, much of the code in this header was inspired by cJSON:
**	- https://github.com/DaveGamble/cJSON
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/encode/common.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//! Like other libccc/encode/ types, JSON is simply an alias for the KVT type
typedef s_kvt	s_json;



#define foreach_s_json(_TYPE_, _VAR_, _JSON_)		foreach (_TYPE_, _VAR_, s_json, _JSON_)

#define foreach_s_json_init			foreach_s_kvt_init
#define foreach_s_json_exit			foreach_s_kvt_exit
#define foreach_s_json_loop_init	foreach_s_kvt_loop_init
#define foreach_s_json_loop_exit	foreach_s_kvt_loop_exit
#define foreach_s_json_loop_incr	foreach_s_kvt_loop_incr
#define foreach_s_json_loop_setv	foreach_s_kvt_loop_setv



/*============================================================================*\
||                            JSON Parsing Operations                         ||
\*============================================================================*/

//!@doc Macros which configure the default behavior of the JSON parsing functions (`Strict` or `Lenient`)
//!@{
#define 				JSON_Parse		JSON_Parse_Lenient
#define c_jsonparse		JSON_Parse

#define 				JSON_Parse_N	JSON_Parse_Lenient_N
#define c_jsonnparse	JSON_Parse_N

#define 				JSON_FromString	JSON_FromString_Lenient
#define c_strtojson		JSON_FromString
//!@}



//! Create a new `s_json` object, parsed from a (valid) JSON string
/*!
**	This function creates a `s_json` object by parsing a JSON string,
**	allowing for several extensions to the JSON official spec, notably:
**	- allows for trailing commas at the end of arrays or objects
**	- allows for leading `+` symbols for positive-sign number literals
**	- allows for `null`/`true`/`false` to be written in uppercase, or mixed-case rather than only lowercase
**	- allows for non-standard whitespace characters: anything for which `isspace()` returns `TRUE`
**	- allows for non-standard string escape sequences, matching those used in C: `\x??` for bytes, `\e`, for escape, etc
**	- supports comments (using either `/``*`,`*``/` block syntax, or `//` single-line)
**	- supports non-standard `number` values: `nan`/NaN and `inf`/infinity
**	- supports numeric literals in other bases: prefix with `0x` for hexadecimal, `0b` for binary, `0o` for octal
**	- supports `BigInt` integers, using the trailing `n` syntax
*/
//!@{

/*!
**	@param	dest	The resulting JSON object
**	@param	str		The string to parse
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
**
**	@see JSON_FromString_Lenient()
*/
//!@{
t_size					JSON_Parse_Lenient(s_json* *dest, t_utf8 const* str, t_size n);
#define c_jsonparse_l	JSON_Parse_Lenient
//!@}

//!@doc @see JSON_Parse_Lenient()
//!@{
s_json*					JSON_FromString_Lenient(t_utf8 const* str);
#define c_strtojson_l	JSON_FromString_Lenient
//!@}

//!@}




//! Create a new `s_json` object, parsed from a (valid) JSON string
/*!
**	This function creates a `s_json` object by parsing a JSON string,
**	strictly following the JSON official spec (https://www.json.org/json-en.html),
**	aborting with an error if anything non-standard is encountered.
*/
//!@{

/*!
**	@param	dest	The resulting JSON object
**	@param	str		The string to parse
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
**
**	@see JSON_FromString_Strict()
*/
//!@{
t_size					JSON_Parse_Strict(s_json* *dest, t_utf8 const* str, t_size n);
#define c_jsonparse_s	JSON_Parse_Strict
//!@}

//!@doc @see JSON_Parse_Strict()
//!@{
s_json*					JSON_FromString_Strict(t_utf8 const* str);
#define c_strtojson_s	JSON_FromString_Strict
//!@}

//!@}



/*============================================================================*\
||                           JSON Printing Operations                         ||
\*============================================================================*/

//!@doc Macros which configure the default behavior of the JSON_Print() function (`Pretty` or `Minify`)
//!@{
#define 				JSON_Print	JSON_Print_Pretty
#define c_jsonprint		JSON_Print

#define 				JSON_ToString	JSON_ToString_Pretty
#define c_jsontostr		JSON_ToString
//!@}



//!@doc Print a `s_json` item to string buffer `dest`, writing at most `n` characters.
/*!
**	@param	dest	The pre-allocated string buffer to write to
**	@param	item	The JSON object to print
**	@param	n		The maximum amount of chars to write into `dest`
**	@returns
**	The amount of characters written to the given `dest` buffer
*/
//!@{
t_size					JSON_Print_Pretty(t_utf8* dest, s_json const* item, t_size n);
#define c_jsonprintfmt 	JSON_Print_Pretty
//!@}

//!@doc Get a new string from the given JSON `item`, with readable formatting.
//!@{
t_utf8*					JSON_ToString_Pretty(s_json const* item);
#define c_jsontostrfmt	JSON_ToString_Pretty
//!@}



//!@doc Like JSON_Print_Pretty(), but this prints the minimum amount of characters possible
//!@{
t_size					JSON_Print_Minify(t_utf8* dest, s_json const* item, t_size n);
#define c_jsonprintmin	JSON_Print_Minify
//!@}

//!@doc Get a new string from the given JSON `item`, without any formatting/whitespace.
//!@{
t_utf8*					JSON_ToString_Minify(s_json const* item);
#define c_jsontostrmin	JSON_ToString_Minify
//!@}

// TODO alternate versions which can print BigInt numbers and comments ?



#if 0
//!@doc Render a s_json entity to text using a buffered strategy.
/*!
**	prebuffer is a guess at the final size. guessing well reduces reallocation. `format = 0` means minified, `format = 1` means formatted/pretty.
*/
//!@{
t_utf8*					JSON_Print_Buffered(s_json const* item, t_sint prebuffer, t_bool format);
#define c_jsonprintbuf 	JSON_Print_Buffered
//!@}
#endif



/*============================================================================*\
||                             JSON String Operations                         ||
\*============================================================================*/

//!@doc Minify a JSON string, to make it more lightweight: removes all whitespace characters
/*!
**	Minify a JSON, removing blank characters (such as ' ', '\t', '\r', '\n') from strings.
**	The input pointer json cannot point to a read-only address area, such as a string constant, 
**	but should point to a readable and writable address area.
*/
//!@{
void				JSON_Minify(t_utf8* json); //!< TODO rename to JSON_Minify_InPlace(), and add JSON_Minify(), which would allocate
#define c_jsonmin	JSON_Minify
//!@}



// TODO JSON_ToValid()



/*============================================================================*\
||                             Basic JSON Operations                          ||
\*============================================================================*/

#define JSON_Item		KVT_Item		//!< @alias{KVT_Item}

#define JSON_Duplicate	KVT_Duplicate	//!< @alias{KVT_Duplicate}

#define JSON_Equals		KVT_Equals		//!< @alias{KVT_Equals}

#define JSON_Concat			KVT_Concat			//!< @alias{KVT_Concat}
#define JSON_Concat_Array	KVT_Concat_Array	//!< @alias{KVT_Concat_Array}
#define JSON_Concat_Object	KVT_Concat_Object	//!< @alias{KVT_Concat_Object}



/*============================================================================*\
||                            JSON "create" Operations                        ||
\*============================================================================*/

#define JSON_CreateNull		KVT_CreateNull		//!< @alias{KVT_CreateNull}
#define JSON_CreateBoolean	KVT_CreateBoolean	//!< @alias{KVT_CreateBoolean}
#define JSON_CreateInteger	KVT_CreateInteger	//!< @alias{KVT_CreateInteger}
#define JSON_CreateFloat	KVT_CreateFloat		//!< @alias{KVT_CreateFloat}
#define JSON_CreateString	KVT_CreateString	//!< @alias{KVT_CreateString}
#define JSON_CreateArray	KVT_CreateArray		//!< @alias{KVT_CreateArray}
#define JSON_CreateObject	KVT_CreateObject	//!< @alias{KVT_CreateObject}
#define JSON_CreateRaw		KVT_CreateRaw		//!< @alias{KVT_CreateRaw}



#define JSON_CreateArrayReference	KVT_CreateArrayReference	//!< @alias{KVT_CreateArrayReference}
#define JSON_CreateObjectReference	KVT_CreateObjectReference	//!< @alias{KVT_CreateObjectReference}
#define JSON_CreateStringReference	KVT_CreateStringReference	//!< @alias{KVT_CreateStringReference}



#define JSON_CreateArray_Boolean	KVT_CreateArray_Boolean	//!< @alias{KVT_CreateArray_Boolean}
#define JSON_CreateArray_UInt		KVT_CreateArray_UInt	//!< @alias{KVT_CreateArray_UInt}
#define JSON_CreateArray_U8			KVT_CreateArray_U8		//!< @alias{KVT_CreateArray_U8}
#define JSON_CreateArray_U16		KVT_CreateArray_U16		//!< @alias{KVT_CreateArray_U16}
#define JSON_CreateArray_U32		KVT_CreateArray_U32		//!< @alias{KVT_CreateArray_U32}
#define JSON_CreateArray_U64		KVT_CreateArray_U64		//!< @alias{KVT_CreateArray_U64}
#define JSON_CreateArray_U128		KVT_CreateArray_U128	//!< @alias{KVT_CreateArray_U128}
#define JSON_CreateArray_SInt		KVT_CreateArray_SInt	//!< @alias{KVT_CreateArray_SInt}
#define JSON_CreateArray_S8			KVT_CreateArray_S8		//!< @alias{KVT_CreateArray_S8}
#define JSON_CreateArray_S16		KVT_CreateArray_S16		//!< @alias{KVT_CreateArray_S16}
#define JSON_CreateArray_S32		KVT_CreateArray_S32		//!< @alias{KVT_CreateArray_S32}
#define JSON_CreateArray_S64		KVT_CreateArray_S64		//!< @alias{KVT_CreateArray_S64}
#define JSON_CreateArray_S128		KVT_CreateArray_S128	//!< @alias{KVT_CreateArray_S128}
#define JSON_CreateArray_Float		KVT_CreateArray_Float	//!< @alias{KVT_CreateArray_Float}
#define JSON_CreateArray_F32		KVT_CreateArray_F32		//!< @alias{KVT_CreateArray_F32}
#define JSON_CreateArray_F64		KVT_CreateArray_F64		//!< @alias{KVT_CreateArray_F64}
#define JSON_CreateArray_F80		KVT_CreateArray_F80		//!< @alias{KVT_CreateArray_F80}
#define JSON_CreateArray_F128		KVT_CreateArray_F128	//!< @alias{KVT_CreateArray_F128}
#define JSON_CreateArray_String		KVT_CreateArray_String	//!< @alias{KVT_CreateArray_String}



/*============================================================================*\
||                             JSON "get" Operations                          ||
\*============================================================================*/

#define JSON_GetArrayLength		KVT_GetArrayLength	//!< @alias{KVT_GetArrayLength}

#define JSON_GetArrayItem		KVT_GetArrayItem	//!< @alias{KVT_GetArrayItem}



#define JSON_GetObjectItem \
		JSON_GetObjectItem_CaseSensitive
#define JSON_GetObjectItem_CaseSensitive	KVT_GetObjectItem_CaseSensitive	//!< @alias{KVT_GetObjectItem_CaseSensitive}
#define JSON_GetObjectItem_IgnoreCase		KVT_GetObjectItem_IgnoreCase	//!< @alias{KVT_GetObjectItem_IgnoreCase}



#define JSON_HasObjectItem \
		JSON_HasObjectItem_CaseSensitive
#define JSON_HasObjectItem_CaseSensitive	KVT_HasObjectItem_CaseSensitive	//!< @alias{KVT_HasObjectItem_CaseSensitive}
#define JSON_HasObjectItem_IgnoreCase		KVT_HasObjectItem_IgnoreCase	//!< @alias{KVT_HasObjectItem_IgnoreCase}



#define JSON_Get				KVT_Get	//!< @alias{KVT_Get}

#define JSON_GetValue_Boolean 	KVT_GetValue_Boolean	//!< @alias{KVT_GetValue_Boolean}
#define JSON_GetValue_Integer 	KVT_GetValue_Integer	//!< @alias{KVT_GetValue_Integer}
#define JSON_GetValue_Float 	KVT_GetValue_Float		//!< @alias{KVT_GetValue_Float}
#define JSON_GetValue_String 	KVT_GetValue_String		//!< @alias{KVT_GetValue_String}



/*============================================================================*\
||                             JSON "set" Operations                          ||
\*============================================================================*/

#define JSON_SetValue_Boolean 	KVT_SetValue_Boolean	//!< @alias{KVT_SetValue_Boolean}
#define JSON_SetValue_Integer 	KVT_SetValue_Integer	//!< @alias{KVT_SetValue_Integer}
#define JSON_SetValue_Float 	KVT_SetValue_Float		//!< @alias{KVT_SetValue_Float}
#define JSON_SetValue_String 	KVT_SetValue_String		//!< @alias{KVT_SetValue_String}



#define JSON_AddToArray_Item			KVT_AddToArray_Item				//!< @alias{KVT_AddToArray_Item}
#define JSON_AddToArray_ItemReference	KVT_AddToArray_ItemReference	//!< @alias{KVT_AddToArray_ItemReference}

#define JSON_AddToObject_Item			KVT_AddToObject_Item			//!< @alias{KVT_AddToObject_Item}
#define JSON_AddToObject_ItemReference	KVT_AddToObject_ItemReference	//!< @alias{KVT_AddToObject_ItemReference}



#define JSON_AddToObject_Null		KVT_AddToObject_Null	//!< @alias{KVT_AddToObject_Null}
#define JSON_AddToObject_Boolean	KVT_AddToObject_Boolean	//!< @alias{KVT_AddToObject_Boolean}
#define JSON_AddToObject_Integer	KVT_AddToObject_Integer	//!< @alias{KVT_AddToObject_Integer}
#define JSON_AddToObject_Float		KVT_AddToObject_Float	//!< @alias{KVT_AddToObject_Float}
#define JSON_AddToObject_String		KVT_AddToObject_String	//!< @alias{KVT_AddToObject_String}
#define JSON_AddToObject_Object		KVT_AddToObject_Object	//!< @alias{KVT_AddToObject_Object}
#define JSON_AddToObject_Array		KVT_AddToObject_Array	//!< @alias{KVT_AddToObject_Array}
#define JSON_AddToObject_Raw		KVT_AddToObject_Raw		//!< @alias{KVT_AddToObject_Raw}



/*============================================================================*\
||                             JSON Check Operations                          ||
\*============================================================================*/

#define JSON_IsInvalid	KVT_IsInvalid	//!< @alias{KVT_IsInvalid}
#define JSON_IsNull		KVT_IsNull		//!< @alias{KVT_IsNull}
#define JSON_IsBoolean	KVT_IsBoolean	//!< @alias{KVT_IsBoolean}
#define JSON_IsInteger	KVT_IsInteger	//!< @alias{KVT_IsInteger}
#define JSON_IsFloat	KVT_IsFloat		//!< @alias{KVT_IsFloat}
#define JSON_IsString	KVT_IsString	//!< @alias{KVT_IsString}
#define JSON_IsArray	KVT_IsArray		//!< @alias{KVT_IsArray}
#define JSON_IsObject	KVT_IsObject	//!< @alias{KVT_IsObject}
#define JSON_IsRaw		KVT_IsRaw		//!< @alias{KVT_IsRaw}



/*============================================================================*\
||                             JSON Other Operations                          ||
\*============================================================================*/

#define JSON_Delete 	KVT_Delete	//!< @alias{KVT_Delete}

#define JSON_Detach 	KVT_Detach	//!< @alias{KVT_Detach}

#define JSON_Replace 	KVT_Replace	//!< @alias{KVT_Replace}



#define JSON_Delete_FromArray 	KVT_Delete_FromArray	//!< @alias{KVT_Delete_FromArray}

#define JSON_Detach_FromArray 	KVT_Detach_FromArray	//!< @alias{KVT_Detach_FromArray}

#define JSON_Replace_InArray 	KVT_Replace_InArray		//!< @alias{KVT_Replace_InArray}

#define JSON_Insert_InArray 	KVT_Insert_InArray		//!< @alias{KVT_Insert_InArray}



#define JSON_Delete_FromObject \
		JSON_Delete_FromObject_CaseSensitive
#define JSON_Delete_FromObject_CaseSensitive	KVT_Delete_FromObject_CaseSensitive	//!< @alias{KVT_Delete_FromObject_CaseSensitive}
#define JSON_Delete_FromObject_IgnoreCase		KVT_Delete_FromObject_IgnoreCase	//!< @alias{KVT_Delete_FromObject_IgnoreCase}

#define JSON_Detach_FromObject \
		JSON_Detach_FromObject_CaseSensitive
#define JSON_Detach_FromObject_CaseSensitive	KVT_Detach_FromObject_CaseSensitive	//!< @alias{KVT_Detach_FromObject_CaseSensitive}
#define JSON_Detach_FromObject_IgnoreCase		KVT_Detach_FromObject_IgnoreCase	//!< @alias{KVT_Detach_FromObject_IgnoreCase}

#define JSON_Replace_InObject \
		JSON_Replace_InObject_CaseSensitive
#define JSON_Replace_InObject_CaseSensitive		KVT_Replace_InObject_CaseSensitive	//!< @alias{KVT_Replace_InObject_CaseSensitive}
#define JSON_Replace_InObject_IgnoreCase		KVT_Replace_InObject_IgnoreCase		//!< @alias{KVT_Replace_InObject_IgnoreCase}



#define TOML_Merge	KVT_Merge	//!< @alias{KVT_Merge}



/*! @endgroup */
HEADER_END
#endif
