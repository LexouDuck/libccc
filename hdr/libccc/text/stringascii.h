/*============================================================================*\
||                                            ______________________________  ||
||  libccc/text/stringascii.h                |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_STRING_ASCII_H
#define __LIBCCC_STRING_ASCII_H
/*!@group{libccc_stringascii,18,libccc/string.h}
**
**	This header defines the common standard ascii text string manipulation functions.
**
**	@isostd{C,https://en.cppreference.com/w/c/string/byte#StringASCII_manipulation}
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"

#include "libccc/format.h" // TODO remove this include ? (breaking change)
#include "libccc/text/ascii.h"
#include "libccc/text/stringutf8.h" // TODO: remove asap

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! Type definition for a string of characters
/*!
**	This typedef is only provided for certain niche purposes, since it is typically
**	not very good practice in C to hide pointers within `typedef` types.
*/
//!@{
typedef t_ascii*	p_strascii;
typedef t_ascii*	p_stringascii;
//!@}



/* TODO function pointers
typedef void	(*f_string_ascii_iterate)		(t_ascii* )
typedef void	(*f_string_ascii_iterate_i)		(unsigned int, t_ascii* )
typedef t_ascii	(*f_string_ascii_map)			(t_ascii)
typedef t_ascii	(*f_string_ascii_map_i)			(unsigned int, t_ascii)
*/



/*
** ************************************************************************** *|
**                          Basic String Operations                           *|
** ************************************************************************** *|
*/

//!@doc Returns a new string which is `n + 1` bytes long (to account for the null-terminator).
/*!
**	@nonstd
**
**	Allocates a new region of memory of the specified size `n + 1`, the last byte
**	being used for the string null terminator character `'\0'`.
**
**	@param	n	The length of the string to allocate (not including null-terminator)
**	@returns
**	A newly allocated region of zero-filled memory which is `n + 1` bytes in length,
**	and has every char set to `'\0'`.
*/
//!@{
_MALLOC()
t_ascii*			StringASCII_New(t_size n);
#define c_strnew	StringASCII_New
//!@}

//!@doc Returns a newly allocated region of `c`-filled memory, which is `n + 1` bytes long.
/*!
**	@nonstd
**
**	Allocates a new region of memory of the specified size `n + 1`, the last byte
**	being used for the string null terminator character `'\0'`.
**
**	@param	n	The length of the string to allocate (not including null-terminator)
**	@param	c	The character value to fill each byte with
**	@returns
**	A newly allocated string which is `n + 1` bytes in length,
**	and has every char set to `c`, plus the last char set to `'\0'`.
*/
//!@{
_MALLOC()
t_ascii*			StringASCII_New_C(t_size n, t_ascii c);
#define c_strcnew	StringASCII_New_C
//!@}



//!@doc Deallocates the given string `str`.
/*!
**	@nonstd
*/
//!@{
void				StringASCII_Free(t_ascii* str);
#define c_strfree	StringASCII_Free
//!@}

//!@doc Deallocates the string pointed to by `*a_str`, and sets the pointer to `NULL`.
/*!
**	@nonstd
*/
//!@{
void				StringASCII_Delete(t_ascii* *a_str);
#define c_strdel	StringASCII_Delete
//!@}



//!@doc Duplicates the given `str`
/*!
**	@isostd{C23,https://en.cppreference.com/w/c/string/byte/strdup}
**
**	@returns
**	A newly allocated string which is a copy of the given string `str`,
**	or `NULL` if the required memory could not be allocated.
*/
//!@{
_MALLOC()
t_ascii*			StringASCII_Duplicate(t_ascii const* str);
#define c_strdup	StringASCII_Duplicate
//!@}

//!@doc Duplicates the given `str`, the copy being at most `n` chars long
/*!
**	@isostd{C23,https://en.cppreference.com/w/c/string/byte/strndup}
**
**	@returns
**	A newly allocated string which is a copy of the given string `str`,
**	or `NULL` if the required memory could not be allocated,
**	copying at most `n` characters.
*/
//!@{
_MALLOC()
t_ascii*			StringASCII_Duplicate_N(t_ascii const* str, t_size n);
#define c_strndup	StringASCII_Duplicate_N
//!@}

//!@doc Duplicates the given `str`, the copy stops at the first occurence of `c`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string which is a copy of the given string `str`,
**	or `NULL` if the required memory could not be allocated,
**	stopping at the first occurence of the given char `c`.
*/
//!@{
_MALLOC()
t_ascii*			StringASCII_Duplicate_Char(t_ascii const* str, t_ascii const c);
#define c_strchrdup	StringASCII_Duplicate_Char
//!@}

//!@doc Duplicates the given `str`, the copy stops at the first occurence of any char in `charset`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string which is a copy of the given string `str`,
**	or `NULL` if the required memory could not be allocated,
**	stopping at the first occurence of any char contained within the given `charset`.
*/
//!@{
_MALLOC()
t_ascii*			StringASCII_Duplicate_Charset(t_ascii const* str, t_ascii const* charset);
#define c_strcstdup	StringASCII_Duplicate_Charset
//!@}

//!@doc Duplicates the given `str`, the copy stops at the first occurence of any char in `string`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string which is a copy of the given string `str`,
**	or `NULL` if the required memory could not be allocated,
**	stopping at the first occurence of the given string `target`.
*/
//!@{
_MALLOC()
t_ascii*			StringASCII_Duplicate_String(t_ascii const* str, t_ascii const* target);
#define c_strstrdup	StringASCII_Duplicate_String
//!@}



//!@doc Clears the given string `str`, setting each character of `str` to `'\0'`.
/*!
**	@nonstd
*/
//!@{
void				StringASCII_Clear(t_ascii* str);
#define c_strclr	StringASCII_Clear
//!@}

//!@doc Sets every char of the given string `str` to `c`, only stopping upon reading a `'\0'` null-terminator.
/*!
**	@nonstd
**
**	Fills the given string `str` with the character `c`
**
**	@param	str	The string to fill
**	@param	c	The character value to fill with
*/
//!@{
void				StringASCII_Set(t_ascii* str, t_ascii c);
#define c_strset	StringASCII_Set
//!@}

// TODO strnset() StringASCII_Set_N



