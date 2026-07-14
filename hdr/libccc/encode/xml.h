/*============================================================================*\
||                                            ______________________________  ||
||  libccc/encode/xml.h                     |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_ENCODE_XML_H
#define __LIBCCC_ENCODE_XML_H
/*!@group{libccc_encode_xml,44,libccc/encode/xml.h}
**
**	This header defines a simple API to manipulate XML files/strings.
**	- XML spec: https://www.w3.org/TR/xml/
**
**	Like the other libccc/encode/ APIs, this XML API is built upon the generic
**	`s_kvt` "Key-Value Tree" type. Since the KVT struct has no dedicated storage
**	for XML tag attributes, this API uses a simple naming convention to store
**	the full XML data model within a plain KVT tree (similar to conventions
**	used by many XML-to-JSON mappers):
**	- The XML document maps to an OBJECT holding a single child,
**		whose key is the root element's tag name.
**	- An XML element with no attributes and no child elements maps to:
**		- a STRING node holding its text content (or a NULL node, if empty)
**	- An XML element with attributes and/or child elements maps to an OBJECT:
**		- each attribute maps to a STRING child, whose key is the attribute
**			name prefixed with the `'@'` char (see #XML_KEYPREFIX_ATTRIBUTE)
**		- the element's text content (if any) maps to a STRING child with
**			the special key `"#text"` (see #XML_KEY_TEXTCONTENT)
**		- each child element maps to a child node, keyed by its tag name
**	- Repeated sibling elements which share the same tag name are coalesced
**		into a single ARRAY child, keyed by that tag name.
**	The XML printing functions apply this same convention in reverse.
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/encode/common.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//! Like other libccc/encode/ types, XML is just an alias for the KVT type
typedef s_kvt	s_xml;



#define foreach_s_xml(_TYPE_, _VAR_, _XML_)		foreach (_TYPE_, _VAR_, s_xml, _XML_)

#define foreach_s_xml_init			foreach_s_kvt_init
#define foreach_s_xml_exit			foreach_s_kvt_exit
#define foreach_s_xml_loop_init	foreach_s_kvt_loop_init
#define foreach_s_xml_loop_exit	foreach_s_kvt_loop_exit
#define foreach_s_xml_loop_incr	foreach_s_kvt_loop_incr
#define foreach_s_xml_loop_setv	foreach_s_kvt_loop_setv



//! The key prefix char which distinguishes XML attributes from child elements, in the KVT tree
#define XML_KEYPREFIX_ATTRIBUTE	'@'
//! The special key which holds the text content of an XML element that also has attributes/children
#define XML_KEY_TEXTCONTENT		"#text"
//! The default tag name used when printing array items which have no associated key
#define XML_TAG_DEFAULT			"item"
//! The default root tag name used when printing a KVT tree which has no single valid root
#define XML_TAG_ROOT			"root"



/*============================================================================*\
||                            XML Parsing Operations                         ||
\*============================================================================*/

//!@doc Macros which configure the default behavior of the XML parsing functions (`Strict` or `Lenient`)
//!@{
#define 				XML_Parse		XML_Parse_Lenient
#define c_xmlparse		XML_Parse

#define 				XML_Parse_N	XML_Parse_Lenient_N
#define c_xmlparsen	XML_Parse_N

#define 				XML_FromString	XML_FromString_Lenient
#define c_strtoxml		XML_FromString
//!@}



