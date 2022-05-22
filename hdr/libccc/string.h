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
**	NOTE: This header includes both ASCII and UTF8 string function APIs.
**
**	@isostd{C,https://en.cppreference.com/w/c/string/byte#StringASCII_manipulation}
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"
#include "libccc/text/string_ascii.h"
#include "libccc/char.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

typedef t_char*	p_str;
typedef t_char*	p_string;



typedef void	(*f_string_iterate)		(t_char* );
typedef void	(*f_string_iterate_i)	(unsigned int, t_char* );
typedef t_char	(*f_string_map)			(t_char);
typedef t_char	(*f_string_map_i)		(unsigned int, t_char);



/*
** ************************************************************************** *|
**                              String functions                              *|
** ************************************************************************** *|
*/

#define String_New                     StringASCII_New
#define String_New_C                   StringASCII_New_C

#define String_Free                    StringASCII_Free
#define String_Delete                  StringASCII_Delete

#define String_Duplicate               StringASCII_Duplicate
#define String_Duplicate_N             StringASCII_Duplicate_N
#define String_Duplicate_Char          StringASCII_Duplicate_Char
#define String_Duplicate_Charset       StringASCII_Duplicate_Charset
#define String_Duplicate_String        StringASCII_Duplicate_String

#define String_Clear                   StringASCII_Clear
#define String_Set                     StringASCII_Set

#define String_Copy                    StringASCII_Copy
#define String_Copy_N                  StringASCII_Copy_N
#define String_Copy_L                  StringASCII_Copy_L

#define String_Add                     StringASCII_Add
#define String_Add_N                   StringASCII_Add_N
#define String_Add_L                   StringASCII_Add_L

#define String_Length                  StringASCII_Length
#define String_Length_N                StringASCII_Length_N

#define String_Equals                  StringASCII_Equals
#define String_Equals_N                StringASCII_Equals_N
#define String_Equals_IgnoreCase       StringASCII_Equals_IgnoreCase
#define String_Equals_N_IgnoreCase     StringASCII_Equals_N_IgnoreCase

#define String_Compare                 StringASCII_Compare
#define String_Compare_N               StringASCII_Compare_N
#define String_Compare_IgnoreCase      StringASCII_Compare_IgnoreCase
#define String_Compare_N_IgnoreCase    StringASCII_Compare_N_IgnoreCase

#define String_Has                     StringASCII_Has
#define String_HasOnly                 StringASCII_HasOnly

#define String_Count_Char              StringASCII_Count_Char
#define String_Count_Charset           StringASCII_Count_Charset
#define String_Count_String            StringASCII_Count_String

#define String_Find_Char               StringASCII_Find_Char
#define String_Find_Charset            StringASCII_Find_Charset
#define String_Find_String             StringASCII_Find_String

#define String_Find_R_Char             StringASCII_Find_R_Char
#define String_FindLast_Char           StringASCII_Find_R_Char

#define String_Find_R_Charset          StringASCII_Find_R_Charset
#define String_FindLast_Charset        StringASCII_Find_R_Charset

#define String_Find_R_String           StringASCII_Find_R_String
#define String_FindLast_String         StringASCII_Find_R_String

#define String_Find_N_Char             StringASCII_Find_N_Char
#define String_Find_N_Charset          StringASCII_Find_N_Charset
#define String_Find_N_String           StringASCII_Find_N_String

#define String_IndexOf_Char            StringASCII_IndexOf_Char
#define String_IndexOf_Charset         StringASCII_IndexOf_Charset
#define String_IndexOf_String          StringASCII_IndexOf_String

#define String_IndexOf_R_Char          StringASCII_IndexOf_R_Char
#define String_LastIndexOf_Char        StringASCII_IndexOf_R_Char

#define String_IndexOf_R_Charset       StringASCII_IndexOf_R_Charset
#define String_LastIndexOf_Charset     StringASCII_IndexOf_R_Charset

#define String_IndexOf_R_String        StringASCII_IndexOf_R_String
#define String_LastIndexOf_String      StringASCII_IndexOf_R_String

#define String_IndexOf_N_Char          StringASCII_IndexOf_N_Char
#define String_IndexOf_N_Charset       StringASCII_IndexOf_N_Charset
#define String_IndexOf_N_String        StringASCII_IndexOf_N_String

#define String_Remove                  StringASCII_Remove

#define String_Replace_Char            StringASCII_Replace_Char
#define String_Replace_Charset         StringASCII_Replace_Charset
#define String_Replace_String          StringASCII_Replace_String

#define String_Concat                  StringASCII_Concat
#define String_Append                  StringASCII_Append
#define String_Prepend                 StringASCII_Prepend
#define String_Merge                   StringASCII_Merge

#define String_Join                    StringASCII_Join
#define String_Insert_InPlace          StringASCII_Insert_InPlace


#define String_Replace_Char_InPlace    StringASCII_Replace_Char_InPlace
#define String_Replace_Charset_InPlace StringASCII_Replace_Charset_InPlace
#define String_Replace_String_InPlace  StringASCII_Replace_String_InPlace

#define String_Map_InPlace             StringASCII_Map_InPlace

#define String_Trim                    StringASCII_Trim
#define String_Trim_L                  StringASCII_Trim_L
#define String_Trim_R                  StringASCII_Trim_R

#define String_Pad                     StringASCII_Pad
#define String_Pad_L                   StringASCII_Pad_L
#define String_Pad_R                   StringASCII_Pad_R


#define String_Print                   StringASCII_ToAsciiEscapedBuf

#define String_ToAsciiEscaped          StringASCII_ToAsciiEscaped
#define String_ToAsciiEscapedBuf       StringASCII_ToAsciiEscapedBuf

#define String_ToJsonEscaped           StringASCII_ToJsonEscaped
#define String_ToJsonEscapedBuf        StringASCII_ToJsonEscapedBuf

#define ENCODER_CHAR_xFF               CharASCII_ToEscaped_xFF

#define String_ToEscaped               StringASCII_ToEscaped
#define String_ToEscaped_e             StringASCII_ToEscaped_e
#define String_ToEscapedBuf            StringASCII_ToEscapedBuf
#define String_ToEscapedBuf_e          StringASCII_ToEscapedBuf_e


#define String_Parse                   StringASCII_Parse

#define String_FromEscape              StringASCII_FromEscape

#define String_Reverse                 StringASCII_Reverse

#define String_Insert                  StringASCII_Insert

#define String_Sub                     StringASCII_Sub

#define String_Iterate                 StringASCII_Iterate
#define String_Iterate_I               StringASCII_Iterate_I

#define String_Map                     StringASCII_Map
#define String_Map_I                   StringASCII_Map_I

#define String_Filter                  StringASCII_Filter
#define String_Filter_I                StringASCII_Filter_I

HEADER_END
#endif

