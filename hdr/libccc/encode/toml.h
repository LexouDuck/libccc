/*============================================================================*\
||                                            ______________________________  ||
||  libccc/encode/toml.h                     |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_ENCODE_TOML_H
#define __LIBCCC_ENCODE_TOML_H
/*!@group{libccc_encode_toml}
**
**	This header defines a simple API to manipulate TOML and/or INI files.
**	- TOML spec: https://toml.io/en/v1.0.0#spec
**	- INI files: https://en.wikipedia.org/wiki/INI_file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc/encode/common.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! Like other libccc/encode/ types, TOML is just an alias for the KVT type
typedef s_kvt	s_toml;



#define foreach_s_toml(_TYPE_, _VAR_, _TOML_)		foreach (_TYPE_, _VAR_, s_toml, _TOML_)

#define foreach_s_toml_init			foreach_s_kvt_init
#define foreach_s_toml_exit			foreach_s_kvt_exit
#define foreach_s_toml_loop_init	foreach_s_kvt_loop_init
#define foreach_s_toml_loop_exit	foreach_s_kvt_loop_exit
#define foreach_s_toml_loop_incr	foreach_s_kvt_loop_incr
#define foreach_s_toml_loop_setv	foreach_s_kvt_loop_setv



/*
** ************************************************************************** *|
**                            TOML Parsing Operations                         *|
** ************************************************************************** *|
*/

//!@doc Macros which configure the default behavior of the TOML parsing functions (`Strict` or `Lenient`)
//!@{
#define 				TOML_Parse		TOML_Parse_Lenient
#define c_tomlparse		TOML_Parse

#define 				TOML_Parse_N	TOML_Parse_Lenient_N
#define c_tomlparsen	TOML_Parse_N

#define 				TOML_FromString	TOML_FromString_Lenient
#define c_strtotoml		TOML_FromString
//!@}



//! Create a new `s_toml` object, parsed from a (valid) TOML string
/*!
**	This function creates a `s_toml` object by parsing a TOML string,
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
**	- `null` is a valid value for any key/value pair (so as to be inter-compatible with JSON, YAML, etc)
*/
//!@{

//!@doc @see TOML_FromString_Lenient()
/*!
**	@param	dest	The resulting TOML object
**	@param	str		The string to parse
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`.
*/
//!@{
t_size					TOML_Parse_Lenient(s_toml* *dest, t_utf8 const* str, t_size n);
#define c_tomlparse_l	TOML_Parse_Lenient
//!@}

//!@doc @see TOML_Parse_Lenient()
//!@{
s_toml*					TOML_FromString_Lenient(t_utf8 const* str);
#define c_strtotoml_l	TOML_FromString_Lenient
//!@}

//!@}



//! Create a new `s_toml` object, parsed from a (valid) TOML string
/*!
**	This function creates a `s_toml` object by parsing a TOML string,
**	strictly following the TOML official spec (https://www.toml.org/toml-en.html),
**	aborting with an error if anything non-standard is encountered.
*/
//!@{

/*!@doc @see TOML_FromString_Strict()
**	@param	dest	The resulting TOML object
**	@param	str		The string to parse
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`.
*/
//!@{
t_size					TOML_Parse_Strict(s_toml* *dest, t_utf8 const* str, t_size n);
#define c_tomlparse_s	TOML_Parse_Strict
//!@}

//!@doc @see TOML_Parse_Strict()
//!@{
s_toml*					TOML_FromString_Strict(t_utf8 const* str);
#define c_strtotoml_s	TOML_FromString_Strict
//!@}

//!@}



/*
** ************************************************************************** *|
**                           TOML Printing Operations                         *|
** ************************************************************************** *|
*/

#define 				TOML_Print	TOML_Print_Pretty
#define c_tomlprint		TOML_Print

#define 				TOML_ToString	TOML_ToString_Pretty
#define c_tomltostr		TOML_ToString



//!@doc Print a `s_toml` item to string buffer `dest`, writing at most `n` characters.
/*!
**	@param	dest	The pre-allocated string buffer to write to
**	@param	item	The TOML object to print
**	@param	n		The maximum amount of chars to write into `dest`
**	@returns
**	The amount of characters written to the given `dest` buffer
*/
//!@{
t_size					TOML_Print_Pretty(t_utf8* dest, s_toml const* item, t_size n);
#define c_tomlprintfmt 	TOML_Print_Pretty
//!@}