//!@doc Copies the given string `str` into `dest`, and returns `dest`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strcpy}
**
**	Copies the given string `src` into `dest` (null-terminator included)
**
**	@returns
**	`dest` (no allocation is performed).
*/
//!@{
t_ascii*			StringASCII_Copy(t_ascii* dest, t_ascii const* src);
#define c_strcpy	StringASCII_Copy
//!@}

//!@doc Copies the first `n` characters of the given string `src` into `dest`, and returns `dest`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strncpy}
**
**	Copies the first `n` characters of the given string `src` into `dest`
**
**	@returns
**	`dest` (no allocation is performed).
*/
//!@{
t_ascii*			StringASCII_Copy_N(t_ascii* dest, t_ascii const* src, t_size n);
#define c_strncpy	StringASCII_Copy_N
//!@}

//!@doc Copies the given string `src` into `dest`, null-terminating the result and returning its length
/*!
**	@isostd{BSD,https://linux.die.net/man/3/strlcpy}
**
**	Copies the given string `src` into `dest`, null-terminating the result.
**	The `'\0'` null-terminator is placed at the position: `(dest + size - 1)`.
**
**	@returns
**	The resulting size of `dest`.
*/
//!@{
t_size				StringASCII_Copy_L(t_ascii* dest, t_ascii const* src, t_size size);
#define c_strlcpy	StringASCII_Copy_L
//!@}



//!@doc Concatenates the given string `src` to the end of `dest`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strcat}
**
**	Concatenates the given string `src` to the end of `dest` (removing dest's null-terminator).
**
**	@returns
**	`dest` (no allocation is performed).
*/
//!@{
t_ascii*			StringASCII_Add(t_ascii* dest, t_ascii const* src);
#define c_strcat	StringASCII_Add
#define c_stradd	StringASCII_Add
//!@}

//!@doc Concatenates the given string `src` to the end of `dest`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strncat}
**
**	Concatenates the first `n` characters of the given string `src` to the end of `dest`.
**
**	@returns
**	`dest` (no allocation is performed).
*/
//!@{
t_ascii*			StringASCII_Add_N(t_ascii* dest, t_ascii const* src, t_size n);
#define c_strncat	StringASCII_Add_N
#define c_strnadd	StringASCII_Add_N
//!@}

//!@doc Concatenates the given string `src` to the end of `dest`
/*!
**	@isostd{BSD,https://linux.die.net/man/3/strlcat}
**
**	Concatenates characters of the given string `src` to the end of `dest`, null-terminating the result.
**	The `'\0'` null-terminator is placed at the position: `(dest + size - 1)`.
**
**	@returns
**	The resulting size of `dest`.
*/
//!@{
t_size				StringASCII_Add_L(t_ascii* dest, t_ascii const* src, t_size size);
#define c_strlcat	StringASCII_Add_L
#define c_strladd	StringASCII_Add_L
//!@}



/*
** ************************************************************************** *|
**                                String Checks                               *|
** ************************************************************************** *|
*/

//!@doc Get the length (in bytes) of a string, excluding final '\0'
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strlen}
**
**	@returns
**	The length of the given null-terminated string `str`.
*/
//!@{
t_size				StringASCII_Length(t_ascii const* str);
#define c_strlen	StringASCII_Length
//!@}

//!@doc Get the length (in bytes) of a string, excluding final '\0', but at most `n` bytes 
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strlen}
**
**	@returns
**	`StringASCII_Length(str)` if that is less than `n`, or `n` if there is no '\0' among the first `n` bytes of the string
*/
//!@{
t_size				StringASCII_Length_N(t_ascii const* str, t_size n);
#define c_strnlen	StringASCII_Length_N
//!@}


//!@doc	Checks whether the two given strings match
/*!
**	@nonstd
**
**	@returns
**	`TRUE` if the two given strings have identical content,
**	`FALSE` otherwise
*/
//!@{
t_bool				StringASCII_Equals(t_ascii const* str1, t_ascii const* str2);
#define c_strequ	StringASCII_Equals
//!@}

//!@doc	Checks whether the first `n` chars of the two given strings match
/*!
**	@nonstd
**
**	@returns
**	`TRUE` if the first `n` chars of the two given strings are identical,
**	`FALSE` otherwise
*/
//!@{
t_bool				StringASCII_Equals_N(t_ascii const* str1, t_ascii const* str2, t_size n);
#define c_strnequ	StringASCII_Equals_N
//!@}

//!@doc	Checks whether the two given strings match (case-insensitive)
/*!
**	@nonstd
**
**	@returns
**	`TRUE` if the two given strings have identical content (case-insensitive),
**	`FALSE` otherwise
*/
//!@{
t_bool					StringASCII_Equals_IgnoreCase(t_ascii const* str1, t_ascii const* str2);
#define c_striequ		StringASCII_Equals_IgnoreCase
#define c_strcaseequ	StringASCII_Equals_IgnoreCase
//!@}

//!@doc	Checks whether the first `n` chars of the two given strings match (case-insensitive)
/*!
**	@nonstd
**
**	@returns
**	`TRUE` if the first `n` chars of the two given strings match (case-insensitive),
**	`FALSE` otherwise
*/
//!@{
t_bool					StringASCII_Equals_N_IgnoreCase(t_ascii const* str1, t_ascii const* str2, t_size n);
#define c_strniequ		StringASCII_Equals_N_IgnoreCase
#define c_strncaseequ	StringASCII_Equals_N_IgnoreCase
//!@}

// TODO StringASCII_EqualsUntil_Char()
// TODO StringASCII_EqualsUntil_Charset()
// TODO StringASCII_EqualsUntil_String()



//!@doc Compares the content of the two given strings
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strcmp}
**
**	@returns
**	The first difference between chars encountered: `(str1[i] - str2[i])`,
**	or `0` if `str1` and `str2` have identical content.
*/
//!@{
t_sint				StringASCII_Compare(t_ascii const* str1, t_ascii const* str2);
#define c_strcmp	StringASCII_Compare
//!@}

//!@doc Compares the first `n` chars of the two given strings
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strncmp}
**
**	@returns
**	The first difference between chars encountered: `(str1[i] - str2[i])`,
**	or `0` if `str1` and `str2` have identical content.
*/
//!@{
t_sint				StringASCII_Compare_N(t_ascii const* str1, t_ascii const* str2, t_size n);
#define c_strncmp	StringASCII_Compare_N
//!@}

