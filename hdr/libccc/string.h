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
/*!@group{libccc_string}
** @{
**	This header defines the common standard string (t_char*) manipulation functions.
**
**	@isostd{C,https://en.cppreference.com/w/c/string/byte#String_manipulation}
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"

#include "libccc/format.h" // TODO remove this include ?

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/* TODO function pointers
**	typedef void	(*f_string_iterate)		(t_char* )
**	typedef void	(*f_string_iterate_i)	(unsigned int, t_char* )
**	typedef t_char	(*f_string_map)			(t_char)
**	typedef t_char	(*f_string_map_i)		(unsigned int, t_char)
*/



/*
** ************************************************************************** *|
**                          Basic String Operations                           *|
** ************************************************************************** *|
*/

//! Returns a new string which is `n + 1` bytes long (to account for the null-terminator).
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
_MALLOC()
t_char*				String_New(t_size n);
#define c_strnew	String_New //!< @alias{String_New}

//! Returns a newly allocated region of `c`-filled memory, which is `n + 1` bytes long.
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
_MALLOC()
t_char*				String_New_C(t_size n, t_char c);
#define c_strcnew	String_New_C //!< @alias{String_New_C}



// TODO String_Free()

//! Deletes (deallocates) the string pointed to by `*a_str`, and sets the pointer to `NULL`.
/*!
**	@nonstd
*/
void				String_Delete(t_char* *a_str);
#define c_strdel	String_Delete //!< @alias{String_Delete}



//! Duplicates the given `str`
/*!
**	@isostd{C23,https://en.cppreference.com/w/c/string/byte/strdup}
**
**	@returns
**	A newly allocated string which is a copy of the given string `str`,
**	or `NULL` if the required memory could not be allocated.
*/
_MALLOC()
t_char*				String_Duplicate(t_char const* str);
#define c_strdup	String_Duplicate //!< @alias{String_Duplicate}

//! Duplicates the given `str`, the copy being at most `n` chars long
/*!
**	@isostd{C23,https://en.cppreference.com/w/c/string/byte/strndup}
**
**	@returns
**	A newly allocated string which is a copy of the given string `str`,
**	or `NULL` if the required memory could not be allocated,
**	copying at most `n` characters.
*/
_MALLOC()
t_char*				String_Duplicate_N(t_char const* str, t_size n);
#define c_strndup	String_Duplicate_N //!< @alias{String_Duplicate_N}

//! Duplicates the given `str`, the copy stops at the first occurence of `c`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string which is a copy of the given string `str`,
**	or `NULL` if the required memory could not be allocated,
**	stopping at the first occurence of the given char `c`.
*/
_MALLOC()
t_char*				String_Duplicate_Char(t_char const* str, t_char const c);
#define c_strchrdup	String_Duplicate_Char //!< @alias{String_Duplicate_Char}

//! Duplicates the given `str`, the copy stops at the first occurence of any char in `charset`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string which is a copy of the given string `str`,
**	or `NULL` if the required memory could not be allocated,
**	stopping at the first occurence of any char contained within the given `charset`.
*/
_MALLOC()
t_char*				String_Duplicate_Charset(t_char const* str, t_char const* charset);
#define c_strcstdup	String_Duplicate_Charset //!< @alias{String_Duplicate_Charset}

//! Duplicates the given `str`, the copy stops at the first occurence of any char in `string`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string which is a copy of the given string `str`,
**	or `NULL` if the required memory could not be allocated,
**	stopping at the first occurence of the given string `target`.
*/
_MALLOC()
t_char*				String_Duplicate_String(t_char const* str, t_char const* target);
#define c_strstrdup	String_Duplicate_String //!< @alias{String_Duplicate_String}



//! Clears the given string `str`, setting each character of `str` to `'\0'`.
/*!
**	@nonstd
*/
void				String_Clear(t_char* str);
#define c_strclr	String_Clear //!< @alias{String_Clear}

//! Sets every char of the given string `str` to `c`, only stopping upon reading a `'\0'` null-terminator.
/*!
**	@nonstd
**
**	Fills the given string `str` with the character `c`
**
**	@param	str	The string to fill
**	@param	c	The character value to fill with
*/
void				String_Set(t_char* str, t_char c);
#define c_strset	String_Set //!< @alias{String_Set}

// TODO strnset() String_Set_N



//! Copies the given string `str` into `dest`, and returns `dest`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strcpy}
**
**	Copies the given string `src` into `dest` (null-terminator included)
**
**	@returns
**	`dest` (no allocation is performed).
*/
t_char*				String_Copy(t_char* dest, t_char const* src);
#define c_strcpy	String_Copy //!< @alias{String_Copy}