//!@doc Like TOML_Print_Pretty(), but this prints the minimum amount of characters possible
//!@{
t_size					TOML_Print_Minify(t_utf8* dest, s_toml const* item, t_size n);
#define c_tomlprintmin 	TOML_Print_Minify
//!@}



//!@doc Get a new string from the given TOML `item`, with readable formatting.
//!@{
t_utf8*					TOML_ToString_Pretty(s_toml const* item);
#define c_tomltostrfmt	TOML_ToString_Pretty
//!@}

//!@doc Get a new string from the given TOML `item`, without any formatting/whitespace.
//!@{
t_utf8*					TOML_ToString_Minify(s_toml const* item);
#define c_tomltostrmin	TOML_ToString_Minify
//!@}



#if 0
//!@doc Render a s_toml entity to text using a buffered strategy.
/*!
**	prebuffer is a guess at the final size. guessing well reduces reallocation. `format = 0` means minified, `format = 1` means formatted/pretty.
*/
//!@{
t_utf8*					TOML_Print_Buffered(s_toml const* item, t_sint prebuffer, t_bool format);
#define c_tomlprintbuf 	TOML_Print_Buffered
//!@}
#endif



/*
** ************************************************************************** *|
**                             TOML String Operations                         *|
** ************************************************************************** *|
*/

//!@doc Minify a TOML string, to make it more lightweight: removes all whitespace characters
/*!
**	Minify a TOML, removing blank characters (such as ' ', '\t', '\r', '\n') from strings.
**	The input pointer toml cannot point to a read-only address area, such as a string constant, 
**	but should point to a readable and writable address area.
*/
//!@{
void				TOML_Minify(t_utf8* toml); //!< TODO rename to TOML_Minify_InPlace(), and add TOML_Minify(), which would allocate
#define c_tomlmin	TOML_Minify
//!@}



// TODO TOML_ToValid()



/*
** ************************************************************************** *|
**                             Basic TOML Operations                          *|
** ************************************************************************** *|
*/

#define TOML_Item		KVT_Item		//!< @alias{KVT_Item}

#define TOML_Duplicate	KVT_Duplicate	//!< @alias{KVT_Duplicate}

#define TOML_Equals		KVT_Equals		//!< @alias{KVT_Equals}

#define TOML_Concat			KVT_Concat			//!< @alias{KVT_Concat}
#define TOML_Concat_Array	KVT_Concat_Array	//!< @alias{KVT_Concat_Array}
#define TOML_Concat_Object	KVT_Concat_Object	//!< @alias{KVT_Concat_Object}



/*
** ************************************************************************** *|
**                            TOML "create" Operations                        *|
** ************************************************************************** *|
*/

#define TOML_CreateNull		KVT_CreateNull		//!< @alias{KVT_CreateNull}
#define TOML_CreateBoolean	KVT_CreateBoolean	//!< @alias{KVT_CreateBoolean}
#define TOML_CreateInteger	KVT_CreateInteger	//!< @alias{KVT_CreateInteger}
#define TOML_CreateFloat	KVT_CreateFloat		//!< @alias{KVT_CreateFloat}
#define TOML_CreateString	KVT_CreateString	//!< @alias{KVT_CreateString}
#define TOML_CreateArray	KVT_CreateArray		//!< @alias{KVT_CreateArray}
#define TOML_CreateObject	KVT_CreateObject	//!< @alias{KVT_CreateObject}
#define TOML_CreateRaw		KVT_CreateRaw		//!< @alias{KVT_CreateRaw}



#define TOML_CreateArrayReference	KVT_CreateArrayReference	//!< @alias{KVT_CreateArrayReference}
#define TOML_CreateObjectReference	KVT_CreateObjectReference	//!< @alias{KVT_CreateObjectReference}
#define TOML_CreateStringReference	KVT_CreateStringReference	//!< @alias{KVT_CreateStringReference}



