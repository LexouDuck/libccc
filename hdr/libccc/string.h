/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/string.h                          |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_STRING_H
#define __LIBCCC_STRING_H
/*! @file libccc/string.h
**	This header defines the common standard string (char*) manipulation functions.
**	@addtogroup libccc/string
**	@{
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

/*
**	Types used from <stdarg.h>:
**	-	va_list
*/
#include <stdarg.h>

#include "libccc_config.h"
#include "libccc_define.h"

#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/pointer.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/* TODO function pointers
**	typedef void	(*f_string_iterate)		(char* )
**	typedef void	(*f_string_iterate_i)	(unsigned int, char* )
**	typedef char	(*f_string_map)			(char)
**	typedef char	(*f_string_map_i)		(unsigned int, char)
*/



/*
** ************************************************************************** *|
**                          Basic String Operations                           *|
** ************************************************************************** *|
*/

/*!
**	Creates a new string instance of the given 'size',
**	allocating 'n' bytes of memory, and setting every char to '\0'.
*/
_MALLOC()
char*				String_New(t_size n);
#define c_strnew	String_New

/*!
**	Creates a new string instance of the given 'size',
**	allocating 'n' bytes of memory, and setting every char to 'c'.
*/
_MALLOC()
char*				String_New_C(t_size n, char c);
#define c_strcnew	String_New_C

/*!
**	Sets every byte of the given string 'str' to 'c', only stopping upon
**	reading a '\0' string terminator character.
*/
void				String_Set(char* str, char c);
#define c_strset	String_Set

/*!
**	Clears the given string 'str', setting each character of 'str' to '\0'.
*/
void				String_Clear(char* str);
#define c_strclr	String_Clear

/*!
**	Deletes the string pointed to by 'ptr', freeing the associated memory.
*/
void				String_Delete(char* *a_str);
#define c_strdel	String_Delete

/*!
**	Returns a newly allocated string which is a copy of the given string 'str',
**	(or NULL if the required memory could not be allocated).
*/
_MALLOC()
char*				String_Duplicate(char const* str);
#define c_strdup	String_Duplicate

/*!
**	Returns a newly allocated string which is a copy of the given string 'str',
**	(or NULL if the required memory could not be allocated), copying at most
**	'n' characters.
*/
_MALLOC()
char*				String_Duplicate_N(char const* str, t_size n);
#define c_strndup	String_Duplicate_N

/*!
**	Returns a newly allocated string which is a copy of the given string 'str',
**	(or NULL if the required memory could not be allocated), stopping at the
**	first occurence of 'c'.
*/
_MALLOC()
char*				String_Duplicate_Char(char const* str, char const c);
#define c_strcdup	String_Duplicate_Char

/*!
**	Copies the given string 'src' into 'dest' (null-terminator included),
**	and returns 'dest' (no allocation is performed).
*/
char*				String_Copy(char* dest, char const* src);
#define c_strcpy	String_Copy

/*!
**	Copies the first 'n' characters of the given string 'src' into 'dest',
**	and returns 'dest' (no allocation is performed).
*/
char*				String_Copy_N(char* dest, char const* src, t_size n);
#define c_strncpy	String_Copy_N

/*!
**	Copies the given string 'src' into 'dest', null-terminating the result
**	(the '\0' is placed at: ('dest' + 'size' - 1)),
**	and returns the resulting size of 'dest'.
*/
t_size				String_Copy_L(char* dest, char const* src, t_size size);
#define c_strlcpy	String_Copy_L

/*!
**	Concatenates the given string 'src' to the end of 'dest',
**	(removing dest's '\0' terminator) and returns 'dest'.
*/
char*				String_Concat(char* dest, char const* src);
#define c_strcat	String_Concat

/*!
**	Concatenates the first 'n' characters of the given string 'src'
**	to the end of 'dest', and returns 'dest'.
*/
char*				String_Concat_N(char* dest, char const* src, t_size n);
#define c_strncat	String_Concat_N

/*!
**	Concatenates characters of the given string 'src' to the end of 'dest',
**	null-terminating the result (places the '\0' at ('dest' + 'size' - 1)),
**	and returns the resulting size of 'dest'.
*/
t_size				String_Concat_L(char* dest, char const* src, t_size size);
#define c_strlcat	String_Concat_L



/*
** ************************************************************************** *|
**                                String Checks                               *|
** ************************************************************************** *|
*/