//!@doc Compares the two given strings (case-insensitive)
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/strcasecmp}
**
**	@returns
**	The first difference between chars encountered: `(str1[i] - str2[i])`,
**	or `0` if `str1` and `str2` have identical content.
*/
//!@{
t_sint					StringASCII_Compare_IgnoreCase(t_ascii const* str1, t_ascii const* str2);
#define c_stricmp		StringASCII_Compare_IgnoreCase
#define c_strcasecmp	StringASCII_Compare_IgnoreCase
//!@}

//!@doc Compares the first `n` chars of the two given strings (case-insensitive)
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/strncasecmp}
**
**	@returns
**	The first difference between chars encountered: `(str1[i] - str2[i])`,
**	or `0` if `str1` and `str2` have identical content.
*/
//!@{
t_sint					StringASCII_Compare_N_IgnoreCase(t_ascii const* str1, t_ascii const* str2, t_size n);
#define c_strnicmp		StringASCII_Compare_N_IgnoreCase
#define c_strncasecmp	StringASCII_Compare_N_IgnoreCase
//!@}

// TODO StringASCII_CompareUntil_Char()
// TODO StringASCII_CompareUntil_Charset()
// TODO StringASCII_CompareUntil_String()



//!@doc Check if the given `str` contains characters from `charset`
/*!
**	@nonstd
**
**	@returns
**	`TRUE` if the given string `str` contains at least one occurence
**	of any character found inside `charset`, otherwise returns `FALSE`.
*/
//!@{
t_bool				StringASCII_Has(t_ascii const* str, t_ascii const* charset);
#define c_strhas	StringASCII_Has
//!@}

//!@doc Check if the given `str` only contains characters from `charset`
/*!
**	@nonstd
**
**	@returns
**	`TRUE` if all the characters inside the given string `str`
**	are contained within the string `charset`, otherwise returns `FALSE`.
*/
//!@{
t_bool					StringASCII_HasOnly(t_ascii const* str, t_ascii const* charset);
#define c_strhasonly	StringASCII_HasOnly
//!@}



// TODO strspn()
// TODO strcspn()



//!@doc Count the total occurences of the given char `c` in the given string `str`
/*!
**	@nonstd
**
**	//TODO: change `c` type to t_ascii when the `String(ASCII|UTF8)` split is complete 
**
**	@returns
**	The amount of occurences of t_ascii `c` in the given string `str`.
*/
//!@{
t_size						StringASCII_Count_Char(t_ascii const* str, t_utf32 c);
#define c_strcount_char		StringASCII_Count_Char
//!@}

//!@doc Count the total occurences of chars from `charset` in the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The amount of occurences of chars in `charset` in the given string `str`.
*/
//!@{
t_size						StringASCII_Count_Charset(t_ascii const* str, t_ascii const* charset);
#define c_strcount_cset		StringASCII_Count_Charset
//!@}

//!@doc Count the total occurences of the given string `query` in the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The amount of occurences of `query` in the given string `str`.
*/
//!@{
t_size						StringASCII_Count_String(t_ascii const* str, t_ascii const* query);
#define c_strcount_str		StringASCII_Count_String
//!@}



/*
** ************************************************************************** *|
**                              String Searching                              *|
** ************************************************************************** *|
*/

//!@doc Finds the first occurence of the given char `c` inside the given string `str`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strchr} but with support for unicode if t_ascii is of type t_utf8
**
**	//TODO: change `c` type to t_ascii when the `String(ASCII|UTF8)` split is complete 
**
**	@returns
**	The first occurence of the given char `c` within `str`,
**	or `NULL` if no char matched.
*/
//!@{
t_ascii*			StringASCII_Find_Char(t_ascii const* str, t_utf32 c);
#define c_strchr	StringASCII_Find_Char
//!@}

//!@doc Finds the first occurence of any char in `charset` inside the given string `str`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strpbrk}
**
**	@returns
**	The first occurence of any char in the given `charset` within `str`,
**	or `NULL` if no char matched.
*/
//!@{
t_ascii*				StringASCII_Find_Charset(t_ascii const* str, t_ascii const* charset);
#define c_strpbrk		StringASCII_Find_Charset
#define c_strchrset		StringASCII_Find_Charset
//!@}

//!@doc Finds the first occurence of the string `query` inside the given string `str`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strstr}
**
**	@returns
**	The first occurence of the string `query` inside the given string `str`,
**	or `NULL` if nothing matched.
*/
//!@{
t_ascii*			StringASCII_Find_String(t_ascii const* str, t_ascii const* query);
#define c_strstr	StringASCII_Find_String
//!@}



//!@doc Finds the last occurence of the given char `c` inside the given string `str`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strrchr}
**
**	//TODO: change `c` type to t_ascii when the `String(ASCII|UTF8)` split is complete 
**
**	@returns
**	The last occurence of the given char `c` within `str`,
**	or `NULL` if no char matched.
*/
//!@{
t_ascii*							StringASCII_Find_R_Char(t_ascii const* str, t_utf32 c);
#define c_strrchr					StringASCII_Find_R_Char
#define StringASCII_FindLast_Char	StringASCII_Find_R_Char
//!@}

//!@doc Finds the last occurence of any char in `charset` inside the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The last occurence of any char in the given `charset` within `str`,
**	or `NULL` if no char matched.
*/
//!@{
t_ascii*								StringASCII_Find_R_Charset(t_ascii const* str, t_ascii const* charset);
#define c_strrpbrk						StringASCII_Find_R_Charset
#define c_strrchrset					StringASCII_Find_R_Charset
#define StringASCII_FindLast_Charset	StringASCII_Find_R_Charset
//!@}

//!@doc Finds the last occurence of the string `query` inside the given string `str`
/*!
**	@isostd{ext,https://linux.die.net/man/3/strrstr}
**
**	@returns
**	The last occurence of the string `query` inside the given string `str`,
**	or `NULL` if nothing matched.
*/
//!@{
t_ascii*								StringASCII_Find_R_String(t_ascii const* str, t_ascii const* query);
#define c_strrstr						StringASCII_Find_R_String
#define StringASCII_FindLast_String		StringASCII_Find_R_String
//!@}



