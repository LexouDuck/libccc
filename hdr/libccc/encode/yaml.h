/*============================================================================*\
||                                            ______________________________  ||
||  libccc/encode/yaml.h                     |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_ENCODE_YAML_H
#define __LIBCCC_ENCODE_YAML_H
/*!@group{libccc_encode_yaml,43,libccc/encode/yaml.h}
**
**	This header defines a simple API to manipulate YAML files/strings.
**	- YAML spec: https://yaml.org/spec/1.2.2/
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/encode/common.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//! Like other libccc/encode/ types, YAML is just an alias for the KVT type
typedef s_kvt	s_yaml;



#define foreach_s_yaml(_TYPE_, _VAR_, _YAML_)		foreach (_TYPE_, _VAR_, s_yaml, _YAML_)

#define foreach_s_yaml_init			foreach_s_kvt_init
#define foreach_s_yaml_exit			foreach_s_kvt_exit
#define foreach_s_yaml_loop_init	foreach_s_kvt_loop_init
#define foreach_s_yaml_loop_exit	foreach_s_kvt_loop_exit
#define foreach_s_yaml_loop_incr	foreach_s_kvt_loop_incr
#define foreach_s_yaml_loop_setv	foreach_s_kvt_loop_setv



//! The amount of space characters used for each level of indentation (NOTE: the YAML spec forbids tab characters for indentation)
#define YAML_PRINTSTYLE_INDENT	2



/*============================================================================*\
||                            YAML Parsing Operations                         ||
\*============================================================================*/

//!@doc Macros which configure the default behavior of the YAML parsing functions (`Strict` or `Lenient`)
//!@{
#define 				YAML_Parse		YAML_Parse_Lenient
#define c_yamlparse		YAML_Parse

#define 				YAML_Parse_N	YAML_Parse_Lenient_N
#define c_yamlparsen	YAML_Parse_N

#define 				YAML_FromString	YAML_FromString_Lenient
#define c_strtoyaml		YAML_FromString
//!@}



//! Create a new `s_yaml` object, parsed from a (valid) YAML string
/*!
**	This function creates a `s_yaml` object by parsing a YAML string.
**	This API supports a large, pragmatic subset of the YAML 1.2 spec, notably:
**	- Block-style mappings (`key: value`), nested via indentation (space chars only)
**	- Block-style sequences (`- item`), including compact in-line notation (`- key: value`)
**	- Flow-style collections (`[a, b, c]` arrays and `{key: value}` objects, JSON-like)
**	- Plain (unquoted), single-quoted (verbatim), and double-quoted (escaped) scalar strings
**	- Block scalar strings: literal (`|`) and folded (`>`), with chomping indicators (`-`/`+`)
**	- Comments (starting with the `#` char, when not inside a quoted string)
**	- The YAML 1.2 "core schema" scalar types: `null`/`~`, `true`/`false`, integers
**		(decimal, or prefixed with `0x` for hexadecimal, `0o` for octal), and floats
**		(including the special values `.inf`, `-.inf` and `.nan`)
**	- Document start/end markers (`---` and `...`) and `%` directive lines (only one
**		document per string is supported: parsing stops at the end-of-document marker)
**	Additionally, when parsing in `Lenient` mode:
**	- YAML 1.1-style booleans are accepted (`yes`/`no`, `on`/`off`, `y`/`n`)
**	- Binary integer literals are accepted (prefixed with `0b`)
**	- Tab characters are tolerated within indentation (each tab counts as a single column)
**	- Non-standard special number values are accepted (`inf`/`nan` without the leading dot)
**	The following YAML features are NOT supported (a parsing error will be thrown):
**	- Anchors (`&anchor`), aliases (`*alias`), and tags (`!!type` or `!tag`)
**	- Complex mapping keys (`? key` explicit key notation, or collections used as keys)
**	- Multiple YAML documents within a single string/file (only the first one is parsed)
**	- Multi-line plain (unquoted) scalar strings (use quoted or block scalars instead)
*/
//!@{