#define TOML_CreateArray_Boolean	KVT_CreateArray_Boolean	//!< @alias{KVT_CreateArray_Boolean}
#define TOML_CreateArray_UInt		KVT_CreateArray_UInt	//!< @alias{KVT_CreateArray_UInt}
#define TOML_CreateArray_U8			KVT_CreateArray_U8		//!< @alias{KVT_CreateArray_U8}
#define TOML_CreateArray_U16		KVT_CreateArray_U16		//!< @alias{KVT_CreateArray_U16}
#define TOML_CreateArray_U32		KVT_CreateArray_U32		//!< @alias{KVT_CreateArray_U32}
#define TOML_CreateArray_U64		KVT_CreateArray_U64		//!< @alias{KVT_CreateArray_U64}
#define TOML_CreateArray_U128		KVT_CreateArray_U128	//!< @alias{KVT_CreateArray_U128}
#define TOML_CreateArray_SInt		KVT_CreateArray_SInt	//!< @alias{KVT_CreateArray_SInt}
#define TOML_CreateArray_S8			KVT_CreateArray_S8		//!< @alias{KVT_CreateArray_S8}
#define TOML_CreateArray_S16		KVT_CreateArray_S16		//!< @alias{KVT_CreateArray_S16}
#define TOML_CreateArray_S32		KVT_CreateArray_S32		//!< @alias{KVT_CreateArray_S32}
#define TOML_CreateArray_S64		KVT_CreateArray_S64		//!< @alias{KVT_CreateArray_S64}
#define TOML_CreateArray_S128		KVT_CreateArray_S128	//!< @alias{KVT_CreateArray_S128}
#define TOML_CreateArray_Float		KVT_CreateArray_Float	//!< @alias{KVT_CreateArray_Float}
#define TOML_CreateArray_F32		KVT_CreateArray_F32		//!< @alias{KVT_CreateArray_F32}
#define TOML_CreateArray_F64		KVT_CreateArray_F64		//!< @alias{KVT_CreateArray_F64}
#define TOML_CreateArray_F80		KVT_CreateArray_F80		//!< @alias{KVT_CreateArray_F80}
#define TOML_CreateArray_F128		KVT_CreateArray_F128	//!< @alias{KVT_CreateArray_F128}
#define TOML_CreateArray_String		KVT_CreateArray_String	//!< @alias{KVT_CreateArray_String}



/*
** ************************************************************************** *|
**                             TOML "get" Operations                          *|
** ************************************************************************** *|
*/

#define TOML_GetArrayLength		KVT_GetArrayLength	//!< @alias{KVT_GetArrayLength}

#define TOML_GetArrayItem		KVT_GetArrayItem	//!< @alias{KVT_GetArrayItem}



#define TOML_GetObjectItem \
		TOML_GetObjectItem_CaseSensitive
#define TOML_GetObjectItem_CaseSensitive	KVT_GetObjectItem_CaseSensitive	//!< @alias{KVT_GetObjectItem_CaseSensitive}
#define TOML_GetObjectItem_IgnoreCase		KVT_GetObjectItem_IgnoreCase	//!< @alias{KVT_GetObjectItem_IgnoreCase}



#define TOML_HasObjectItem \
		TOML_HasObjectItem_CaseSensitive
#define TOML_HasObjectItem_CaseSensitive	KVT_HasObjectItem_CaseSensitive	//!< @alias{KVT_HasObjectItem_CaseSensitive}
#define TOML_HasObjectItem_IgnoreCase		KVT_HasObjectItem_IgnoreCase	//!< @alias{KVT_HasObjectItem_IgnoreCase}



#define TOML_Get				KVT_Get	//!< @alias{KVT_Get}

#define TOML_GetValue_Boolean 	KVT_GetValue_Boolean	//!< @alias{KVT_GetValue_Boolean}
#define TOML_GetValue_Integer 	KVT_GetValue_Integer	//!< @alias{KVT_GetValue_Integer}
#define TOML_GetValue_Float 	KVT_GetValue_Float		//!< @alias{KVT_GetValue_Float}
#define TOML_GetValue_String 	KVT_GetValue_String		//!< @alias{KVT_GetValue_String}



/*
** ************************************************************************** *|
**                             TOML "set" Operations                          *|
** ************************************************************************** *|
*/

#define TOML_SetValue_Boolean 	KVT_SetValue_Boolean	//!< @alias{KVT_SetValue_Boolean}
#define TOML_SetValue_Integer 	KVT_SetValue_Integer	//!< @alias{KVT_SetValue_Integer}
#define TOML_SetValue_Float 	KVT_SetValue_Float		//!< @alias{KVT_SetValue_Float}
#define TOML_SetValue_String 	KVT_SetValue_String		//!< @alias{KVT_SetValue_String}



#define TOML_AddToArray_Item			KVT_AddToArray_Item				//!< @alias{KVT_AddToArray_Item}
#define TOML_AddToArray_ItemReference	KVT_AddToArray_ItemReference	//!< @alias{KVT_AddToArray_ItemReference}

#define TOML_AddToObject_Item			KVT_AddToObject_Item			//!< @alias{KVT_AddToObject_Item}
#define TOML_AddToObject_ItemReference	KVT_AddToObject_ItemReference	//!< @alias{KVT_AddToObject_ItemReference}