//!@doc Finds the first occurence of the given char `c` inside the first `n` chars of the given string `str`
/*!
**	@nonstd
**
**	//TODO: change `c` type to t_ascii when the `String(ASCII|UTF8)` split is complete 
**
**	@returns
**	The first occurence of the given char `c` inside the given string `str`,
**	or `NULL` if no char matched. (checks only `n` chars in `str`).
*/
//!@{
t_ascii*			StringASCII_Find_N_Char(t_ascii const* str, t_utf32 c, t_size n);
#define c_strnchr	StringASCII_Find_N_Char
//!@}

//!@doc Finds the first occurence of any char in `charset` inside the first `n` chars of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The first occurence of any char from `charset` inside the given string `str`,
**	or `NULL` if no char matched. (checks only `n` chars in `str`).
*/
//!@{
t_ascii*				StringASCII_Find_N_Charset(t_ascii const* str, t_ascii const* charset, t_size n);
#define c_strnpbrk		StringASCII_Find_N_Charset
#define c_strnchrset	StringASCII_Find_N_Charset
//!@}

//!@doc Finds the first occurence of the string `query` inside the first `n` chars of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The first occurence of the string `query` inside the given string `str`,
**	or `NULL` if nothing matched. (checks only `n` chars in `str`).
*/
//!@{
t_ascii*			StringASCII_Find_N_String(t_ascii const* str, t_ascii const* query, t_size n);
#define c_strnstr	StringASCII_Find_N_String
//!@}



//!@doc Finds the first occurence of the given char `c` inside the given string `str`
/*!
**	@nonstd
**
**	//TODO: change `c` type to t_ascii when the `String(ASCII|UTF8)` split is complete 
**
**	@returns
**	The index of the first occurrence at which `c` is found in `str`,
**	or -1 if `c` does not exist in `str`.
*/
//!@{
t_sintmax			StringASCII_IndexOf_Char(t_ascii const* str, t_utf32 c);
#define c_strichr	StringASCII_IndexOf_Char
//!@}

//!@doc Finds the first occurence of any char in `charset` inside the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The index of the first occurrence at which `c` is found in `str`,
**	or -1 if `c` does not exist in `str`.
*/
//!@{
t_sintmax				StringASCII_IndexOf_Charset(t_ascii const* str, t_ascii const* charset);
#define c_stripbrk		StringASCII_IndexOf_Charset
#define c_strichrset	StringASCII_IndexOf_Charset
//!@}

//!@doc Finds the first occurence of the string `query` inside the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The index of the first occurrence at which `query` is found in `str`,
**	or -1 if `query` does not exist in str.
*/
//!@{
t_sintmax			StringASCII_IndexOf_String(t_ascii const* str, t_ascii const* query);
#define c_stristr	StringASCII_IndexOf_String
//!@}



//!@doc Finds the last occurence of the given char `c` inside the given string `str`
/*!
**	@nonstd
**
**	//TODO: change `c` type to t_ascii when the `String(ASCII|UTF8)` split is complete 
**
**	@returns
**	The last occurence of the given char `c` within `str`,
**	or `NULL` if no char matched.
*/
//!@{
t_sintmax								StringASCII_IndexOf_R_Char(t_ascii const* str, t_utf32 c);
#define c_strirchr						StringASCII_IndexOf_R_Char
#define StringASCII_LastIndexOf_Char	StringASCII_IndexOf_R_Char
//!@}

//!@doc Finds the last occurence of any char in `charset` inside the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The last occurence of any char in the given `charset` within `str`,
**	or `NULL` if no char matched.
*/
//!@{
t_sintmax								StringASCII_IndexOf_R_Charset(t_ascii const* str, t_ascii const* charset);
#define c_strirpbrk						StringASCII_IndexOf_R_Charset
#define c_strirchrset					StringASCII_IndexOf_R_Charset
#define StringASCII_LastIndexOf_Charset	StringASCII_IndexOf_R_Charset
//!@}

//!@doc Finds the last occurence of the string `query` inside the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The last occurence of the string `query` inside the given string `str`,
**	or `NULL` if nothing matched.
*/
//!@{
t_sintmax								StringASCII_IndexOf_R_String(t_ascii const* str, t_ascii const* query);
#define c_strirstr						StringASCII_IndexOf_R_String
#define StringASCII_LastIndexOf_String	StringASCII_IndexOf_R_String
//!@}



//!@doc Finds the first occurence of the given char `c` inside the first `n` chars of the given string `str`
/*!
**	@nonstd
**
**	//TODO: change `c` type to t_ascii when the `String(ASCII|UTF8)` split is complete 
**
**	@returns
**	The first occurence of the given char `c` within `str`,
**	or `NULL` if no char matched. (checks only `n` chars in `str`).
*/
//!@{
t_sintmax				StringASCII_IndexOf_N_Char(t_ascii const* str, t_utf32 c, t_size n);
#define c_strinchr		StringASCII_IndexOf_N_Char
//!@}

//!@doc Finds the first occurence of any char in `charset` inside the first `n` chars of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The first occurence of any char in the given `charset` within `str`,
**	or `NULL` if no char matched. (checks only `n` chars in `str`).
*/
//!@{
t_sintmax					StringASCII_IndexOf_N_Charset(t_ascii const* str, t_ascii const* charset, t_size n);
#define c_strinpbrk			StringASCII_IndexOf_N_Charset
#define c_strinchrset		StringASCII_IndexOf_N_Charset
//!@}

//!@doc Finds the first occurence of the string `query` inside the first `n` chars of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The first occurence of the string `query` inside the given string `str`,
**	or `NULL` if nothing matched. (checks only `n` chars in `str`).
*/
//!@{
t_sintmax				StringASCII_IndexOf_N_String(t_ascii const* str, t_ascii const* query, t_size n);
#define c_strinstr		StringASCII_IndexOf_N_String
//!@}



/*
** ************************************************************************** *|
**                              String Replacements                           *|
** ************************************************************************** *|
*/