//!@doc @see YAML_FromString_Lenient()
/*!
**	@param	dest	The resulting YAML object
**	@param	str		The string to parse
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`.
*/
//!@{
t_size					YAML_Parse_Lenient(s_yaml* *dest, t_utf8 const* str, t_size n);
#define c_yamlparse_l	YAML_Parse_Lenient
//!@}

//!@doc @see YAML_Parse_Lenient()
//!@{
s_yaml*					YAML_FromString_Lenient(t_utf8 const* str);
#define c_strtoyaml_l	YAML_FromString_Lenient
//!@}

//!@}



//! Create a new `s_yaml` object, parsed from a (valid) YAML string
/*!
**	This function creates a `s_yaml` object by parsing a YAML string,
**	strictly following the YAML official spec (https://yaml.org/spec/1.2.2/),
**	limited to the "core schema" (https://yaml.org/spec/1.2.2/#103-core-schema),
**	aborting with an error if anything non-standard is encountered.
*/
//!@{

/*!@doc @see YAML_FromString_Strict()
**	@param	dest	The resulting YAML object
**	@param	str		The string to parse
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`.
*/
//!@{
t_size					YAML_Parse_Strict(s_yaml* *dest, t_utf8 const* str, t_size n);
#define c_yamlparse_s	YAML_Parse_Strict
//!@}

//!@doc @see YAML_Parse_Strict()
//!@{
s_yaml*					YAML_FromString_Strict(t_utf8 const* str);
#define c_strtoyaml_s	YAML_FromString_Strict
//!@}

//!@}



/*============================================================================*\
||                           YAML Printing Operations                         ||
\*============================================================================*/

#define 				YAML_Print	YAML_Print_Pretty
#define c_yamlprint		YAML_Print

#define 				YAML_ToString	YAML_ToString_Pretty
#define c_yamltostr		YAML_ToString



//!@doc Print a `s_yaml` item to string buffer `dest`, writing at most `n` characters.
/*!
**	This prints the YAML in human-readable, block-style notation (with newlines/indentation).
**	@param	dest	The pre-allocated string buffer to write to
**	@param	item	The YAML object to print
**	@param	n		The maximum amount of chars to write into `dest`
**	@returns
**	The amount of characters written to the given `dest` buffer
*/
//!@{
t_size					YAML_Print_Pretty(t_utf8* dest, s_yaml const* item, t_size n);
#define c_yamlprintfmt 	YAML_Print_Pretty
//!@}

//!@doc Like YAML_Print_Pretty(), but this prints the minimum amount of characters possible
/*!
**	Since whitespace/indentation is semantically important in block-style YAML,
**	this function prints the given `item` using flow-style notation (JSON-like),
**	which allows for the most compact single-line output possible.
*/
//!@{
t_size					YAML_Print_Minify(t_utf8* dest, s_yaml const* item, t_size n);
#define c_yamlprintmin 	YAML_Print_Minify
//!@}



//!@doc Get a new string from the given YAML `item`, with readable formatting.
//!@{
t_utf8*					YAML_ToString_Pretty(s_yaml const* item);
#define c_yamltostrfmt	YAML_ToString_Pretty
//!@}

//!@doc Get a new string from the given YAML `item`, without any formatting/whitespace (flow-style).
//!@{
t_utf8*					YAML_ToString_Minify(s_yaml const* item);
#define c_yamltostrmin	YAML_ToString_Minify
//!@}



#if 0
//!@doc Render a s_yaml entity to text using a buffered strategy.
/*!
**	prebuffer is a guess at the final size. guessing well reduces reallocation. `format = 0` means minified, `format = 1` means formatted/pretty.
*/
//!@{
t_utf8*					YAML_Print_Buffered(s_yaml const* item, t_sint prebuffer, t_bool format);
#define c_yamlprintbuf 	YAML_Print_Buffered
//!@}
#endif



/*============================================================================*\
||                             YAML String Operations                         ||
\*============================================================================*/