//! Create a new `s_xml` object, parsed from a (valid) XML string
/*!
**	This function creates a `s_xml` object by parsing a XML string.
**	This API supports a large, pragmatic subset of the XML 1.0 spec, notably:
**	- Elements (with proper open/close tag matching), including self-closing tags (`<tag/>`)
**	- Attributes, single-quoted or double-quoted (stored with an `'@'` key prefix: see above)
**	- Text content (leading/trailing whitespace is trimmed), and `<![CDATA[...]]>` sections (verbatim)
**	- The five predefined entities (`&lt;` `&gt;` `&amp;` `&apos;` `&quot;`),
**		as well as numeric character references (`&#NNN;` decimal, and `&#xHH;` hexadecimal)
**	- Comments (`<!-- ... -->`), which are simply skipped
**	- The XML declaration (`<?xml ... ?>`) and processing instructions (`<?target ... ?>`), skipped
**	- A `<!DOCTYPE ...>` declaration (skipped: DTD content is not processed, so there is
**		no entity expansion whatsoever - this parser is inherently safe from XXE attacks)
**	- Namespace prefixes are preserved verbatim as part of tag/attribute names (`<ns:tag>`)
**	Additionally, when parsing in `Lenient` mode:
**	- Attribute values without quotes are accepted (`<tag key=value>`)
**	- Minimized/valueless attributes are accepted (`<input disabled>`, HTML-style),
**		in which case the attribute's value is an empty string
**	- Multiple root-level elements are accepted (useful for HTML/XML fragments)
**	- Unknown entity references (e.g. `&foo;`) are kept verbatim in the text
**	- Mismatched-case or unclosed tags remain errors (they are structurally unrecoverable)
**	The following XML features are NOT supported (a parsing error will be thrown):
**	- Internal DTD subsets with entity definitions (`<!ENTITY ...>`: no entity expansion)
**	- Mixed content ordering: text interleaved between child elements is supported, but all
**		text segments are concatenated into a single `"#text"` value (interleaving order is lost)
**	- Sibling element order is only preserved between same-named siblings (see ARRAY coalescing)
*/
//!@{

//!@doc @see XML_FromString_Lenient()
/*!
**	@param	dest	The resulting XML object
**	@param	str		The string to parse
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`.
*/
//!@{
t_size					XML_Parse_Lenient(s_xml* *dest, t_utf8 const* str, t_size n);
#define c_xmlparse_l	XML_Parse_Lenient
//!@}

//!@doc @see XML_Parse_Lenient()
//!@{
s_xml*					XML_FromString_Lenient(t_utf8 const* str);
#define c_strtoxml_l	XML_FromString_Lenient
//!@}

//!@}



//! Create a new `s_xml` object, parsed from a (valid) XML string
/*!
**	This function creates a `s_xml` object by parsing an XML string,
**	strictly checking the well-formedness rules of the official XML 1.0 spec
**	(https://www.w3.org/TR/xml/), aborting with an error if anything
**	non-well-formed is encountered (unquoted attributes, unknown entities,
**	duplicate attributes, multiple root elements, etc).
*/
//!@{

/*!@doc @see XML_FromString_Strict()
**	@param	dest	The resulting XML object
**	@param	str		The string to parse
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`.
*/
//!@{
t_size					XML_Parse_Strict(s_xml* *dest, t_utf8 const* str, t_size n);
#define c_xmlparse_s	XML_Parse_Strict
//!@}

//!@doc @see XML_Parse_Strict()
//!@{
s_xml*					XML_FromString_Strict(t_utf8 const* str);
#define c_strtoxml_s	XML_FromString_Strict
//!@}

//!@}



/*============================================================================*\
||                           XML Printing Operations                         ||
\*============================================================================*/

#define 				XML_Print	XML_Print_Pretty
#define c_xmlprint		XML_Print

#define 				XML_ToString	XML_ToString_Pretty
#define c_xmltostr		XML_ToString



//!@doc Print a `s_xml` item to string buffer `dest`, writing at most `n` characters.
/*!
**	This prints the XML in human-readable notation (with newlines and tab indentation),
**	preceded by an `<?xml version="1.0" encoding="UTF-8"?>` declaration.
**	Elements which hold only text content are printed on a single line.
**	@param	dest	The pre-allocated string buffer to write to
**	@param	item	The XML object to print
**	@param	n		The maximum amount of chars to write into `dest`
**	@returns
**	The amount of characters written to the given `dest` buffer
*/
//!@{
t_size					XML_Print_Pretty(t_utf8* dest, s_xml const* item, t_size n);
#define c_xmlprintfmt 	XML_Print_Pretty
//!@}

//!@doc Like XML_Print_Pretty(), but this prints the minimum amount of characters possible
/*!
**	This prints the given `item` as a single line of XML, without any whitespace
**	between elements, and without the leading `<?xml ?>` declaration.
*/
//!@{
t_size					XML_Print_Minify(t_utf8* dest, s_xml const* item, t_size n);
#define c_xmlprintmin 	XML_Print_Minify
//!@}



//!@doc Get a new string from the given XML `item`, with readable formatting.
//!@{
t_utf8*					XML_ToString_Pretty(s_xml const* item);
#define c_xmltostrfmt	XML_ToString_Pretty
//!@}