/*!
**	Returns the length of the given null-terminated string 'str'.
*/
t_size				String_Length(char const* str);
#define c_strlen	String_Length

/*!
**	Compares the two given strings, and returns the first difference
**	between characters encountered (str1[i] - str2[i]).
**	Otherwise, it will return 0 if 'str1' and 'str2' are identical.
*/
int						String_Compare(char const* str1, char const* str2);
#define c_strcmp		String_Compare

/*!
**	Compares at most 'n' chars of the two given strings, and returns
**	the first difference of characters encountered: (str1[i] - str2[i]).
*/
int						String_Compare_N(char const* str1, char const* str2, t_size n);
#define c_strncmp		String_Compare_N

/*!
**	Compares the two given strings (case-insensitive), and returns the
**	first difference between characters encountered (str1[i] - str2[i]).
**	Otherwise, it will return 0 if 'str1' and 'str2' are identical.
*/
int						String_Compare_IgnoreCase(char const* str1, char const* str2);
#define c_stricmp		String_Compare_IgnoreCase
#define c_strcasecmp	String_Compare_IgnoreCase

/*!
**	Compares at most 'n' chars of the two given strings (case-insensitive),
**	and returns the first difference of characters encountered: (str1[i] - str2[i]).
*/
int						String_Compare_N_IgnoreCase(char const* str1, char const* str2, t_size n);
#define c_strnicmp		String_Compare_N_IgnoreCase
#define c_strncasecmp	String_Compare_N_IgnoreCase

//!	Returns TRUE if the two given strings have identical content, and FALSE otherwise
/*!
**	@returns 1(TRUE) if the two given strings have identical content, and 0(FALSE) otherwise
*/
t_bool					String_Equals(char const* str1, char const* str2);
#define c_strequ		String_Equals

//!	Returns TRUE if the first 'n' chars of the two given strings match, and FALSE otherwise
/*!
**	@returns 1(TRUE) if the first 'n' chars of the two given strings match, and 0(FALSE) otherwise
*/
t_bool					String_Equals_N(char const* str1, char const* str2, t_size n);
#define c_strnequ		String_Equals_N

//!	Returns TRUE if the two given strings have identical content (case-insensitive), and FALSE otherwise
/*!
**	@returns 1(TRUE) if the two given strings have identical content (case-insensitive), and 0(FALSE) otherwise
*/
t_bool					String_Equals_IgnoreCase(char const* str1, char const* str2);
#define c_striequ		String_Equals_IgnoreCase
#define c_strcaseequ	String_Equals_IgnoreCase

//!	Returns TRUE if the first 'n' chars of the two given strings match (ignoring case), and FALSE otherwise
/*!
**	@returns 1(TRUE) if the first 'n' chars of the two given strings match (ignoring case), and 0(FALSE) otherwise
*/
t_bool					String_Equals_N_IgnoreCase(char const* str1, char const* str2, t_size n);
#define c_strniequ		String_Equals_N_IgnoreCase
#define c_strncaseequ	String_Equals_N_IgnoreCase

/*!
**	Returns 1 if the given string 'str' contains at least one occurence
**	of any character found inside 'charset', returns 0 otherwise.
*/
t_bool						String_Has(char const* str, char const* charset);
#define c_strhas			String_Has

/*!
**	Returns 1 if all the characters inside the given string 'str'
**	are contained within the string 'charset', returns 0 otherwise.
*/
t_bool						String_HasOnly(char const* str, char const* charset);
#define c_strhasonly		String_HasOnly

/*!
**	Returns the amount of occurences of char 'c' in the given string 'str'.
*/
t_size						String_Count_Char(char const* str, char c);
#define c_strcount_char	String_Count_Char

/*!
**	Returns the amount of occurences of chars in 'cset' in the given string
**	'str'.
*/
t_size						String_Count_Charset(char const* str, char const* cset);
#define c_strcount_charset	String_Count_Charset

/*!
**	Returns the amount of occurences of 'query' in the given string 'str'.
*/
t_size						String_Count_String(char const* str, char const* query);
#define c_strcount_str		String_Count_String



/*
** ************************************************************************** *|
**                         String Searching/Replacing                         *|
** ************************************************************************** *|
*/

/*!
**	Returns a pointer to the first occurence of the given character 'c'
**	in the given string 'str' (or NULL if nothing matched).
*/
char*				String_Find_Char(char const* str, char c);
#define c_strchr	String_Find_Char