//!@doc Minify a YAML string, to make it more lightweight: removes all whitespace characters
/*!
**	Minify a YAML, removing blank characters (such as ' ', '\t', '\r', '\n') from strings.
**	NOTE: since whitespace is semantically important in block-style YAML, this function
**	cannot operate in-place like JSON_Minify() does: instead, use YAML_ToString_Minify(),
**	after parsing, to obtain a minimal flow-style (JSON-like) YAML string.
**	The input pointer yaml cannot point to a read-only address area, such as a string constant, 
**	but should point to a readable and writable address area.
*/
//!@{
void				YAML_Minify(t_utf8* yaml); //!< TODO rename to YAML_Minify_InPlace(), and add YAML_Minify(), which would allocate
#define c_yamlmin	YAML_Minify
//!@}



// TODO YAML_ToValid()



/*============================================================================*\
||                             Basic YAML Operations                          ||
\*============================================================================*/

#define YAML_Item		KVT_Item		//!< @alias{KVT_Item}

#define YAML_Duplicate	KVT_Duplicate	//!< @alias{KVT_Duplicate}

#define YAML_Equals		KVT_Equals		//!< @alias{KVT_Equals}

#define YAML_Concat			KVT_Concat			//!< @alias{KVT_Concat}
#define YAML_Concat_Array	KVT_Concat_Array	//!< @alias{KVT_Concat_Array}
#define YAML_Concat_Object	KVT_Concat_Object	//!< @alias{KVT_Concat_Object}



/*============================================================================*\
||                            YAML "create" Operations                        ||
\*============================================================================*/

#define YAML_CreateNull		KVT_CreateNull		//!< @alias{KVT_CreateNull}
#define YAML_CreateBoolean	KVT_CreateBoolean	//!< @alias{KVT_CreateBoolean}
#define YAML_CreateInteger	KVT_CreateInteger	//!< @alias{KVT_CreateInteger}
#define YAML_CreateFloat	KVT_CreateFloat		//!< @alias{KVT_CreateFloat}
#define YAML_CreateString	KVT_CreateString	//!< @alias{KVT_CreateString}
#define YAML_CreateArray	KVT_CreateArray		//!< @alias{KVT_CreateArray}
#define YAML_CreateObject	KVT_CreateObject	//!< @alias{KVT_CreateObject}
#define YAML_CreateRaw		KVT_CreateRaw		//!< @alias{KVT_CreateRaw}



#define YAML_CreateArrayReference	KVT_CreateArrayReference	//!< @alias{KVT_CreateArrayReference}
#define YAML_CreateObjectReference	KVT_CreateObjectReference	//!< @alias{KVT_CreateObjectReference}
#define YAML_CreateStringReference	KVT_CreateStringReference	//!< @alias{KVT_CreateStringReference}



#define YAML_CreateArray_Boolean	KVT_CreateArray_Boolean	//!< @alias{KVT_CreateArray_Boolean}
#define YAML_CreateArray_UInt		KVT_CreateArray_UInt	//!< @alias{KVT_CreateArray_UInt}
#define YAML_CreateArray_U8			KVT_CreateArray_U8		//!< @alias{KVT_CreateArray_U8}
#define YAML_CreateArray_U16		KVT_CreateArray_U16		//!< @alias{KVT_CreateArray_U16}
#define YAML_CreateArray_U32		KVT_CreateArray_U32		//!< @alias{KVT_CreateArray_U32}
#define YAML_CreateArray_U64		KVT_CreateArray_U64		//!< @alias{KVT_CreateArray_U64}
#define YAML_CreateArray_U128		KVT_CreateArray_U128	//!< @alias{KVT_CreateArray_U128}
#define YAML_CreateArray_SInt		KVT_CreateArray_SInt	//!< @alias{KVT_CreateArray_SInt}
#define YAML_CreateArray_S8			KVT_CreateArray_S8		//!< @alias{KVT_CreateArray_S8}
#define YAML_CreateArray_S16		KVT_CreateArray_S16		//!< @alias{KVT_CreateArray_S16}
#define YAML_CreateArray_S32		KVT_CreateArray_S32		//!< @alias{KVT_CreateArray_S32}
#define YAML_CreateArray_S64		KVT_CreateArray_S64		//!< @alias{KVT_CreateArray_S64}
#define YAML_CreateArray_S128		KVT_CreateArray_S128	//!< @alias{KVT_CreateArray_S128}
#define YAML_CreateArray_Float		KVT_CreateArray_Float	//!< @alias{KVT_CreateArray_Float}
#define YAML_CreateArray_F32		KVT_CreateArray_F32		//!< @alias{KVT_CreateArray_F32}
#define YAML_CreateArray_F64		KVT_CreateArray_F64		//!< @alias{KVT_CreateArray_F64}
#define YAML_CreateArray_F80		KVT_CreateArray_F80		//!< @alias{KVT_CreateArray_F80}
#define YAML_CreateArray_F128		KVT_CreateArray_F128	//!< @alias{KVT_CreateArray_F128}
#define YAML_CreateArray_String		KVT_CreateArray_String	//!< @alias{KVT_CreateArray_String}