//! Copies the first `n` characters of the given string `src` into `dest`, and returns `dest`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strncpy}
**
**	Copies the first `n` characters of the given string `src` into `dest`
**
**	@returns
**	`dest` (no allocation is performed).
*/
t_char*				String_Copy_N(t_char* dest, t_char const* src, t_size n);
#define c_strncpy	String_Copy_N //!< @alias{String_Copy_N}

//! Copies the given string `src` into `dest`, null-terminating the result and returning its length
/*!
**	@isostd{BSD,https://linux.die.net/man/3/strlcpy}
**
**	Copies the given string `src` into `dest`, null-terminating the result.
**	The `'\0'` null-terminator is placed at the position: `(dest + size - 1)`.
**
**	@returns
**	The resulting size of `dest`.
*/
t_size				String_Copy_L(t_char* dest, t_char const* src, t_size size);
#define c_strlcpy	String_Copy_L //!< @alias{String_Copy_L}



//! Concatenates the given string `src` to the end of `dest`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strcat}
**
**	Concatenates the given string `src` to the end of `dest` (removing dest's null-terminator).
**
**	@returns
**	`dest` (no allocation is performed).
*/
t_char*				String_Concat(t_char* dest, t_char const* src);
#define c_strcat	String_Concat //!< @alias{String_Concat}

//! Concatenates the given string `src` to the end of `dest`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strncat}
**
**	Concatenates the first `n` characters of the given string `src` to the end of `dest`.
**
**	@returns
**	`dest` (no allocation is performed).
*/
t_char*				String_Concat_N(t_char* dest, t_char const* src, t_size n);
#define c_strncat	String_Concat_N //!< @alias{String_Concat_N}

//! Concatenates the given string `src` to the end of `dest`
/*!
**	@isostd{BSD,https://linux.die.net/man/3/strlcat}
**
**	Concatenates characters of the given string `src` to the end of `dest`, null-terminating the result.
**	The `'\0'` null-terminator is placed at the position: `(dest + size - 1)`.
**
**	@returns
**	The resulting size of `dest`.
*/
t_size				String_Concat_L(t_char* dest, t_char const* src, t_size size);
#define c_strlcat	String_Concat_L //!< @alias{String_Concat_L}



/*
** ************************************************************************** *|
**                                String Checks                               *|
** ************************************************************************** *|
*/

//! Get the length (in bytes) of a string
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strlen}
**
**	@returns
**	The length of the given null-terminated string `str`.
*/
t_size				String_Length(t_char const* str);
#define c_strlen	String_Length //!< @alias{String_Length}

// TODO strnlen() String_Length_N



//!	Checks whether the two given strings match
/*!
**	@nonstd
**
**	@returns
**	`TRUE` if the two given strings have identical content,
**	`FALSE` otherwise
*/
t_bool					String_Equals(t_char const* str1, t_char const* str2);
#define c_strequ		String_Equals //!< @alias{String_Equals}

//!	Checks whether the first `n` chars of the two given strings match
/*!
**	@nonstd
**
**	@returns
**	`TRUE` if the first `n` chars of the two given strings are identical,
**	`FALSE` otherwise
*/
t_bool					String_Equals_N(t_char const* str1, t_char const* str2, t_size n);
#define c_strnequ		String_Equals_N //!< @alias{String_Equals_N}

//!	Checks whether the two given strings match (case-insensitive)
/*!
**	@nonstd
**
**	@returns
**	`TRUE` if the two given strings have identical content (case-insensitive),
**	`FALSE` otherwise
*/
t_bool					String_Equals_IgnoreCase(t_char const* str1, t_char const* str2);
#define c_striequ		String_Equals_IgnoreCase //!< @alias{String_Equals_IgnoreCase}
#define c_strcaseequ	String_Equals_IgnoreCase //!< @alias{String_Equals_IgnoreCase}

//!	Checks whether the first `n` chars of the two given strings match (case-insensitive)
/*!
**	@nonstd
**
**	@returns
**	`TRUE` if the first `n` chars of the two given strings match (case-insensitive),
**	`FALSE` otherwise
*/
t_bool					String_Equals_N_IgnoreCase(t_char const* str1, t_char const* str2, t_size n);
#define c_strniequ		String_Equals_N_IgnoreCase //!< @alias{String_Equals_N_IgnoreCase}
#define c_strncaseequ	String_Equals_N_IgnoreCase //!< @alias{String_Equals_N_IgnoreCase}