//!@doc Removes all occurences of the given `query` string within the given string `str`.
/*!
**	@nonstd
**
**	@returns
**	A new null-terminated string which is a copy of `str`,
**	in which all occurences of the string `query` have been removed.
*/
//!@{
_MALLOC()
t_ascii*				StringASCII_Remove(t_ascii const* str, t_ascii const* query);
#define c_strremove		StringASCII_Remove
//!@}



//!@doc Replaces every occurence inside `str` of the given char `char_old` with `char_new`
/*!
**	@nonstd
**
**	@returns
**	A new null-terminated string which is a copy of `str`,
**	in which every occurence of an `old` char is replaced with a `new` char.
*/
//!@{
_MALLOC()
t_ascii*					StringASCII_Replace_Char(t_ascii const* str, t_ascii const char_old, t_ascii const char_new);
#define c_strrep_char		StringASCII_Replace_Char
//!@}

//!@doc Replaces every occurence inside `str` of any char in `charset_old` with the corresponding char in `charset_new`
/*!
**	@nonstd
**
**	@returns
**	A new null-terminated string which is a copy of `str`,
**	in which every char in the `old` charset is replaced by the
**	corresponding character in the `new` charset (at the same index).
*/
//!@{
_MALLOC()
t_ascii*					StringASCII_Replace_Charset(t_ascii const* str, t_ascii const* cset_old, t_ascii const* cset_new);
#define c_strrep_cset		StringASCII_Replace_Charset
//!@}

//!@doc Replaces every occurence inside `str` of the given string `str_old` with `str_new`
/*!
**	@nonstd
**
**	@see `stringarray.h` -> StringASCII_Split_String() for extra notes.
**
**	@returns
**	A new null-terminated string which is a copy of `str`,
**	in which every occurence of the string `old` is replaced with `new`.
*/
//!@{
_MALLOC()
t_ascii*					StringASCII_Replace_String(t_ascii const* str, t_ascii const* str_old, t_ascii const* str_new);
#define c_strrep_str		StringASCII_Replace_String
//!@}



/*
** ************************************************************************** *|
**                      String Concatenation Operations                       *|
** ************************************************************************** *|
*/

//!@doc Concatenates two strings into a new one
/*!
**	@nonstd
**
**	@returns
**	A new null-terminated string which is the concatenation of `str1` and `str2`.
*/
//!@{
_MALLOC()
t_ascii*				StringASCII_Concat(t_ascii const* str1, t_ascii const* str2);
#define c_strconcat		StringASCII_Concat
//!@}

//!@doc Concatenates two strings into a new one, deleting the right-hand string
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string which is the concatenation of `dest` and `src`.
**	Deletes `dest`, replacing it with the newly allocated result.
*/
//!@{
_MALLOC()
t_ascii*				StringASCII_Append(t_ascii* *dest, t_ascii const* src);
#define c_strappend		StringASCII_Append
//!@}

//!@doc Concatenates two strings into a new one, deleting the left-hand string
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string which is the concatenation of `src` and `dest`.
**	Deletes `dest`, replacing it with the newly allocated result.
*/
//!@{
_MALLOC()
t_ascii*				StringASCII_Prepend(t_ascii const* src, t_ascii* *dest);
#define c_strprepend	StringASCII_Prepend
//!@}

//!@doc Concatenates two strings into a new one, deleting both strings
/*!
**	@nonstd
**
**	Deletes both given strings (free and set to `NULL`).
**
**	@returns
**	A newly allocated string which is the concatenation of `*a_str1` and `*a_str2`.
*/
//!@{
_MALLOC()
t_ascii*				StringASCII_Merge(t_ascii* *a_str1, t_ascii* *a_str2);
#define c_strmerge		StringASCII_Merge
//!@}



//!@doc Concatenates the given set of strings `strarr`, putting the given separator string `sep` between each
/*!
**	@nonstd
**	
**	This function is the inverse operation of the StringASCII_Split() function.
**
**	@param	strarr	The array of strings to join together (terminated by a `NULL` pointer).
**	@param	sep		The separator string, which is to be added between eahc joined string.
**	@returns
**	A new null-terminated string which is the concatenation of all the strings contained in
**	the given string array `strarr`, with the `sep` separator string in-between each string.
*/
//!@{
_MALLOC()
t_ascii*				StringASCII_Join(t_ascii const** strarr, t_ascii const* sep);
#define c_strjoin		StringASCII_Join
//!@}



/*
** ************************************************************************** *|
**                           String In-Place Editing                          *|
** ************************************************************************** *|
*/

//!@doc Reallocates the given string `dest`, inserting the string `src` at the given `index`.
/*!
**	@nonstd
**
**	Inserts the string `src` at index `index` in `dest`; deletes `dest` and
**	replaces it with the result. Also returns the result.
*/
//!@{
t_ascii*						StringASCII_Insert_InPlace(t_ascii* *dest, t_ascii const* src, t_u32 index);
#define c_strinsert_inplace		StringASCII_Insert_InPlace
//!@}



//!@doc Replaces every occurence in `str` of `char_old` with `char_new`.
/*!
**	@nonstd
**
**	This function works somewhat like the shell command `tr`.
**	Substitutes every `char_old[i]` for `char_new[i]` in `str`.
**	TODO document edge-case behavior if `(char_old == '\0')`
*/
//!@{
void								StringASCII_Replace_Char_InPlace(t_ascii* str, t_ascii const char_old, t_ascii const char_new);
#define c_strrep_char_inplace		StringASCII_Replace_Char_InPlace
//!@}

//!@doc Replaces every occurence in `str` of any char in `charset_old` with the corresponding char in `charset_new`.
/*!
**	@nonstd
**
**	This function works somewhat like the shell command `tr`.
**	Substitutes every `charset_old[i]` for `charset_new[i]` in `str`.
**	Fails silently if `charset_old` and `charset_new` have different lengths,
**	or if a character is repeated in `charset_old` (only one image for every antecedent),
**	or if `charset_old` or `charset_new` are empty strings.
*/
//!@{
void								StringASCII_Replace_Charset_InPlace(t_ascii* str, t_ascii const* charset_old, t_ascii const* charset_new);
#define c_strrep_cset_inplace		StringASCII_Replace_Charset_InPlace
//!@}