//!@doc Get a new string from the given XML `item`, without any formatting/whitespace (flow-style).
//!@{
t_utf8*					XML_ToString_Minify(s_xml const* item);
#define c_xmltostrmin	XML_ToString_Minify
//!@}



#if 0
//!@doc Render a s_xml entity to text using a buffered strategy.
/*!
**	prebuffer is a guess at the final size. guessing well reduces reallocation. `format = 0` means minified, `format = 1` means formatted/pretty.
*/
//!@{
t_utf8*					XML_Print_Buffered(s_xml const* item, t_sint prebuffer, t_bool format);
#define c_xmlprintbuf 	XML_Print_Buffered
//!@}
#endif



/*============================================================================*\
||                             XML String Operations                         ||
\*============================================================================*/

//!@doc Minify an XML string, to make it more lightweight: removes needless whitespace
/*!
**	Minifies an XML string in-place: removes all comments (`<!-- ... -->`), and all
**	whitespace-only text content found between tags (newlines, indentation, etc).
**	Text content which contains any non-whitespace chars is preserved verbatim,
**	as are `<![CDATA[...]]>` sections and the contents of tags themselves.
**	The input pointer xml cannot point to a read-only address area, such as a string constant,
**	but should point to a readable and writable address area.
*/
//!@{
void				XML_Minify(t_utf8* xml);
#define c_xmlmin	XML_Minify
//!@}



// TODO XML_ToValid()



/*============================================================================*\
||                             Basic XML Operations                          ||
\*============================================================================*/

#define XML_Item		KVT_Item		//!< @alias{KVT_Item}

#define XML_Duplicate	KVT_Duplicate	//!< @alias{KVT_Duplicate}

#define XML_Equals		KVT_Equals		//!< @alias{KVT_Equals}

#define XML_Concat			KVT_Concat			//!< @alias{KVT_Concat}
#define XML_Concat_Array	KVT_Concat_Array	//!< @alias{KVT_Concat_Array}
#define XML_Concat_Object	KVT_Concat_Object	//!< @alias{KVT_Concat_Object}



/*============================================================================*\
||                            XML "create" Operations                        ||
\*============================================================================*/

#define XML_CreateNull		KVT_CreateNull		//!< @alias{KVT_CreateNull}
#define XML_CreateBoolean	KVT_CreateBoolean	//!< @alias{KVT_CreateBoolean}
#define XML_CreateInteger	KVT_CreateInteger	//!< @alias{KVT_CreateInteger}
#define XML_CreateFloat	KVT_CreateFloat		//!< @alias{KVT_CreateFloat}
#define XML_CreateString	KVT_CreateString	//!< @alias{KVT_CreateString}
#define XML_CreateArray	KVT_CreateArray		//!< @alias{KVT_CreateArray}
#define XML_CreateObject	KVT_CreateObject	//!< @alias{KVT_CreateObject}
#define XML_CreateRaw		KVT_CreateRaw		//!< @alias{KVT_CreateRaw}



#define XML_CreateArrayReference	KVT_CreateArrayReference	//!< @alias{KVT_CreateArrayReference}
#define XML_CreateObjectReference	KVT_CreateObjectReference	//!< @alias{KVT_CreateObjectReference}
#define XML_CreateStringReference	KVT_CreateStringReference	//!< @alias{KVT_CreateStringReference}