/*!
**	Returns the first index at which 'c' is found in 'str', or -1 if 'c' does
**	not exist in 'str'.
*/
t_s32				String_Find_CharIndex(char const* str, char c);
#define c_strichr	String_Find_CharIndex

/*!
**	Returns the first occurence of the string 'query' inside
**	the given string 'str' (or NULL if nothing matched).
*/
char*				String_Find_String(char const* str, char const* query);
#define c_strstr	String_Find_String

/*!
**	Returns the first index at which 'query' is found in 'str', or -1 if
**	'query' does not exist in str.
*/
t_s32				String_Find_StringIndex(char const* str, char const* query);
#define c_stristr	String_Find_StringIndex

/*!
**	Returns a pointer to the last occurence of the given character 'c'
**	in the given string 'str' (or NULL if nothing matched).
*/
char*				String_Find_R_Char(char const* str, char c);
#define c_strrchr	String_Find_R_Char

/*!
**	Returns the last occurence of the string 'query' inside
**	the given string 'str' (or NULL if nothing matched).
*/
char*				String_Find_R_String(char const* str, char const* query);
#define c_strrstr	String_Find_R_String

/*!
**	Returns a pointer to the first occurence of the given character 'c'
**	in the given string 'str' (or NULL if nothing matched),
**	searching only the first 'n' characters of 'str'.
*/
char*				String_Find_N_Char(char const* str, char c, t_size n);
#define c_strnchr	String_Find_N_Char

/*!
**	Returns the first occurence of the string 'query' inside
**	the given string 'str' (or NULL if nothing matched),
**	searching only the first 'n' characters of 'str'.
*/
char*				String_Find_N_String(char const* str, char const* query, t_size n);
#define c_strnstr	String_Find_N_String

/*!
**	Returns a new null-terminated string which is a copy of 'str',
**	in which all occurences of the string 'query' have been removed.
*/
_MALLOC()
char*					String_Remove(char const* str, char const* query);
#define c_strremove		String_Remove

/*!
**	Returns a new null-terminated string which is a copy of 'str', in which
**	all non-printable characters found in 'str' are made into printable
**	ANSI-C '\xHH' escape sequences (where "H"s are uppercase hex digits).
*/
_MALLOC()
char*					String_ToEscape(char const* str);
#define c_strtoescape	String_ToEscape

/*!
**	Returns a new null-terminated string which is a copy of 'str',
**	in which every occurence of an 'old' char is replaced with a 'new' char.
*/
//TODO implement
_MALLOC()
char*						String_Replace_Char(char const* str, char const char_old, char const char_new);
#define c_strrep_char		String_Replace_Char

/*!
**	Returns a new null-terminated string which is a copy of 'str',
**	in which every char in the 'old' charset is replaced by the
**	corresponding character in the 'new' charset (at the same index).
*/
//TODO implement
_MALLOC()
char*						String_Replace_Charset(char const* str, char const* charset_old, char const* charset_new);
#define c_strrep_charset	String_Replace_Charset

/*!
**	Returns a new null-terminated string which is a copy of 'str',
**	in which every occurence of the string 'old' is replaced with 'new'.
**	NB: see stringarray.h -> c_strsplit_str for extra notes on bevahior.
*/
_MALLOC()
char*						String_Replace_String(char const* str, char const* str_old, char const* str_new);
#define c_strrep_str		String_Replace_String



/*
** ************************************************************************** *|
**                           String In Place Editors                          *|
** ************************************************************************** *|
*/

/*!
**	Returns a newly allocated string which is the concatenation of 's1' and 's2'.
**	Deletes both inputs from memory. Also, returns the result.
*/
_MALLOC()
char*					String_Merge(char* *a_s1, char* *a_s2);
#define c_strmerge		String_Merge

/*!
**	Returns a newly allocated string which is the concatenation of 'dest' and 'src'.
**	Deletes 'dest', replacing it by the result. Also, returns the result.
*/
_MALLOC()
char*					String_Append(char* *dest, char const* src);
#define c_strappend		String_Append


/*!
**	Returns a newly allocated string which is the concatenation of 'src' and 'dest'.
**	Deletes 'dest', replacing it by the result. Also, returns the result.
*/
_MALLOC()
char*					String_Prepend(char const* src, char* *dest);
#define c_strprepend	String_Prepend