//!@doc Replaces every occurence in `str` of `str_old` with `str_new`
/*!
**	@nonstd
**
**	@see `stringarray.h` -> StringASCII_Split_String() for extra notes.
*/
//!@{
void								StringASCII_Replace_String_InPlace(t_ascii* *a_str, t_ascii const* str_old, t_ascii const* str_new);
#define c_strrep_str_inplace		StringASCII_Replace_String_InPlace
//!@}



//!@doc Applies a custom `map` function to each char of the given string `*a_str`
/*!
**	@nonstd
**
**	Changes the content of `*a_str` by applying the given `map` function to each of its chars.
**	Deletes the string `*a_str`, and sets the result's in it instead.
**
**	@returns
**	The newly allocated string which replaces `*a_str`.
*/
//!@{
t_ascii*					StringASCII_Map_InPlace(t_ascii* *a_str, t_ascii (*map)(t_ascii));
#define c_strmap_inplace	StringASCII_Map_InPlace
//!@}



/*
** ************************************************************************** *|
**                        String Whitespace Operations                        *|
** ************************************************************************** *|
*/

//!@doc Trims any char from `charset` from both sides of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string from `str` in which all leading and trailing
**	characters present in `charset` have been removed.
*/
//!@{
_MALLOC()
t_ascii*				StringASCII_Trim(t_ascii const* str, t_ascii const* charset);
#define c_strtrim		StringASCII_Trim
//!@}

//!@doc Trims any char from `charset` from the left side of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string from `str` in which all leading
**	characters present in `charset` have been removed.
*/
//!@{
_MALLOC()
t_ascii*				StringASCII_Trim_L(t_ascii const* str, t_ascii const* charset);
#define c_strtriml		StringASCII_Trim_L
//!@}

//!@doc Trims any char from `charset` from the right side of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string from `str` in which all trailing
**	characters present in `charset` have been removed.
*/
//!@{
_MALLOC()
t_ascii*				StringASCII_Trim_R(t_ascii const* str, t_ascii const* charset);
#define c_strtrimr		StringASCII_Trim_R
//!@}



//!@doc Pads the given `str` to be `length` chars long, adding `c` chars on both sides, if needed
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string from `str` which is `length` characters long,
**	by padding it with `c` chars on both sides,
**	if the desired `length` is larger than `str`.
*/
//!@{
_MALLOC()
t_ascii*				StringASCII_Pad(t_ascii const* str, t_ascii c, t_size length);
#define c_strpad		StringASCII_Pad
//!@}

//!@doc Pads the given `str` to be `length` chars long, adding `c` chars on the left side, if needed
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string from `str` which is `length` characters long,
**	by padding it with `c` chars on its left side,
**	if the desired `length` is larger than `str`.
*/
//!@{
_MALLOC()
t_ascii*				StringASCII_Pad_L(t_ascii const* str, t_ascii c, t_size length);
#define c_strpadl		StringASCII_Pad_L
//!@}

//!@doc Pads the given `str` to be `length` chars long, adding `c` chars on the right side, if needed
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string from `str` which is `length` characters long,
**	by padding it with `c` chars on its right side,
**	if the desired `length` is larger than `str`.
*/
//!@{
_MALLOC()
t_ascii*				StringASCII_Pad_R(t_ascii const* str, t_ascii c, t_size length);
#define c_strpadr		StringASCII_Pad_R
//!@}



/*
** ************************************************************************** *|
**                          Other String Operations                           *|
** ************************************************************************** *|
*/

#define StringASCII_Print	StringASCII_ToASCIIEscapedBuf

//! Creates a new string from `str`, replacing special characters with ASCII escape-sequences
/*!
**	@nonstd
**
**	Returns a new null-terminated string where every non-printable or non-ascii
**	character of `str` is replaced by either its `normal` escape sequence (if 
**	available) or encodes the character with either a '\xFF'-type '\uFFFF'-type
**	or a '\UFFFFFFFF'-type escape sequence if no alias sequence exists (like "\n").
**	Here is the list of characters which will be escaped by default:
**	- `\\`	`\` (a single backslash, escaping the escape character)
**	- `\'`	Apostrophe
**	- `\"`	Double quotes
**	- `\/`	Forward Slash
**	- `\a`	Bell/Alert/Audible
**	- `\b`	Backspace
**	- `\t`	Tab character
**	- `\n`	Line feed
**	- `\v`	Vertical tab
**	- `\f`	Form-feed
**	- `\r`	Carriage return
**	- `\e`	Escape
**	- `\x??`		Byte value, written as hexadecimal
**	- `\u????`		UTF-8 multi-byte character, written as a hexadecimal code point (Unicode: U+????)
**	- `\U????????`	UTF-8 multi-byte character, written as a hexadecimal code point (Unicode: U+????????)
*/
_MALLOC()
t_ascii*				StringASCII_ToASCIIEscaped(t_ascii const* str);
#define c_strtoasciiesc	StringASCII_ToASCIIEscaped


//! Equivalent of `StringASCII_ToASCIIEscaped` but writes in the given `dest` buffer.
/*!
**	@nonstd
**
**	One can call with NULL `dest` to get the size it would write
**
**	@returns
**	The amount of byte written to `dest`, or that would have been written to `dest` if `dest` wasn't NULL
*/
t_size					StringASCII_ToASCIIEscapedBuf(t_ascii *dest, size_t max_writelen, t_ascii const* str);

//! Creates a new string from `str`, replacing special characters with JSON-like escape-sequences
/*!
**	@nonstd
**
**	Returns a new null-terminated json-compliant string.
**	Non-pritable characters are escaped with a `\uFFFF` format except for these escape sequences:
**	- `\\`	`\` (a single backslash, escaping the escape character)
**	- `\"`	Double quotes
**	- `\b`	Backspace
**	- `\t`	Tab character
**	- `\n`	Line feed
**	- `\f`	Form-feed
**	- `\r`	Carriage return
*/
_MALLOC()
t_ascii*				StringASCII_ToJsonEscaped(t_ascii const* str);
#define c_strtojsonesc	StringASCII_ToJsonEscaped

//! Equivalent of `StringASCII_ToJsonEscaped` but writes in the given `dest` buffer.
/*!
**	@nonstd
**
**	One can call with NULL `dest` to get the size it would write
**
**	@returns
**	The amount of byte written to `dest`, or that would have been written to `dest` if `dest` wasn't NULL
*/
t_size					StringASCII_ToJsonEscapedBuf(t_ascii *dest, size_t max_writelen, t_ascii const* str);