#define TOML_AddToObject_Null		KVT_AddToObject_Null	//!< @alias{KVT_AddToObject_Null}
#define TOML_AddToObject_Boolean	KVT_AddToObject_Boolean	//!< @alias{KVT_AddToObject_Boolean}
#define TOML_AddToObject_Integer	KVT_AddToObject_Integer	//!< @alias{KVT_AddToObject_Integer}
#define TOML_AddToObject_Float		KVT_AddToObject_Float	//!< @alias{KVT_AddToObject_Float}
#define TOML_AddToObject_String		KVT_AddToObject_String	//!< @alias{KVT_AddToObject_String}
#define TOML_AddToObject_Object		KVT_AddToObject_Object	//!< @alias{KVT_AddToObject_Object}
#define TOML_AddToObject_Array		KVT_AddToObject_Array	//!< @alias{KVT_AddToObject_Array}
#define TOML_AddToObject_Raw		KVT_AddToObject_Raw		//!< @alias{KVT_AddToObject_Raw}



/*
** ************************************************************************** *|
**                             TOML Check Operations                          *|
** ************************************************************************** *|
*/

#define TOML_IsInvalid	KVT_IsInvalid	//!< @alias{KVT_IsInvalid}
#define TOML_IsNull		KVT_IsNull		//!< @alias{KVT_IsNull}
#define TOML_IsBoolean	KVT_IsBoolean	//!< @alias{KVT_IsBoolean}
#define TOML_IsInteger	KVT_IsInteger	//!< @alias{KVT_IsInteger}
#define TOML_IsFloat	KVT_IsFloat		//!< @alias{KVT_IsFloat}
#define TOML_IsString	KVT_IsString	//!< @alias{KVT_IsString}
#define TOML_IsArray	KVT_IsArray		//!< @alias{KVT_IsArray}
#define TOML_IsObject	KVT_IsObject	//!< @alias{KVT_IsObject}
#define TOML_IsRaw		KVT_IsRaw		//!< @alias{KVT_IsRaw}



/*
** ************************************************************************** *|
**                             TOML Other Operations                          *|
** ************************************************************************** *|
*/

#define TOML_Delete 	KVT_Delete	//!< @alias{KVT_Delete}

#define TOML_Detach 	KVT_Detach	//!< @alias{KVT_Detach}

#define TOML_Replace 	KVT_Replace	//!< @alias{KVT_Replace}



#define TOML_Delete_FromArray 	KVT_Delete_FromArray	//!< @alias{KVT_Delete_FromArray}

#define TOML_Detach_FromArray 	KVT_Detach_FromArray	//!< @alias{KVT_Detach_FromArray}

#define TOML_Replace_InArray 	KVT_Replace_InArray		//!< @alias{KVT_Replace_InArray}

#define TOML_Insert_InArray 	KVT_Insert_InArray		//!< @alias{KVT_Insert_InArray}



#define TOML_Delete_FromObject \
		TOML_Delete_FromObject_CaseSensitive
#define TOML_Delete_FromObject_CaseSensitive	KVT_Delete_FromObject_CaseSensitive	//!< @alias{KVT_Delete_FromObject_CaseSensitive}
#define TOML_Delete_FromObject_IgnoreCase		KVT_Delete_FromObject_IgnoreCase	//!< @alias{KVT_Delete_FromObject_IgnoreCase}

#define TOML_Detach_FromObject \
		TOML_Detach_FromObject_CaseSensitive
#define TOML_Detach_FromObject_CaseSensitive	KVT_Detach_FromObject_CaseSensitive	//!< @alias{KVT_Detach_FromObject_CaseSensitive}
#define TOML_Detach_FromObject_IgnoreCase		KVT_Detach_FromObject_IgnoreCase	//!< @alias{KVT_Detach_FromObject_IgnoreCase}

#define TOML_Replace_InObject \
		TOML_Replace_InObject_CaseSensitive
#define TOML_Replace_InObject_CaseSensitive		KVT_Replace_InObject_CaseSensitive	//!< @alias{KVT_Replace_InObject_CaseSensitive}
#define TOML_Replace_InObject_IgnoreCase		KVT_Replace_InObject_IgnoreCase		//!< @alias{KVT_Replace_InObject_IgnoreCase}



#define TOML_Merge	KVT_Merge	//!< @alias{KVT_Merge}



/*! @endgroup */
HEADER_END
#endif