/*============================================================================*\
||                             YAML "get" Operations                          ||
\*============================================================================*/

#define YAML_GetArrayLength		KVT_GetArrayLength	//!< @alias{KVT_GetArrayLength}

#define YAML_GetArrayItem		KVT_GetArrayItem	//!< @alias{KVT_GetArrayItem}



#define YAML_GetObjectItem \
		YAML_GetObjectItem_CaseSensitive
#define YAML_GetObjectItem_CaseSensitive	KVT_GetObjectItem_CaseSensitive	//!< @alias{KVT_GetObjectItem_CaseSensitive}
#define YAML_GetObjectItem_IgnoreCase		KVT_GetObjectItem_IgnoreCase	//!< @alias{KVT_GetObjectItem_IgnoreCase}



#define YAML_HasObjectItem \
		YAML_HasObjectItem_CaseSensitive
#define YAML_HasObjectItem_CaseSensitive	KVT_HasObjectItem_CaseSensitive	//!< @alias{KVT_HasObjectItem_CaseSensitive}
#define YAML_HasObjectItem_IgnoreCase		KVT_HasObjectItem_IgnoreCase	//!< @alias{KVT_HasObjectItem_IgnoreCase}



#define YAML_Get				KVT_Get	//!< @alias{KVT_Get}

#define YAML_GetValue_Boolean 	KVT_GetValue_Boolean	//!< @alias{KVT_GetValue_Boolean}
#define YAML_GetValue_Integer 	KVT_GetValue_Integer	//!< @alias{KVT_GetValue_Integer}
#define YAML_GetValue_Float 	KVT_GetValue_Float		//!< @alias{KVT_GetValue_Float}
#define YAML_GetValue_String 	KVT_GetValue_String		//!< @alias{KVT_GetValue_String}



/*============================================================================*\
||                             YAML "set" Operations                          ||
\*============================================================================*/

#define YAML_SetValue_Boolean 	KVT_SetValue_Boolean	//!< @alias{KVT_SetValue_Boolean}
#define YAML_SetValue_Integer 	KVT_SetValue_Integer	//!< @alias{KVT_SetValue_Integer}
#define YAML_SetValue_Float 	KVT_SetValue_Float		//!< @alias{KVT_SetValue_Float}
#define YAML_SetValue_String 	KVT_SetValue_String		//!< @alias{KVT_SetValue_String}



#define YAML_AddToArray_Item			KVT_AddToArray_Item				//!< @alias{KVT_AddToArray_Item}
#define YAML_AddToArray_ItemReference	KVT_AddToArray_ItemReference	//!< @alias{KVT_AddToArray_ItemReference}

#define YAML_AddToObject_Item			KVT_AddToObject_Item			//!< @alias{KVT_AddToObject_Item}
#define YAML_AddToObject_ItemReference	KVT_AddToObject_ItemReference	//!< @alias{KVT_AddToObject_ItemReference}