#define XML_CreateArray_Boolean	KVT_CreateArray_Boolean	//!< @alias{KVT_CreateArray_Boolean}
#define XML_CreateArray_UInt		KVT_CreateArray_UInt	//!< @alias{KVT_CreateArray_UInt}
#define XML_CreateArray_U8			KVT_CreateArray_U8		//!< @alias{KVT_CreateArray_U8}
#define XML_CreateArray_U16		KVT_CreateArray_U16		//!< @alias{KVT_CreateArray_U16}
#define XML_CreateArray_U32		KVT_CreateArray_U32		//!< @alias{KVT_CreateArray_U32}
#define XML_CreateArray_U64		KVT_CreateArray_U64		//!< @alias{KVT_CreateArray_U64}
#define XML_CreateArray_U128		KVT_CreateArray_U128	//!< @alias{KVT_CreateArray_U128}
#define XML_CreateArray_SInt		KVT_CreateArray_SInt	//!< @alias{KVT_CreateArray_SInt}
#define XML_CreateArray_S8			KVT_CreateArray_S8		//!< @alias{KVT_CreateArray_S8}
#define XML_CreateArray_S16		KVT_CreateArray_S16		//!< @alias{KVT_CreateArray_S16}
#define XML_CreateArray_S32		KVT_CreateArray_S32		//!< @alias{KVT_CreateArray_S32}
#define XML_CreateArray_S64		KVT_CreateArray_S64		//!< @alias{KVT_CreateArray_S64}
#define XML_CreateArray_S128		KVT_CreateArray_S128	//!< @alias{KVT_CreateArray_S128}
#define XML_CreateArray_Float		KVT_CreateArray_Float	//!< @alias{KVT_CreateArray_Float}
#define XML_CreateArray_F32		KVT_CreateArray_F32		//!< @alias{KVT_CreateArray_F32}
#define XML_CreateArray_F64		KVT_CreateArray_F64		//!< @alias{KVT_CreateArray_F64}
#define XML_CreateArray_F80		KVT_CreateArray_F80		//!< @alias{KVT_CreateArray_F80}
#define XML_CreateArray_F128		KVT_CreateArray_F128	//!< @alias{KVT_CreateArray_F128}
#define XML_CreateArray_String		KVT_CreateArray_String	//!< @alias{KVT_CreateArray_String}



/*============================================================================*\
||                             XML "get" Operations                          ||
\*============================================================================*/

#define XML_GetArrayLength		KVT_GetArrayLength	//!< @alias{KVT_GetArrayLength}

#define XML_GetArrayItem		KVT_GetArrayItem	//!< @alias{KVT_GetArrayItem}



#define XML_GetObjectItem \
		XML_GetObjectItem_CaseSensitive
#define XML_GetObjectItem_CaseSensitive	KVT_GetObjectItem_CaseSensitive	//!< @alias{KVT_GetObjectItem_CaseSensitive}
#define XML_GetObjectItem_IgnoreCase		KVT_GetObjectItem_IgnoreCase	//!< @alias{KVT_GetObjectItem_IgnoreCase}



#define XML_HasObjectItem \
		XML_HasObjectItem_CaseSensitive
#define XML_HasObjectItem_CaseSensitive	KVT_HasObjectItem_CaseSensitive	//!< @alias{KVT_HasObjectItem_CaseSensitive}
#define XML_HasObjectItem_IgnoreCase		KVT_HasObjectItem_IgnoreCase	//!< @alias{KVT_HasObjectItem_IgnoreCase}



#define XML_Get				KVT_Get	//!< @alias{KVT_Get}

#define XML_GetValue_Boolean 	KVT_GetValue_Boolean	//!< @alias{KVT_GetValue_Boolean}
#define XML_GetValue_Integer 	KVT_GetValue_Integer	//!< @alias{KVT_GetValue_Integer}
#define XML_GetValue_Float 	KVT_GetValue_Float		//!< @alias{KVT_GetValue_Float}
#define XML_GetValue_String 	KVT_GetValue_String		//!< @alias{KVT_GetValue_String}



/*============================================================================*\
||                             XML "set" Operations                          ||
\*============================================================================*/

#define XML_SetValue_Boolean 	KVT_SetValue_Boolean	//!< @alias{KVT_SetValue_Boolean}
#define XML_SetValue_Integer 	KVT_SetValue_Integer	//!< @alias{KVT_SetValue_Integer}
#define XML_SetValue_Float 	KVT_SetValue_Float		//!< @alias{KVT_SetValue_Float}
#define XML_SetValue_String 	KVT_SetValue_String		//!< @alias{KVT_SetValue_String}



#define XML_AddToArray_Item			KVT_AddToArray_Item				//!< @alias{KVT_AddToArray_Item}
#define XML_AddToArray_ItemReference	KVT_AddToArray_ItemReference	//!< @alias{KVT_AddToArray_ItemReference}

#define XML_AddToObject_Item			KVT_AddToObject_Item			//!< @alias{KVT_AddToObject_Item}
#define XML_AddToObject_ItemReference	KVT_AddToObject_ItemReference	//!< @alias{KVT_AddToObject_ItemReference}