// TODO String_EqualsUntil_Char()
// TODO String_EqualsUntil_Charset()
// TODO String_EqualsUntil_String()



//! Compares the content of the two given strings
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strcmp}
**
**	@returns
**	The first difference between chars encountered: `(str1[i] - str2[i])`,
**	or `0` if `str1` and `str2` have identical content.
*/
t_sint					String_Compare(t_char const* str1, t_char const* str2);
#define c_strcmp		String_Compare //!< @alias{String_Compare}

//! Compares the first `n` chars of the two given strings
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strncmp}
**
**	@returns
**	The first difference between chars encountered: `(str1[i] - str2[i])`,
**	or `0` if `str1` and `str2` have identical content.
*/
t_sint					String_Compare_N(t_char const* str1, t_char const* str2, t_size n);
#define c_strncmp		String_Compare_N //!< @alias{String_Compare_N}

//! Compares the two given strings (case-insensitive)
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/strcasecmp}
**
**	@returns
**	The first difference between chars encountered: `(str1[i] - str2[i])`,
**	or `0` if `str1` and `str2` have identical content.
*/
t_sint					String_Compare_IgnoreCase(t_char const* str1, t_char const* str2);
#define c_stricmp		String_Compare_IgnoreCase //!< @alias{String_Compare_IgnoreCase}
#define c_strcasecmp	String_Compare_IgnoreCase //!< @alias{String_Compare_IgnoreCase}

//! Compares the first `n` chars of the two given strings (case-insensitive)
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/strncasecmp}
**
**	@returns
**	The first difference between chars encountered: `(str1[i] - str2[i])`,
**	or `0` if `str1` and `str2` have identical content.
*/
t_sint					String_Compare_N_IgnoreCase(t_char const* str1, t_char const* str2, t_size n);
#define c_strnicmp		String_Compare_N_IgnoreCase //!< @alias{String_Compare_N_IgnoreCase}
#define c_strncasecmp	String_Compare_N_IgnoreCase //!< @alias{String_Compare_N_IgnoreCase}

// TODO String_CompareUntil_Char()
// TODO String_CompareUntil_Charset()
// TODO String_CompareUntil_String()



//! Check if the given `str` contains characters from `charset`
/*!
**	@nonstd
**
**	@returns
**	`TRUE` if the given string `str` contains at least one occurence
**	of any character found inside `charset`, otherwise returns `FALSE`.
*/
t_bool						String_Has(t_char const* str, t_char const* charset);
#define c_strhas			String_Has //!< @alias{String_Has}

//! Check if the given `str` only contains characters from `charset`
/*!
**	@nonstd
**
**	@returns
**	`TRUE` if all the characters inside the given string `str`
**	are contained within the string `charset`, otherwise returns `FALSE`.
*/
t_bool						String_HasOnly(t_char const* str, t_char const* charset);
#define c_strhasonly		String_HasOnly //!< @alias{String_HasOnly}



// TODO strspn()
// TODO strcspn()



//! Count the total occurences of the given char `c` in the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The amount of occurences of t_char `c` in the given string `str`.
*/
t_size						String_Count_Char(t_char const* str, t_char c);
#define c_strcount_chr		String_Count_Char //!< @alias{String_Count_Char}

//! Count the total occurences of chars from `charset` in the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The amount of occurences of chars in `charset` in the given string `str`.
*/
t_size						String_Count_Charset(t_char const* str, t_char const* charset);
#define c_strcount_cset	S	tring_Count_Charset //!< @alias{String_Count_Charset}

//! Count the total occurences of the given string `query` in the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The amount of occurences of `query` in the given string `str`.
*/
t_size						String_Count_String(t_char const* str, t_char const* query);
#define c_strcount_str		String_Count_String //!< @alias{String_Count_String}



/*
** ************************************************************************** *|
**                              String Searching                              *|
** ************************************************************************** *|
*/

//! Finds the first occurence of the given char `c` inside the given string `str`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strchr}
**
**	@returns
**	The first occurence of the given char `c` within `str`,
**	or `NULL` if no char matched.
*/
t_char*							String_Find_Char(t_char const* str, t_char c);
#define c_strchr				String_Find_Char //!< @alias{String_Find_Char}

//! Finds the first occurence of any char in `charset` inside the given string `str`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strpbrk}
**
**	@returns
**	The first occurence of any char in the given `charset` within `str`,
**	or `NULL` if no char matched.
*/
t_char*							String_Find_Charset(t_char const* str, t_char const* charset);
#define c_strpbrk				String_Find_Charset //!< @alias{String_Find_Charset}
#define c_strchrset				String_Find_Charset //!< @alias{String_Find_Charset}