/*!
**	Inserts the string 'src' at index 'index' in 'dest'; deletes 'dest' and
**	replaces it by the result. Also returns the result.
*/
char*							String_Insert_InPlace(char* *dest, char const* src, t_u32 index);
#define c_strinsert_inplace		String_Insert_InPlace

/*!
**	Replaces every occurence of 'old' by 'new' in 'str'.
*/
void								String_Replace_Char_InPlace(char* str, char const char_old, char const char_new);
#define c_strrep_char_inplace		String_Replace_Char_InPlace

/*!
**	Replaces 'old' charset by 'new' charset in 'str'.
**	Works like the bash function tr. Substitutes old[i] by new[i] in 'str'.
**	Fails silently if strlen is different for 'old' and 'new', or if a
**	character is repeated in 'old' (only one image for every antecedent), or if
**	'old' or 'new' are the empty string.
*/
void								String_Replace_Charset_InPlace(char* str, char const* charset_old, char const* charset_new);
#define c_strrep_charset_inplace	String_Replace_Charset_InPlace

/*!
**	Replaces every occurence of the query old by the string new in str.
**	NB: see stringarray.h -> c_strsplit_str for extra notes on bevahior.
*/
void								String_Replace_String_InPlace(char* *a_str, char const* str_old, char const* str_new);
#define c_strrep_str_inplace		String_Replace_String_InPlace

/*!
**	Changes the content of '*a_str' by applying f to each of its chars.
**	Deletes 'a_str', and sets the result in it instead. Also returns the 
**	result.
*/
char*								String_Map_InPlace(char* *a_str, char (*f)(char));
#define c_strmap_inplace			String_Map_InPlace



/*
** ************************************************************************** *|
**                        Common Whitespace Operations                        *|
** ************************************************************************** *|
*/

/*!
**	Returns a new string from 'str' in which all leading and trailing
**	whitespace characters (' ', \n, \t,  \r, \v and \f) have been removed.
*/
_MALLOC()
char*					String_Trim(char const* str, char const* charset);
#define c_strtrim		String_Trim

/*!
**	Returns a new string from 'str' in which all leading
**	characters present in 'charset' have been removed.
*/
_MALLOC()
char*					String_Trim_L(char const* str, char const* charset);
#define c_strtrim_l		String_Trim_L

/*!
**	Returns a new string from 'str' in which all trailing
**	characters present in 'charset' have been removed.
*/
_MALLOC()
char*					String_Trim_R(char const* str, char const* charset);
#define c_strtrim_r		String_Trim_R

/*!
**	Returns a new null-terminated string duplicate of 'str' which is
**	'length' characters long, by padding it with 'c' chars on both sides
**	if the desired 'length' is larger than 'str'.
*/
_MALLOC()
char*					String_Pad(char const* str, char c, t_size length);
#define c_strpad		String_Pad

/*!
**	Returns a new null-terminated string duplicate of 'str' which is
**	'length' characters long, by padding it with 'c' chars on its
**	left side if the desired 'length' is larger than 'str'.
*/
_MALLOC()
char*					String_Pad_L(char const* str, char c, t_size length);
#define c_strpad_l		String_Pad_L

/*!
**	Returns a new null-terminated string duplicate of 'str' which is
**	'length' characters long, by padding it with 'c' chars on its
**	right side if the desired 'length' is larger than 'str'.
*/
_MALLOC()
char*					String_Pad_R(char const* str, char c, t_size length);
#define c_strpad_r		String_Pad_R

/*!
**	Returns a new null-terminated string where every non-printable character
**	of 'str' is replaced by either its 'normal' escape sequence (if available)
**	or a '\x'-type byte escape sequence otherwise.
*/
_MALLOC()
char*					String_ToPrintableString(char const* str);
#define c_strprint		String_ToPrintableString



/*
** ************************************************************************** *|
**                          Other String Operations                           *|
** ************************************************************************** *|
*/

/*!
**	Returns a newly allocated string which is a copy of the given string 'str',
**	but in reverse order (except for the \0 terminator, obviously).
*/
_MALLOC()
char*					String_Reverse(char const* str);
#define c_strrev		String_Reverse

/*!
**	Returns a new null-terminated string which is the result of
**	the concatenation of the two given strings 'str1' and 'str2'.
*/
_MALLOC()
char*					String_Join(char const* str1, char const* str2);
#define c_strjoin		String_Join