#define YAML_AddToObject_Null		KVT_AddToObject_Null	//!< @alias{KVT_AddToObject_Null}
#define YAML_AddToObject_Boolean	KVT_AddToObject_Boolean	//!< @alias{KVT_AddToObject_Boolean}
#define YAML_AddToObject_Integer	KVT_AddToObject_Integer	//!< @alias{KVT_AddToObject_Integer}
#define YAML_AddToObject_Float		KVT_AddToObject_Float	//!< @alias{KVT_AddToObject_Float}
#define YAML_AddToObject_String		KVT_AddToObject_String	//!< @alias{KVT_AddToObject_String}
#define YAML_AddToObject_Object		KVT_AddToObject_Object	//!< @alias{KVT_AddToObject_Object}
#define YAML_AddToObject_Array		KVT_AddToObject_Array	//!< @alias{KVT_AddToObject_Array}
#define YAML_AddToObject_Raw		KVT_AddToObject_Raw		//!< @alias{KVT_AddToObject_Raw}



/*============================================================================*\
||                             YAML Check Operations                          ||
\*============================================================================*/

#define YAML_IsInvalid	KVT_IsInvalid	//!< @alias{KVT_IsInvalid}
#define YAML_IsNull		KVT_IsNull		//!< @alias{KVT_IsNull}
#define YAML_IsBoolean	KVT_IsBoolean	//!< @alias{KVT_IsBoolean}
#define YAML_IsInteger	KVT_IsInteger	//!< @alias{KVT_IsInteger}
#define YAML_IsFloat	KVT_IsFloat		//!< @alias{KVT_IsFloat}
#define YAML_IsString	KVT_IsString	//!< @alias{KVT_IsString}
#define YAML_IsArray	KVT_IsArray		//!< @alias{KVT_IsArray}
#define YAML_IsObject	KVT_IsObject	//!< @alias{KVT_IsObject}
#define YAML_IsRaw		KVT_IsRaw		//!< @alias{KVT_IsRaw}



/*============================================================================*\
||                             YAML Other Operations                          ||
\*============================================================================*/

#define YAML_Delete 	KVT_Delete	//!< @alias{KVT_Delete}

#define YAML_Detach 	KVT_Detach	//!< @alias{KVT_Detach}

#define YAML_Replace 	KVT_Replace	//!< @alias{KVT_Replace}



#define YAML_Delete_FromArray 	KVT_Delete_FromArray	//!< @alias{KVT_Delete_FromArray}

#define YAML_Detach_FromArray 	KVT_Detach_FromArray	//!< @alias{KVT_Detach_FromArray}

#define YAML_Replace_InArray 	KVT_Replace_InArray		//!< @alias{KVT_Replace_InArray}

#define YAML_Insert_InArray 	KVT_Insert_InArray		//!< @alias{KVT_Insert_InArray}



#define YAML_Delete_FromObject \
		YAML_Delete_FromObject_CaseSensitive
#define YAML_Delete_FromObject_CaseSensitive	KVT_Delete_FromObject_CaseSensitive	//!< @alias{KVT_Delete_FromObject_CaseSensitive}
#define YAML_Delete_FromObject_IgnoreCase		KVT_Delete_FromObject_IgnoreCase	//!< @alias{KVT_Delete_FromObject_IgnoreCase}

#define YAML_Detach_FromObject \
		YAML_Detach_FromObject_CaseSensitive
#define YAML_Detach_FromObject_CaseSensitive	KVT_Detach_FromObject_CaseSensitive	//!< @alias{KVT_Detach_FromObject_CaseSensitive}
#define YAML_Detach_FromObject_IgnoreCase		KVT_Detach_FromObject_IgnoreCase	//!< @alias{KVT_Detach_FromObject_IgnoreCase}

#define YAML_Replace_InObject \
		YAML_Replace_InObject_CaseSensitive
#define YAML_Replace_InObject_CaseSensitive		KVT_Replace_InObject_CaseSensitive	//!< @alias{KVT_Replace_InObject_CaseSensitive}
#define YAML_Replace_InObject_IgnoreCase		KVT_Replace_InObject_IgnoreCase		//!< @alias{KVT_Replace_InObject_IgnoreCase}



#define YAML_Merge	KVT_Merge	//!< @alias{KVT_Merge}



/*! @endgroup */
HEADER_END
#endif