//! Finds the first occurence of the string `query` inside the given string `str`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strstr}
**
**	@returns
**	The first occurence of the string `query` inside the given string `str`,
**	or `NULL` if nothing matched.
*/
t_char*							String_Find_String(t_char const* str, t_char const* query);
#define c_strstr				String_Find_String //!< @alias{String_Find_String}



//! Finds the last occurence of the given char `c` inside the given string `str`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strrchr}
**
**	@returns
**	The last occurence of the given char `c` within `str`,
**	or `NULL` if no char matched.
*/
t_char*							String_Find_R_Char(t_char const* str, t_char c);
#define c_strrchr				String_Find_R_Char //!< @alias{String_Find_R_Char}
#define String_FindLast_Char	String_Find_R_Char //!< @alias{String_Find_R_Char}

//! Finds the last occurence of any char in `charset` inside the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The last occurence of any char in the given `charset` within `str`,
**	or `NULL` if no char matched.
*/
t_char*							String_Find_R_Charset(t_char const* str, t_char const* charset);
#define c_strrpbrk				String_Find_R_Charset //!< @alias{String_Find_R_Charset}
#define c_strrchrset			String_Find_R_Charset //!< @alias{String_Find_R_Charset}
#define String_FindLast_Charset	String_Find_R_Charset //!< @alias{String_Find_R_Charset}

//! Finds the last occurence of the string `query` inside the given string `str`
/*!
**	@isostd{ext,https://linux.die.net/man/3/strrstr}
**
**	@returns
**	The last occurence of the string `query` inside the given string `str`,
**	or `NULL` if nothing matched.
*/
t_char*							String_Find_R_String(t_char const* str, t_char const* query);
#define c_strrstr				String_Find_R_String //!< @alias{String_Find_R_String}
#define String_FindLast_String	String_Find_R_String //!< @alias{String_Find_R_String}



//! Finds the first occurence of the given char `c` inside the first `n` chars of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The first occurence of the given char `c` inside the given string `str`,
**	or `NULL` if no char matched. (checks only `n` chars in `str`).
*/
t_char*							String_Find_N_Char(t_char const* str, t_char c, t_size n);
#define c_strnchr				String_Find_N_Char //!< @alias{String_Find_N_Char}

//! Finds the first occurence of any char in `charset` inside the first `n` chars of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The first occurence of any char from `charset` inside the given string `str`,
**	or `NULL` if no char matched. (checks only `n` chars in `str`).
*/
t_char*							String_Find_N_Charset(t_char const* str, t_char const* charset, t_size n);
#define c_strnpbrk				String_Find_N_Charset //!< @alias{String_Find_N_Charset}
#define c_strnchrset			String_Find_N_Charset //!< @alias{String_Find_N_Charset}

//! Finds the first occurence of the string `query` inside the first `n` chars of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The first occurence of the string `query` inside the given string `str`,
**	or `NULL` if nothing matched. (checks only `n` chars in `str`).
*/
t_char*							String_Find_N_String(t_char const* str, t_char const* query, t_size n);
#define c_strnstr				String_Find_N_String //!< @alias{String_Find_N_String}



//! Finds the first occurence of the given char `c` inside the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The index of the first occurrence at which `c` is found in `str`,
**	or -1 if `c` does not exist in `str`.
*/
t_sintmax							String_IndexOf_Char(t_char const* str, t_char c);
#define c_strichr					String_IndexOf_Char //!< @alias{String_IndexOf_Char}

//! Finds the first occurence of any char in `charset` inside the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The index of the first occurrence at which `c` is found in `str`,
**	or -1 if `c` does not exist in `str`.
*/
t_sintmax							String_IndexOf_Charset(t_char const* str, t_char const* charset);
#define c_stripbrk					String_IndexOf_Charset //!< @alias{String_IndexOf_Charset}
#define c_strichrset				String_IndexOf_Charset //!< @alias{String_IndexOf_Charset}

//! Finds the first occurence of the string `query` inside the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The index of the first occurrence at which `query` is found in `str`,
**	or -1 if `query` does not exist in str.
*/
t_sintmax							String_IndexOf_String(t_char const* str, t_char const* query);
#define c_stristr					String_IndexOf_String //!< @alias{String_IndexOf_String}



//! Finds the last occurence of the given char `c` inside the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The last occurence of the given char `c` within `str`,
**	or `NULL` if no char matched.
*/
t_sintmax							String_IndexOf_R_Char(t_char const* str, t_char c);
#define c_strirchr					String_IndexOf_R_Char //!< @alias{String_IndexOf_R_Char}
#define String_LastIndexOf_Char		String_IndexOf_R_Char //!< @alias{String_IndexOf_R_Char}