// mallocs and return a new string
// note: force_encoding_for can be NULL. char_encoder maybe NULL but will cause a fail if we need to encode a char

//! Creates a new string from `str` escaping any relevant characters
/*!
**	@nonstd
**
**	Returns a new string where every character is escaped according to the parameters:
**
**	Every character in `charset` or for which `force_encoding_for` returns `TRUE` will be escaped.
**	If the character is in `charset` and it's corresponding alias (the value of `aliases` at the 
**	same index) is not `NULL`, then the alias will be written.
**	Otherwise, the character will be encoded with `char_encoder`
**
**	KNOWN ISSUE: Does not work with empty string as long as `SIZE_ERROR` macro is `0`.        DZ_ON_REFACTOR_OF_SIZE_ERROR: delete this line, it'll have solved the issue
**
**	@param	str					The input string whose content will be copied and escaped
**	@param	charset				String containing all characters to escape by an alias
**	@param	aliases				String array containing the alias of every character of `charset`.
**									A character in `charset` corresponds to an alias in `aliases` by index.
**									If an alias is `NULL`, then the character will be encoded instead
**									The array doesn't have to be null-terminated, but needs to be of same size
**									as `charset`
**	@param	force_encoding_for	Predicate that can force a given character to be escaped by returning `TRUE`.
**									If `force_encoding_for` is `NULL`, only character of `charset` that don't
**									have an alias will be encoded.
**	@param	char_encoder		Function taking care of encoding a character.
**									If `NULL`, the function will fail if it ever needs to encode a character,
**									but will succeed if it never needs to do so.
**									@see f_char_encoder
**
**	@returns
**	The new alloc'd string containing the escaped version of `str`, or
**	NULL in case of error
*/
_MALLOC()
t_ascii*	StringASCII_ToEscaped(
		t_ascii const* str,
		t_ascii const* charset,
		t_ascii const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder);

#define c_strtoesc	StringASCII_ToEscaped

//! Exhaustive version of `StringASCII_ToEscaped`
/*
**	@see StringASCII_ToEscaped, only additional parameters are documented here
**
**	All 'out parameters` are optional and will be initialized even if the function fails
**
**	@params	out_len			Used to return the length of returned string
**								`SIZE_ERROR` in case of failure
**	@params	out_readlen		Used to return the length read from input string. Useful when max_writelen is given
**								Even if the function fails, represent the number of byte that could successfully 
**								be read before the error. `str + out_readlen` will always point to the first byte
**								of a multi-byte sequence
**	@params	max_resultlen	Maximum length of string to return (excluding final '\0'). No limit if set to `SIZE_ERROR`.
**								The function takes care of not reaching `max_writelen` in the middle of
**								an alias or encoded char by realizing there is not enough space and stopping
**								before writting it.
**								This means that the returned string may be shorter than `max_writelen` even
**								when it was limited by it
*/
_MALLOC()
t_ascii*	StringASCII_ToEscaped_e(
		t_size *out_len,
		t_size *out_readlen,
		t_size max_resultlen,
		t_ascii const* str,
		t_ascii const* charset,
		t_ascii const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder);

#define c_strtoesc_e	StringASCII_ToEscaped_e

//! Same as `StringASCII_ToEscaped` except it will write the escaped string directly to `dest`
/*
**	@see StringASCII_ToEscaped, only additional parameters are documented here
**
**	If `dest` is NULL, nothing is written and the number of bytes that would be written is returned.
**	Even in case of error, `dest` will be null-terminated and will be filled whatever was successfully
**	written before the error
**
**	CAUTION: unlike the non-"Buf" variant, `max_writelen` is the number of bytes allowed to be written INCLUDING final '\0'
**
**	@param	dest			The buffer to write the escaped string to, if not `NULL`
**	@params	max_writelen	Maximum length of string to return (including final '\0'). No limit if set to `SIZE_ERROR`.
**								The function takes care of not reaching `max_writelen` in the middle of
**								an alias or encoded char by realizing there is not enough space and stopping
**								before writting it.
**								This means that the returned string may be shorter than `max_writelen` even
**								when it was limited by it
**	@returns
**	The number of bytes written to `dest` or that would have been written to `dest` if it was not `NULL`, or
**	SIZE_ERROR in case of error
*/
t_size StringASCII_ToEscapedBuf(
		t_ascii *dest,
		size_t max_writelen,
		t_ascii const* str,
		t_ascii const* charset,
		t_ascii const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder);

//! Exhaustive version of `StringASCII_ToEscapedBuf`
/*
**	@see StringASCII_ToEscapedBuf
**
**	All 'out parameters` are optional and will be initialized even if the function fails
**
**	CAUTION: unlike the non-"Buf" variant, `max_writlen` is the number of bytes allowed to be written INCLUDING final '\0'
**
**	@params	out_readlen		Used to return the length read from input string. Useful when max_writelen is given
**								Even if the function fails, represent the number of byte that could successfully 
**								be read before the error. `str + out_readlen` will always point to the first byte
**								of a multi-byte sequence
*/
t_size StringASCII_ToEscapedBuf_e(
		t_ascii *dest,
		t_size *out_readlen,
		size_t max_writelen,
		t_ascii const* str,
		t_ascii const* charset,
		t_ascii const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder);

//!@}



//! Creates a new string from `str`, replacing escape-sequences with their corresponding char value
/*!
**	@nonstd
**
**	Inverse of `StringASCII_ToASCIIEscaped`
**
**	Returns a new null-terminated string where every valid backslash escape sequence
**	is converted to its corresponding string byte.
**	Here is the list of character escape sequences which will be properly parsed:
**	- `\\`	`\` (a single backslash, escaping the escape character)
**	- `\'`	Apostrophe
**	- `\"`	Double quotes
**	- `\a`	Bell/Alert/Audible
**	- `\b`	Backspace
**	- `\t`	Tab character
**	- `\n`	Line feed
**	- `\v`	Vertical tab
**	- `\f`	Form-feed
**	- `\r`	Carriage return
**	- `\e`	Escape
**	- `\x??`		Byte value, written as hexadecimal
**	- `\u????`		UTF-8 multi-byte character, written as a hexadecimal code point (Unicode: U+????)
**	- `\U????????`	UTF-8 multi-byte character, written as a hexadecimal code point (Unicode: U+????????)
**	Any other backslash-ed character will simply resolve to itself (ie: removing the preceding backslash)
*/
//!@{

