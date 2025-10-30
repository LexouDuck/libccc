/*============================================================================*\
||                                            ______________________________  ||
||  libccc/stringarray.h                     |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_STRINGARRAY_H
#define __LIBCCC_STRINGARRAY_H
/*!@group{libccc_stringarray,19,libccc/stringarray.h}
**
**	This header defines some useful functions for string array (t_char**) handling.
**	NOTE: This header includes multiple string array function APIs: ASCII, UTF32, UTF8
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"
#include "libccc/text/stringarray/ascii.h"
#include "libccc/text/stringarray/utf32.h"
#include "libccc/text/stringarray/utf8.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//! Type definition for an array of strings (ASCII format)
/*!
**	This typedef is only provided for certain niche purposes (such as use with generics),
**	since it is typically not very good practice in C to hide pointers within `typedef` types.
*/
//!@{
typedef t_char**	p_strarr;
typedef t_char**	p_strarray;
typedef t_char**	p_stringarray;
//!@}



typedef t_char*		(*f_stringarray_iterate)	(t_char* str);
typedef t_char*		(*f_stringarray_iterate_i)	(t_char* str, t_uint i);
typedef t_char*		(*f_stringarray_map)		(t_char const* str);
typedef t_char*		(*f_stringarray_map_i)		(t_char const* str, t_uint i);
typedef t_bool		(*f_stringarray_filter)		(t_char const* str);
typedef t_bool		(*f_stringarray_filter_i)	(t_char const* str, t_uint i);
typedef void*		(*f_stringarray_reduce)		(t_char const* str, void* acc);
typedef void*		(*f_stringarray_reduce_i)	(t_char const* str, void* acc, t_uint i);



/*============================================================================*\
||                     StringArray API redirection macros                     ||
\*============================================================================*/

// StringArray: string splitting
#define String_Split_Char			(CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Split_Char))
#define String_Split_Charset		(CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Split_Charset))
#define String_Split_String			(CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Split_String))
#define String_Divide				(CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Divide))
// StringArray: checking operations
#define StringArray_Length			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Length))
#define StringArray_TotalLength		(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_TotalLength))
// StringArray: creation operations
#define StringArray_New				(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_New))
#define StringArray_New_C			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_New_C))
#define StringArray_Create			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Create))
#define StringArray_Duplicate		(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Duplicate))
#define StringArray_Sub				(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Sub))
#define StringArray_Copy			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Copy))
// StringArray: deletion operations
#define StringArray_Free			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Free))
#define StringArray_Delete			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Delete))
// StringArray: editing operations
#define StringArray_Add				(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Add))
#define StringArray_Insert			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Insert))
#define StringArray_Wedge			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Wedge))
#define StringArray_RemoveAt		(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_RemoveAt))
#define StringArray_RemoveAt_F		(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_RemoveAt_F))
#define StringArray_Remove			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Remove))
#define StringArray_Remove_F		(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Remove_F))
#define StringArray_RemoveAll		(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_RemoveAll))
#define StringArray_RemoveAll_F		(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_RemoveAll_F))
#define StringArray_Replace			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Replace))
#define StringArray_ReplaceFirst	(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_ReplaceFirst))
#define StringArray_ReplaceLast		(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_ReplaceLast))
#define StringArray_Reverse			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Reverse))
#define StringArray_Pad_L			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Pad_L))
// StringArray: concatenation operations
#define StringArray_Concat			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Concat))
#define StringArray_Append			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Append))
#define StringArray_Prepend			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Prepend))
#define StringArray_Merge			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Merge))
#define StringArray_Join			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Join))
// StringArray: comparison operations
#define StringArray_Equals			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Equals))
#define StringArray_Equals_N		(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Equals_N))
#define StringArray_Compare			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Compare))
#define StringArray_Compare_N		(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Compare_N))
// StringArray: analysis operations
#define StringArray_Find			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Find))
#define StringArray_Find_F			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Find_F))
#define StringArray_IndexOf			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_IndexOf))
#define StringArray_IndexOf_F		(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_IndexOf_F))
#define StringArray_Count_Char		(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Count_Char))
#define StringArray_Count_Charset	(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Count_Charset))
#define StringArray_Count_String	(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Count_String))
// StringArray: functional operations
#define StringArray_Iterate			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Iterate))
#define StringArray_Iterate_I		(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Iterate_I))
#define StringArray_Map				(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Map))
#define StringArray_Map_I			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Map_I))
#define StringArray_Filter			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Filter))
#define StringArray_Filter_I		(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Filter_I))
#define StringArray_Reduce			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Reduce))
#define StringArray_Reduce_I		(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Reduce_I))
#define StringArray_Fold			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Fold))
#define StringArray_Fold_I			(CONCAT(CONCAT(StringArray,LIBCONFIG_STRING_FORMAT),_Fold_I))



/*! @endgroup */
HEADER_END
#endif