/*!
**	Returns a reallocated version of the given string 'dest', in which
**	the string 'str' has been inserted at the index 'offset'.
*/
_MALLOC()
char*					String_Insert(char const* dest, char const* src, t_size offset);
#define c_strinsert		String_Insert

/*!
**	Returns a new null-terminated string which is a subsection of 'str',
**	starting at char index 'index' and copying 'n' characters.
*/
_MALLOC()
char*					String_Sub(char const* str, t_size index, t_size n);
#define c_strsub		String_Sub



//! Constructs a string from the given 'format' string and multiple args (equivalent to 'asprintf()')
/*!
**	Returns a new null-terminated string, which is generated from the given
**	'format' string and variadic args - it is equivalent to 'asprintf()'.
**	________________________________________________________________
**	| Flag	| Output									| Example	|
**	|_______|___________________________________________|___________|
**	%d, %i	Signed decimal integer						392
**	%u		Unsigned decimal integer					7235
**	%o		Unsigned octal								610
**	%x		Unsigned hexadecimal integer				7fa
**	%X		Unsigned hexadecimal integer (uppercase)	7FA
**	%f		Decimal floating point, lowercase			392.65
**	%F		Decimal floating point, uppercase			392.65
**	%e		Scientific notation float, lowercase		3.9265e+2
**	%E		Scientific notation float, uppercase		3.9265E+2
**	%g		Use the shortest representation: %e or %f	392.65
**	%G		Use the shortest representation: %E or %F	392.65
**	%a		Hexadecimal floating point, lowercase		-0xc.90fep-2
**	%A		Hexadecimal floating point, uppercase		-0XC.90FEP-2
**	%c		Character									a
**	%s		String of characters						example
**	%p		Pointer address								b8000000
**	%n		Nothing printed.: the corresponding argument must be a pointer to a signed int. The number of characters written so far is stored in the pointed location.	
**	%%		A % followed by another % character will write a single % to the stream.	%
**	Learn more: https://www.cplusplus.com/reference/cstdio/printf/
*/
_FORMAT(printf, 1, 2)
_MALLOC()
char*					String_Format(char const* format, ...);
#define c_asprintf		String_Format
#define c_strbuild		String_Format
#define c_strformat		String_Format
#define String_Build	String_Format
//! @copydef String_Build, but takes a variadic arguments list
_MALLOC()
char*					String_Format_VA(char const* format, va_list args);
#define String_Build_VA	String_Format_VA



//! Constructs a string from the given 'format' string and multiple args, writing at most 'max' chars into 'dest' (equivalent to 'snprintf()')
/*!
**	@param	dest	The destination buffer, in which to write the resulting string (if NULL, does not write anything and simply returns the length)
**	@param	max		The maximum amount of characters to write to 'dest', including the '\0' null terminator
**	@param	format	The format string used to construct the resulting date string: learn more here https://www.cplusplus.com/reference/cstdio/printf/
**	@returns the amount of characters in the constructed format string, regardless of 'max' size
*/
_FORMAT(printf, 3, 4)
t_size				String_Format_N(char* dest, t_size max, char const* format, ...);
#define c_snprintf	String_Format_N
//! @copydef String_Build, but takes a variadic arguments list
t_size				String_Format_N_VA(char* dest, t_size max, char const* format, va_list args);
#define c_vsnprintf	String_Format_N



/*!
**	Iterates upon each character of the given string 'str',
**	applying the given function 'f' to each of its characters.
*/
void					String_Iterate(char* str, void (*f)(char* c));
#define c_striter		String_Iterate

/*!
**	Iterates upon each character of the given string 'str',
**	applying the function 'f' to each of its chars (with index information).
*/
void					String_Iterate_I(char* str, void (*f)(t_size index, char* c));
#define c_striteri		String_Iterate_I

/*!
**	Creates a new null-terminated string by iterating upon the string 'str',
**	applying the function 'f' to each of its chars.
*/
_MALLOC()
char*					String_Map(char const* str, char (*f)(char c));
#define c_strmap		String_Map

/*!
**	Creates a new null-terminated string by iterating upon the string 'str',
**	applying the function 'f' to each of its chars (with index information).
*/
_MALLOC()
char*					String_Map_I(char const* str, char (*f)(t_size index, char c));
#define c_strmapi		String_Map_I



/*! @} */
HEADER_END
#endif
