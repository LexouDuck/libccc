/*============================================================================*\
||                                            ______________________________  ||
||  libccc/string.h                          |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_STRING_H
#define __LIBCCC_STRING_H
/*!@group{libccc_string,18,libccc/string.h}
**
**	This header defines the common standard string manipulation functions.
**	NOTE: This header includes multiple string function APIs: ASCII, UTF32, UTF8
**
**	@isostd{C,https://en.cppreference.com/w/c/string/byte#StringASCII_manipulation}
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"
#include "libccc/text/string/ascii.h"
#include "libccc/text/string/utf32.h"
#include "libccc/text/string/utf8.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//! Type definition for a string of characters
/*!
**	This typedef is only provided for certain niche purposes (such as use with generics),
**	since it is typically not very good practice in C to hide pointers within `typedef` types.
*/
//!@{
typedef t_char*	p_str;
typedef t_char*	p_string;
//!@}



typedef void	(*f_string_iterate)		(t_char* c);
typedef void	(*f_string_iterate_i)	(t_char* c, t_size i);
typedef t_char	(*f_string_map)			(t_char c);
typedef t_char	(*f_string_map_i)		(t_char c, t_size i);
typedef t_bool	(*f_string_filter)		(t_char c);
typedef t_bool	(*f_string_filter_i)	(t_char c, t_size i);



/*============================================================================*\
||                       String API redirection macros                        ||
\*============================================================================*/

// Basic String Operations
#define String_New                     (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_New))
#define String_New_C                   (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_New_C))
#define String_Free                    (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Free))
#define String_Delete                  (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Delete))
#define String_Duplicate               (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Duplicate))
#define String_Duplicate_N             (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Duplicate_N))
#define String_Duplicate_Char          (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Duplicate_Char))
#define String_Duplicate_Charset       (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Duplicate_Charset))
#define String_Duplicate_String        (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Duplicate_String))
#define String_Clear                   (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Clear))
#define String_Set                     (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Set))
#define String_Copy                    (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Copy))
#define String_Copy_N                  (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Copy_N))
#define String_Copy_L                  (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Copy_L))
#define String_Add                     (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Add))
#define String_Add_N                   (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Add_N))
#define String_Add_L                   (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Add_L))
// String Checks
#define String_Length                  (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Length))
#define String_Length_N                (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Length_N))
#define String_Equals                  (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Equals))
#define String_Equals_N                (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Equals_N))
#define String_Equals_IgnoreCase       (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Equals_IgnoreCase))
#define String_Equals_N_IgnoreCase     (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Equals_N_IgnoreCase))
#define String_Compare                 (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Compare))
#define String_Compare_N               (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Compare_N))
#define String_Compare_IgnoreCase      (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Compare_IgnoreCase))
#define String_Compare_N_IgnoreCase    (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Compare_N_IgnoreCase))
#define String_Has                     (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Has))
#define String_HasOnly                 (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_HasOnly))
#define String_Count_Char              (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Count_Char))
#define String_Count_Charset           (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Count_Charset))
#define String_Count_String            (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Count_String))
// String Searching
#define String_Find_Char               (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Find_Char))
#define String_Find_Charset            (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Find_Charset))
#define String_Find_String             (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Find_String))
#define String_Find_R_Char             (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Find_R_Char))
#define String_FindLast_Char           (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Find_R_Char))
#define String_Find_R_Charset          (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Find_R_Charset))
#define String_FindLast_Charset        (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Find_R_Charset))
#define String_Find_R_String           (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Find_R_String))
#define String_FindLast_String         (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Find_R_String))
#define String_Find_N_Char             (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Find_N_Char))
#define String_Find_N_Charset          (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Find_N_Charset))
#define String_Find_N_String           (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Find_N_String))
#define String_IndexOf_Char            (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_IndexOf_Char))
#define String_IndexOf_Charset         (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_IndexOf_Charset))
#define String_IndexOf_String          (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_IndexOf_String))
#define String_IndexOf_R_Char          (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_IndexOf_R_Char))
#define String_LastIndexOf_Char        (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_IndexOf_R_Char))
#define String_IndexOf_R_Charset       (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_IndexOf_R_Charset))
#define String_LastIndexOf_Charset     (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_IndexOf_R_Charset))
#define String_IndexOf_R_String        (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_IndexOf_R_String))
#define String_LastIndexOf_String      (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_IndexOf_R_String))
#define String_IndexOf_N_Char          (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_IndexOf_N_Char))
#define String_IndexOf_N_Charset       (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_IndexOf_N_Charset))
#define String_IndexOf_N_String        (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_IndexOf_N_String))
// String Replacements
#define String_Remove                  (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Remove))
#define String_Replace_Char            (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Replace_Char))
#define String_Replace_Charset         (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Replace_Charset))
#define String_Replace_String          (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Replace_String))
// String Concatenation Operations
#define String_Concat                  (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Concat))
#define String_Append                  (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Append))
#define String_Prepend                 (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Prepend))
#define String_Merge                   (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Merge))
#define String_Join                    (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Join))
// String In-Place Editing
#define String_Insert_InPlace          (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Insert_InPlace))
#define String_Replace_Char_InPlace    (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Replace_Char_InPlace))
#define String_Replace_Charset_InPlace (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Replace_Charset_InPlace))
#define String_Replace_String_InPlace  (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Replace_String_InPlace))
#define String_Map_InPlace             (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Map_InPlace))
// String Whitespace Operations
#define String_Trim                    (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Trim))
#define String_Trim_L                  (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Trim_L))
#define String_Trim_R                  (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Trim_R))
#define String_Pad                     (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Pad))
#define String_Pad_L                   (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Pad_L))
#define String_Pad_R                   (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Pad_R))
// Other String Operations
#define String_Reverse                 (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Reverse))
#define String_Insert                  (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Insert))
#define String_Sub                     (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Sub))
// Functional Operations
#define String_Iterate                 (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Iterate))
#define String_Iterate_I               (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Iterate_I))
#define String_Map                     (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Map))
#define String_Map_I                   (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Map_I))
#define String_Filter                  (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Filter))
#define String_Filter_I                (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Filter_I))

HEADER_END
#endif