//! Finds the last occurence of any char in `charset` inside the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The last occurence of any char in the given `charset` within `str`,
**	or `NULL` if no char matched.
*/
t_sintmax							String_IndexOf_R_Charset(t_char const* str, t_char const* charset);
#define c_strirpbrk					String_IndexOf_R_Charset //!< @alias{String_IndexOf_R_Charset}
#define c_strirchrset				String_IndexOf_R_Charset //!< @alias{String_IndexOf_R_Charset}
#define String_LastIndexOf_Charset	String_IndexOf_R_Charset //!< @alias{String_IndexOf_R_Charset}

//! Finds the last occurence of the string `query` inside the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The last occurence of the string `query` inside the given string `str`,
**	or `NULL` if nothing matched.
*/
t_sintmax							String_IndexOf_R_String(t_char const* str, t_char const* query);
#define c_strirstr					String_IndexOf_R_String //!< @alias{String_IndexOf_R_String}
#define String_LastIndexOf_String	String_IndexOf_R_String //!< @alias{String_IndexOf_R_String}



//! Finds the first occurence of the given char `c` inside the first `n` chars of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The first occurence of the given char `c` within `str`,
**	or `NULL` if no char matched. (checks only `n` chars in `str`).
*/
t_sintmax							String_IndexOf_N_Char(t_char const* str, t_char c, t_size n);
#define c_strinchr					String_IndexOf_N_Char //!< @alias{String_IndexOf_N_Char}

//! Finds the first occurence of any char in `charset` inside the first `n` chars of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The first occurence of any char in the given `charset` within `str`,
**	or `NULL` if no char matched. (checks only `n` chars in `str`).
*/
t_sintmax							String_IndexOf_N_Charset(t_char const* str, t_char const* charset, t_size n);
#define c_strinpbrk					String_IndexOf_N_Charset //!< @alias{String_IndexOf_N_Charset}
#define c_strinchrset				String_IndexOf_N_Charset //!< @alias{String_IndexOf_N_Charset}

//! Finds the first occurence of the string `query` inside the first `n` chars of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The first occurence of the string `query` inside the given string `str`,
**	or `NULL` if nothing matched. (checks only `n` chars in `str`).
*/
t_sintmax							String_IndexOf_N_String(t_char const* str, t_char const* query, t_size n);
#define c_strinstr					String_IndexOf_N_String //!< @alias{String_IndexOf_N_String}



/*
** ************************************************************************** *|
**                              String Replacements                           *|
** ************************************************************************** *|
*/

//! Removes all occurences of `query` within the givne `str`
/*!
**	@nonstd
**
**	@returns
**	A new null-terminated string which is a copy of `str`,
**	in which all occurences of the string `query` have been removed.
*/
_MALLOC()
t_char*					String_Remove(t_char const* str, t_char const* query);
#define c_strremove		String_Remove //!< @alias{String_Remove}



//! Replaces every occurence inside `str` of the given char `char_old` with `char_new`
/*!
**	@nonstd
**
**	@returns
**	A new null-terminated string which is a copy of `str`,
**	in which every occurence of an `old` char is replaced with a `new` char.
*/
_MALLOC()
t_char*						String_Replace_Char(t_char const* str, t_char const char_old, t_char const char_new); // TODO implement
#define c_strrep_char		String_Replace_Char //!< @alias{String_Replace_Char}

//! Replaces every occurence inside `str` of any char in `charset_old` with the corresponding char in `charset_new`
/*!
**	@nonstd
**
**	@returns
**	A new null-terminated string which is a copy of `str`,
**	in which every char in the `old` charset is replaced by the
**	corresponding character in the `new` charset (at the same index).
*/
_MALLOC()
t_char*						String_Replace_Charset(t_char const* str, t_char const* charset_old, t_char const* charset_new); // TODO implement
#define c_strrep_charset	String_Replace_Charset //!< @alias{String_Replace_Charset}

//! Replaces every occurence inside `str` of the given string `str_old` with `str_new`
/*!
**	@nonstd
**
**	@see `stringarray.h` -> String_Split_String() for extra notes.
**
**	@returns
**	A new null-terminated string which is a copy of `str`,
**	in which every occurence of the string `old` is replaced with `new`.
*/
_MALLOC()
t_char*						String_Replace_String(t_char const* str, t_char const* str_old, t_char const* str_new);
#define c_strrep_str		String_Replace_String //!< @alias{String_Replace_String}