#define XML_AddToObject_Null		KVT_AddToObject_Null	//!< @alias{KVT_AddToObject_Null}
#define XML_AddToObject_Boolean	KVT_AddToObject_Boolean	//!< @alias{KVT_AddToObject_Boolean}
#define XML_AddToObject_Integer	KVT_AddToObject_Integer	//!< @alias{KVT_AddToObject_Integer}
#define XML_AddToObject_Float		KVT_AddToObject_Float	//!< @alias{KVT_AddToObject_Float}
#define XML_AddToObject_String		KVT_AddToObject_String	//!< @alias{KVT_AddToObject_String}
#define XML_AddToObject_Object		KVT_AddToObject_Object	//!< @alias{KVT_AddToObject_Object}
#define XML_AddToObject_Array		KVT_AddToObject_Array	//!< @alias{KVT_AddToObject_Array}
#define XML_AddToObject_Raw		KVT_AddToObject_Raw		//!< @alias{KVT_AddToObject_Raw}



/*============================================================================*\
||                             XML Check Operations                          ||
\*============================================================================*/

#define XML_IsInvalid	KVT_IsInvalid	//!< @alias{KVT_IsInvalid}
#define XML_IsNull		KVT_IsNull		//!< @alias{KVT_IsNull}
#define XML_IsBoolean	KVT_IsBoolean	//!< @alias{KVT_IsBoolean}
#define XML_IsInteger	KVT_IsInteger	//!< @alias{KVT_IsInteger}
#define XML_IsFloat	KVT_IsFloat		//!< @alias{KVT_IsFloat}
#define XML_IsString	KVT_IsString	//!< @alias{KVT_IsString}
#define XML_IsArray	KVT_IsArray		//!< @alias{KVT_IsArray}
#define XML_IsObject	KVT_IsObject	//!< @alias{KVT_IsObject}
#define XML_IsRaw		KVT_IsRaw		//!< @alias{KVT_IsRaw}



/*============================================================================*\
||                             XML Other Operations                          ||
\*============================================================================*/

#define XML_Delete 	KVT_Delete	//!< @alias{KVT_Delete}

#define XML_Detach 	KVT_Detach	//!< @alias{KVT_Detach}

#define XML_Replace 	KVT_Replace	//!< @alias{KVT_Replace}



#define XML_Delete_FromArray 	KVT_Delete_FromArray	//!< @alias{KVT_Delete_FromArray}

#define XML_Detach_FromArray 	KVT_Detach_FromArray	//!< @alias{KVT_Detach_FromArray}

#define XML_Replace_InArray 	KVT_Replace_InArray		//!< @alias{KVT_Replace_InArray}

#define XML_Insert_InArray 	KVT_Insert_InArray		//!< @alias{KVT_Insert_InArray}



#define XML_Delete_FromObject \
		XML_Delete_FromObject_CaseSensitive
#define XML_Delete_FromObject_CaseSensitive	KVT_Delete_FromObject_CaseSensitive	//!< @alias{KVT_Delete_FromObject_CaseSensitive}
#define XML_Delete_FromObject_IgnoreCase		KVT_Delete_FromObject_IgnoreCase	//!< @alias{KVT_Delete_FromObject_IgnoreCase}

#define XML_Detach_FromObject \
		XML_Detach_FromObject_CaseSensitive
#define XML_Detach_FromObject_CaseSensitive	KVT_Detach_FromObject_CaseSensitive	//!< @alias{KVT_Detach_FromObject_CaseSensitive}
#define XML_Detach_FromObject_IgnoreCase		KVT_Detach_FromObject_IgnoreCase	//!< @alias{KVT_Detach_FromObject_IgnoreCase}

#define XML_Replace_InObject \
		XML_Replace_InObject_CaseSensitive
#define XML_Replace_InObject_CaseSensitive		KVT_Replace_InObject_CaseSensitive	//!< @alias{KVT_Replace_InObject_CaseSensitive}
#define XML_Replace_InObject_IgnoreCase		KVT_Replace_InObject_IgnoreCase		//!< @alias{KVT_Replace_InObject_IgnoreCase}



#define XML_Merge	KVT_Merge	//!< @alias{KVT_Merge}



/*! @endgroup */
HEADER_END
#endif