/*!@doc
**	@param	dest		The destination string
**	@param	str			The string to duplicate, while resolving all escape-sequences to their corresponding char
**	@param	n			The maximum amount of characters to parse (infinite if `0` is given)
**	@param	any_escape	If `TRUE`, every backslash will be understood as an escape character
**						(ie: any escape sequance will function, with any char after the `'\'`)
**	@returns
**	The amount of characters parsed from the given `str`.
*/
//!@{
t_size					StringASCII_Parse(t_ascii* *dest, t_ascii const* str, t_size n, t_bool any_escape);
#define c_strparse		StringASCII_Parse
//!@}

//!@doc
/*!
**	@param	str			The string to duplicate, while resolving all escape-sequences to their corresponding char
**	@param	any_escape	If `TRUE`, every backslash will be understood as an escape character. 
**						Every backslashed character will be resolved to either the character this known escape 
**						sequence represents, or simply character if this escape sequence is not known (effectively
**						removing the backslash)
**
**	@returns
**	A newly allocated modified copy of the given `str` (can be smaller than `str`),
**	with any escape-sequences transformed into their target character value.
*/
//!@{
_MALLOC()
t_ascii*							StringASCII_FromEscape(t_ascii const* str, t_bool any_escape);
#define c_esctostr					StringASCII_FromEscape
#define StringASCII_Decode			StringASCII_FromEscape
#define StringASCII_FromPrintable	StringASCII_FromEscape
//!@}

//!@}



//!@doc Get an inverted version of the given string `str`
/*!
**	@nonstd
**
**	Does not support utf8 characters
**
**	@returns
**	A newly allocated string which is a copy of the given string `str`,
**	but in reverse order (except for the \0 terminator, obviously).
*/
//!@{
_MALLOC()
t_ascii*			StringASCII_Reverse(t_ascii const* str);
#define c_strrev	StringASCII_Reverse
//!@}



//!@doc Get a new string from `dest`, with `src` inserted at the given `index`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string from the given string `dest`,
**	in which the string `src` has been inserted at the given `index`.
*/
//!@{
_MALLOC()
t_ascii*				StringASCII_Insert(t_ascii const* dest, t_ascii const* src, t_size index);
#define c_strinsert		StringASCII_Insert
//!@}



//!@doc Get a subsection which is `n` chars long of the given string `str`, starting at `index`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string which is a subsection of `str`,
**	starting at position `index` and copying `n` characters.
*/
//!@{
_MALLOC()
t_ascii*			StringASCII_Sub(t_ascii const* str, t_size index, t_size n);
#define c_strsub	StringASCII_Sub
//!@}



/*
** ************************************************************************** *|
**                           Functional Operations                            *|
** ************************************************************************** *|
*/

//!@doc Calls a custom function `f` for each character of the given string `str`
/*!
**	@nonstd
**
**	Iterates upon each character of the given string `str`,
**	applying the given function `f` to each of its characters.
*/
//!@{
void					StringASCII_Iterate(t_ascii* str, void (*f)(t_ascii* c));
#define c_striter		StringASCII_Iterate
//!@}

//!@doc Calls a custom function `f` for each character of the given string `str`
/*!
**	@nonstd
**
**	Iterates upon each character of the given string `str`, (with index information)
**	applying the function `f` to each of its chars.
*/
//!@{
void					StringASCII_Iterate_I(t_ascii* str, void (*f)(t_ascii* c, t_size index));
#define c_striiter		StringASCII_Iterate_I
//!@}



//!@doc Creates a new string with each character mapped to another, using the custom function `map`
/*!
**	@nonstd
**
**	@returns
**	A new string by iterating upon the string `str`,
**	applying the function `map` to each of its characters.
*/
//!@{
_MALLOC()
t_ascii*				StringASCII_Map(t_ascii const* str, t_ascii (*map)(t_ascii c));
#define c_strmap		StringASCII_Map
//!@}

//!@doc Creates a new string with each character mapped to another, using the custom function `map`
/*!
**	@nonstd
**
**	@returns
**	A new string by iterating upon the string `str`, (with index information)
**	applying the function `map` to each of its characters.
*/
//!@{
_MALLOC()
t_ascii*				StringASCII_Map_I(t_ascii const* str, t_ascii (*map)(t_ascii c, t_size index));
#define c_strimap		StringASCII_Map_I
//!@}



//!@doc Creates a new string from `str`, only keeping chars when the custom function `filter` returns `TRUE`
/*!
**	@nonstd
**
**	@returns
**	A new null-terminated string by iterating upon the string `str`,
**	removing any chars for which the given `filter` function returns `FALSE`.
*/
//!@{
_MALLOC()
t_ascii*				StringASCII_Filter(t_ascii const* str, t_bool (*filter)(t_ascii c));
#define c_strfilter		StringASCII_Filter
//!@}

//!@doc Creates a new string from `str`, only keeping chars when the custom function `filter` returns `TRUE`
/*!
**	@nonstd
**
**	@returns
**	A new string by iterating upon the string `str`, (with index information)
**	removing any chars for which the given `filter` function returns `FALSE`.
*/
//!@{
_MALLOC()
t_ascii*				StringASCII_Filter_I(t_ascii const* str, t_bool (*filter)(t_ascii c, t_size index));
#define c_strifilter	StringASCII_Filter_I
//!@}



/*
** ************************************************************************** *|
**                    Essential builtins (for compatibility)                  *|
** ************************************************************************** *|
*/

#ifdef __IOS__ // TODO smarter check here

inline
int		strcmp(char const* str1, char const* str2)
{ return (StringASCII_Compare(str1, str2)); }

inline
int		strncmp(char const* str1, char const* str2, size_t n)
{ return (StringASCII_Compare_N(str1, str2, n)); }

inline
char*	strchr(char const* str, int c)
{ return (StringASCII_Find_Char(str, c)); }

#endif



/*! @endgroup */
HEADER_END
#endif