/*
** ************************************************************************** *|
**                      String Concatenation Operations                       *|
** ************************************************************************** *|
*/

//! Concatenates two strings into a new one
/*!
**	@nonstd
**
**	@returns
**	A new null-terminated string which is the concatenation of `str1` and `str2`.
*/
_MALLOC()
t_char*					String_Join(t_char const* str1, t_char const* str2);
#define c_strjoin		String_Join //!< @alias{String_Join}

//! Concatenates two strings into a new one, deleting both strings
/*!
**	@nonstd
**
**	Deletes both given strings (free and set to `NULL`).
**
**	@returns
**	A newly allocated string which is the concatenation of `*a_str1` and `*a_str2`.
*/
_MALLOC()
t_char*					String_Merge(t_char* *a_str1, t_char* *a_str2);
#define c_strmerge		String_Merge //!< @alias{String_Merge}

//! Concatenates two strings into a new one, deleting the right-hand string
/*!
**	@nonstd
**
**	Deletes `dest`, replacing it with the result.
**
**	@returns
**	A newly allocated string which is the concatenation of `dest` and `src`.
*/
_MALLOC()
t_char*					String_Append(t_char* *dest, t_char const* src);
#define c_strappend		String_Append //!< @alias{String_Append}

//! Concatenates two strings into a new one, deleting the left-hand string
/*!
**	@nonstd
**
**	Deletes `dest`, replacing it with the result.
**
**	@returns
**	A newly allocated string which is the concatenation of `src` and `dest`.
*/
_MALLOC()
t_char*					String_Prepend(t_char const* src, t_char* *dest);
#define c_strprepend	String_Prepend //!< @alias{String_Prepend}



/*
** ************************************************************************** *|
**                           String In-Place Editing                          *|
** ************************************************************************** *|
*/

/*!
**	@nonstd
**
**	Inserts the string `src` at index `index` in `dest`; deletes `dest` and
**	replaces it by the result. Also returns the result.
*/
t_char*							String_Insert_InPlace(t_char* *dest, t_char const* src, t_u32 index);
#define c_strinsert_inplace		String_Insert_InPlace //!< @alias{String_Insert_InPlace}



//! Replaces every occurence in `str` of `char_old` with `char_new`.
/*!
**	@nonstd
**
**	This function works somewhat like the shell command `tr`.
**	Substitutes every `char_old[i]` for `char_new[i]` in `str`.
**	TODO document edge-case behavior if `(char_old == '\0')`
*/
void								String_Replace_Char_InPlace(t_char* str, t_char const char_old, t_char const char_new);
#define c_strrep_char_inplace		String_Replace_Char_InPlace //!< @alias{String_Replace_Char_InPlace}

//! Replaces every occurence in `str` of any char in `charset_old` with the corresponding char in `charset_new`.
/*!
**	@nonstd
**
**	This function works somewhat like the shell command `tr`.
**	Substitutes every `charset_old[i]` for `charset_new[i]` in `str`.
**	Fails silently if `charset_old` and `charset_new` have different lengths,
**	or if a character is repeated in `charset_old` (only one image for every antecedent),
**	or if `charset_old` or `charset_new` are empty strings.
*/
void								String_Replace_Charset_InPlace(t_char* str, t_char const* charset_old, t_char const* charset_new);
#define c_strrep_charset_inplace	String_Replace_Charset_InPlace //!< @alias{String_Replace_Charset_InPlace}

//! Replaces every occurence in `str` of `str_old` with `str_new`
/*!
**	@nonstd
**
**	@see `stringarray.h` -> String_Split_String() for extra notes.
*/
void								String_Replace_String_InPlace(t_char* *a_str, t_char const* str_old, t_char const* str_new);
#define c_strrep_str_inplace		String_Replace_String_InPlace //!< @alias{String_Replace_String_InPlace}



//! Applies a custom `map` function to each char of the given string `*a_str`
/*!
**	@nonstd
**
**	Changes the content of `*a_str` by applying the given `map` function to each of its chars.
**	Deletes the string `*a_str`, and sets the result's in it instead.
**
**	@returns
**	The newly allocated string which replaces `*a_str`.
*/
t_char*							String_Map_InPlace(t_char* *a_str, t_char (*map)(t_char));
#define c_strmap_inplace		String_Map_InPlace //!< @alias{String_Map_InPlace}



/*
** ************************************************************************** *|
**                        String Whitespace Operations                        *|
** ************************************************************************** *|
*/

//! Trims any char from `charset` from both sides of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string from `str` in which all leading and trailing
**	characters present in `charset` have been removed.
*/
_MALLOC()
t_char*					String_Trim(t_char const* str, t_char const* charset);
#define c_strtrim		String_Trim //!< @alias{String_Trim}

//! Trims any char from `charset` from the left side of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string from `str` in which all leading
**	characters present in `charset` have been removed.
*/
_MALLOC()
t_char*					String_Trim_L(t_char const* str, t_char const* charset);
#define c_strtrim_l		String_Trim_L //!< @alias{String_Trim_L}

//! Trims any char from `charset` from the right side of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string from `str` in which all trailing
**	characters present in `charset` have been removed.
*/
_MALLOC()
t_char*					String_Trim_R(t_char const* str, t_char const* charset);
#define c_strtrim_r		String_Trim_R //!< @alias{String_Trim_R}



//! Pads the given `str` to be `length` chars long, adding `c` chars on both sides, if needed
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string from `str` which is `length` characters long,
**	by padding it with `c` chars on both sides,
**	if the desired `length` is larger than `str`.
*/
_MALLOC()
t_char*					String_Pad(t_char const* str, t_char c, t_size length);
#define c_strpad		String_Pad //!< @alias{String_Pad}

//! Pads the given `str` to be `length` chars long, adding `c` chars on the left side, if needed
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string from `str` which is `length` characters long,
**	by padding it with `c` chars on its left side,
**	if the desired `length` is larger than `str`.
*/
_MALLOC()
t_char*					String_Pad_L(t_char const* str, t_char c, t_size length);
#define c_strpad_l		String_Pad_L //!< @alias{String_Pad_L}

//! Pads the given `str` to be `length` chars long, adding `c` chars on the right side, if needed
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string from `str` which is `length` characters long,
**	by padding it with `c` chars on its right side,
**	if the desired `length` is larger than `str`.
*/
_MALLOC()
t_char*					String_Pad_R(t_char const* str, t_char c, t_size length);
#define c_strpad_r		String_Pad_R //!< @alias{String_Pad_R}



/*
** ************************************************************************** *|
**                          Other String Operations                           *|
** ************************************************************************** *|
*/

//! Creates a new string from `str`, replacing special characters with appropriate escape-sequences
/*!
**	@nonstd
**
**	Returns a new null-terminated string where every non-printable character
**	of `str` is replaced by either its `normal` escape sequence (if available)
**	or a '\\xFF'-type byte/unicode escape sequence if no simple short escape sequence exists.
**	Here is the list of characters which will be escaped by default:
**	- `\\`	`\` (a single backslash, escaping the escape character)
**	- `\'`	Apostrophe
**	- `\"`	Double quotes
**	- `\0`	Null character (string terminator)
**	- `\a`	Bell/Alert/Audible
**	- `\b`	Backspace
**	- `\t`	Tab character
**	- `\n`	Line feed
**	- `\v`	Vertical tab
**	- `\f`	Form-feed
**	- `\r`	Carriage return
**	- `\e`	Escape
**	- `\x??`		Byte value, written as hexadecimal
**	- TODO `\u????`		UTF-8 multi-byte character, written as a hexadecimal code point (Unicode: U+????)
**	- TODO `\U????????`	UTF-8 multi-byte character, written as a hexadecimal code point (Unicode: U+????????)
**
**	@param	str				The string to print/duplicate, with escape-sequences
**	@param	charset_extra	A string containing any extra characters which should be escaped
**							(ie: any char in `charset_extra` will become a `\x??` byte escape sequence)
**	@returns
**	A newly allocated string from the given `str` (can be larger than `str`),
**	in which any special characters are replaced with an appropriate escape-sequence.
*/
_MALLOC()
t_char*							String_Print(t_char const* str, t_char const* charset_extra);
#define c_strprint				String_Print //!< @alias{String_Print}
#define String_Encode			String_Print //!< @alias{String_Print}
#define String_ToPrintable		String_Print //!< @alias{String_Print}



//! Creates a new string from `str`, replacing escape-sequences with their corresponding char value
/*!
**	@nonstd
**
**	Returns a new null-terminated string where every valid backslash escape sequence
**	is converted to its corresponding string byte.
**	Here is the list of character escape sequences which will be properly parsed:
**	- `\\`	`\` (a single backslash, escaping the escape character)
**	- `\'`	Apostrophe
**	- `\"`	Double quotes
**	- `\0`	Null character (string terminator)
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
**
**	@param	str			The string to duplicate, while resolving all escape-sequences to their corresponding char
**	@param	any_escape	If `TRUE`, every backslash will be understood as an escape character
**						(ie: any escape sequance will function, with any char after the `'\'`)
**	@returns
**	A newly allocated modified copy of the given `str` (can be smaller than `str`),
**	with any escape-sequences transformed into their target character value.
*/
_MALLOC()
t_char*							String_Parse(t_char const* str, t_bool any_escape);
#define c_strparse				String_Parse //!< @alias{String_Parse}
#define String_Decode			String_Parse //!< @alias{String_Parse}
#define String_FromPrintable	String_Parse //!< @alias{String_Parse}



//! Get an inverted version of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string which is a copy of the given string `str`,
**	but in reverse order (except for the \0 terminator, obviously).
*/
_MALLOC()
t_char*					String_Reverse(t_char const* str);
#define c_strrev		String_Reverse //!< @alias{String_Reverse}



//! Get a new string from `dest`, with `src` inserted at the given `index`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string from the given string `dest`,
**	in which the string `src` has been inserted at the given `index`.
*/
_MALLOC()
t_char*					String_Insert(t_char const* dest, t_char const* src, t_size index);
#define c_strinsert		String_Insert //!< @alias{String_Insert}



//! Get a subsection which is `n` chars long of the given string `str`, starting at `index`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string which is a subsection of `str`,
**	starting at position `index` and copying `n` characters.
*/
_MALLOC()
t_char*					String_Sub(t_char const* str, t_size index, t_size n);
#define c_strsub		String_Sub //!< @alias{String_Sub}



/*
** ************************************************************************** *|
**                           Functional Operations                            *|
** ************************************************************************** *|
*/

//! Calls a custom function `f` for each character of the given string `str`
/*!
**	@nonstd
**
**	Iterates upon each character of the given string `str`,
**	applying the given function `f` to each of its characters.
*/
void					String_Iterate(t_char* str, void (*f)(t_char* c));
#define c_striter		String_Iterate //!< @alias{String_Iterate}

//! Calls a custom function `f` for each character of the given string `str`
/*!
**	@nonstd
**
**	Iterates upon each character of the given string `str`, (with index information)
**	applying the function `f` to each of its chars.
*/
void					String_Iterate_I(t_char* str, void (*f)(t_char* c, t_size index));
#define c_striteri		String_Iterate_I //!< @alias{String_Iterate_I}



//! Creates a new string with each character mapped to another, using the custom function `map`
/*!
**	@nonstd
**
**	@returns
**	A new string by iterating upon the string `str`,
**	applying the function `map` to each of its characters.
*/
_MALLOC()
t_char*					String_Map(t_char const* str, t_char (*map)(t_char c));
#define c_strmap		String_Map //!< @alias{String_Map}

//! Creates a new string with each character mapped to another, using the custom function `map`
/*!
**	@nonstd
**
**	@returns
**	A new string by iterating upon the string `str`, (with index information)
**	applying the function `map` to each of its characters.
*/
_MALLOC()
t_char*					String_Map_I(t_char const* str, t_char (*map)(t_char c, t_size index));
#define c_strmapi		String_Map_I //!< @alias{String_Map_I}



//! Creates a new string from `str`, only keeping chars when the custom function `filter` returns `TRUE`
/*!
**	@nonstd
**
**	@returns
**	A new null-terminated string by iterating upon the string `str`,
**	removing any chars for which the given `filter` function returns `FALSE`.
*/
_MALLOC()
t_char*					String_Filter(t_char const* str, t_bool (*filter)(t_char c)); // TODO implement
#define c_strfilt		String_Filter //!< @alias{String_Map}

//! Creates a new string from `str`, only keeping chars when the custom function `filter` returns `TRUE`
/*!
**	@nonstd
**
**	@returns
**	A new string by iterating upon the string `str`, (with index information)
**	removing any chars for which the given `filter` function returns `FALSE`.
*/
_MALLOC()
t_char*					String_Filter_I(t_char const* str, t_bool (*filter)(t_char c, t_size index)); // TODO implement
#define c_strfilti		String_Filter_I //!< @alias{String_Map_I}



/*
** ************************************************************************** *|
**                    Essential builtins (for compatibility)                  *|
** ************************************************************************** *|
*/

#ifdef __IOS__ // TODO smarter check here

inline
int		strcmp(char const* str1, char const* str2)
{ return (String_Compare(str1, str2)); }

inline
int		strncmp(char const* str1, char const* str2, size_t n)
{ return (String_Compare_N(str1, str2, n)); }

inline
char*	strchr(char const* str, int c)
{ return (String_Find_Char(str, c)); }

#endif



/*! @} */
HEADER_END
#endif
