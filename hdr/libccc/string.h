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
**	@isostd{https://en.cppreference.com/w/c/string/byte#String_manipulation}
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc_config.h"
#include "libccc_naming.h"
#include "libccc_define.h"

#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/pointer.h"
#include "libccc/char.h"
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

_MALLOC()
//! Returns a newly allocated region of zero-filled memory, which is `n + 1` bytes long.
/*!
**	Allocates a new region of memory of the specified size `n + 1`, the last byte
**	being used for the string null terminator character '\0'.
**
**	@param	n	The length of the string to allocate
**	@returns	A new string which is `n + 1` bytes in length,
**				and has every char set to '\0'.
*/
t_char*				String_New(t_size n);
#define c_strnew	String_New //!< @alias{String_New}

_MALLOC()
//! Returns a newly allocated region of `c`-filled memory, which is `n + 1` bytes long.
/*!
**	Allocates a new region of memory of the specified size `n + 1`, the last byte
**	being used for the string null terminator character '\0'.
**
**	@param	n	The length of the string to allocate
**	@param	c	The character value to fill each byte with
**	@returns	A new string which is `n + 1` bytes in length,
**				and has every char set to `c`, plus the last t_char set to '\0'.
*/
t_char*				String_New_C(t_size n, t_char c);
#define c_strcnew	String_New_C //!< @alias{String_New_C}

//! Sets every char of the given string `str` to `c`, only stopping upon reading a '\0' string terminator character.
/*!
**	Fills the given string `str` with the character `c`
**
**	@param	str	The string to fill
**	@param	c	The character value to fill with
*/
void				String_Set(t_char* str, t_char c);
#define c_strset	String_Set //!< @alias{String_Set}

//! Clears the given string `str`, setting each character of `str` to '\0'.
/*!
*/
void				String_Clear(t_char* str);
#define c_strclr	String_Clear //!< @alias{String_Clear}

/*!
**	Deletes the string pointed to by `ptr`, freeing the associated memory.
*/
void				String_Delete(t_char* *a_str);
#define c_strdel	String_Delete //!< @alias{String_Delete}

/*!
**	Returns a newly allocated string which is a copy of the given string `str`,
**	(or #NULL required memory could not be allocated).
*/
_MALLOC()
t_char*				String_Duplicate(t_char const* str);
#define c_strdup	String_Duplicate //!< @alias{String_Duplicate}

/*!
**	Returns a newly allocated string which is a copy of the given string `str`,
**	(or #NULL required memory could not be allocated), copying at most
**	`n` characters.
*/
_MALLOC()
t_char*				String_Duplicate_N(t_char const* str, t_size n);
#define c_strndup	String_Duplicate_N //!< @alias{String_Duplicate_N}

/*!
**	Returns a newly allocated string which is a copy of the given string `str`,
**	(or #NULL required memory could not be allocated), stopping at the
**	first occurence of `c`.
*/
_MALLOC()
t_char*				String_Duplicate_C(t_char const* str, t_char const c);
#define c_strcdup	String_Duplicate_C //!< @alias{String_Duplicate_Char}

/*!
**	Copies the given string `src` into `dest` (null-terminator included),
**	and returns `dest` (no allocation is performed).
*/
t_char*				String_Copy(t_char* dest, t_char const* src);
#define c_strcpy	String_Copy //!< @alias{String_Copy}

//! Copies the first `n` characters of the given string `src` into `dest`, and returns `dest`
/*!
**	Copies the first `n` characters of the given string `src` into `dest`,
**	and returns `dest` (no allocation is performed).
*/
t_char*				String_Copy_N(t_char* dest, t_char const* src, t_size n);
#define c_strncpy	String_Copy_N //!< @alias{String_Copy_N}

//! Copies the given string `src` into `dest`, null-terminating the result and returning its length
/*!
**	Copies the given string `src` into `dest`, null-terminating the result
**	(the '\0' is placed at: `(dest + size - 1)`),
**	and returns the resulting size of `dest`.
*/
t_size				String_Copy_L(t_char* dest, t_char const* src, t_size size);
#define c_strlcpy	String_Copy_L //!< @alias{String_Copy_L}

/*!
**	Concatenates the given string `src` to the end of `dest`,
**	(removing dest's '\0' terminator) and returns `dest`.
*/
t_char*				String_Concat(t_char* dest, t_char const* src);
#define c_strcat	String_Concat //!< @alias{String_Concat}

/*!
**	Concatenates the first `n` characters of the given string `src`
**	to the end of `dest`, and returns `dest`.
*/
t_char*				String_Concat_N(t_char* dest, t_char const* src, t_size n);
#define c_strncat	String_Concat_N //!< @alias{String_Concat_N}

/*!
**	Concatenates characters of the given string `src` to the end of `dest`,
**	null-terminating the result (places the '\0' at `dest + size - 1`),
**	and returns the resulting size of `dest`.
*/
t_size				String_Concat_L(t_char* dest, t_char const* src, t_size size);
#define c_strlcat	String_Concat_L //!< @alias{String_Concat_L}



/*
** ************************************************************************** *|
**                                String Checks                               *|
** ************************************************************************** *|
*/

/*!
**	Returns the length of the given null-terminated string `str`.
*/
t_size				String_Length(t_char const* str);
#define c_strlen	String_Length //!< @alias{String_Length}

/*!
**	Compares the two given strings, and returns the first difference
**	between characters encountered `str1[i] - str2[i]`
**	Otherwise, it will return 0 if `str1` and `str2` are identical.
*/
int						String_Compare(t_char const* str1, t_char const* str2);
#define c_strcmp		String_Compare //!< @alias{String_Compare}

/*!
**	Compares at most `n` chars of the two given strings, and returns
**	the first difference of characters encountered: `str1[i] - str2[i]`
*/
int						String_Compare_N(t_char const* str1, t_char const* str2, t_size n);
#define c_strncmp		String_Compare_N //!< @alias{String_Compare_N}

/*!
**	Compares the two given strings (case-insensitive), and returns the
**	first difference between characters encountered `str1[i] - str2[i]`
**	Otherwise, it will return 0 if `str1` and `str2` are identical.
*/
int						String_Compare_IgnoreCase(t_char const* str1, t_char const* str2);
#define c_stricmp		String_Compare_IgnoreCase //!< @alias{String_Compare_IgnoreCase}
#define c_strcasecmp	String_Compare_IgnoreCase //!< @alias{String_Compare_IgnoreCase}

/*!
**	Compares at most `n` chars of the two given strings (case-insensitive),
**	and returns the first difference of characters encountered: `str1[i] - str2[i]`
*/
int						String_Compare_N_IgnoreCase(t_char const* str1, t_char const* str2, t_size n);
#define c_strnicmp		String_Compare_N_IgnoreCase //!< @alias{String_Compare_N_IgnoreCase}
#define c_strncasecmp	String_Compare_N_IgnoreCase //!< @alias{String_Compare_N_IgnoreCase}

// TODO String_CompareUntil_Char()
// TODO String_CompareUntil_Charset()
// TODO String_CompareUntil_String()



//!	Returns #TRUE if the two given strings have identical content, and #FALSE otherwise
/*!
**	@returns #TRUE if the two given strings have identical content, and #FALSE otherwise
*/
t_bool					String_Equals(t_char const* str1, t_char const* str2);
#define c_strequ		String_Equals //!< @alias{String_Equals}

//!	Returns #TRUE if the first `n` chars of the two given strings match, and #FALSE otherwise
/*!
**	@returns #TRUE if the first `n` chars of the two given strings match, and #FALSE otherwise
*/
t_bool					String_Equals_N(t_char const* str1, t_char const* str2, t_size n);
#define c_strnequ		String_Equals_N //!< @alias{String_Equals_N}

//!	Returns #TRUE if the two given strings have identical content (case-insensitive), and #FALSE otherwise
/*!
**	@returns #TRUE if the two given strings have identical content (case-insensitive), and #FALSE otherwise
*/
t_bool					String_Equals_IgnoreCase(t_char const* str1, t_char const* str2);
#define c_striequ		String_Equals_IgnoreCase //!< @alias{String_Equals_IgnoreCase}
#define c_strcaseequ	String_Equals_IgnoreCase //!< @alias{String_Equals_IgnoreCase}

//!	Returns #TRUE if the first `n` chars of the two given strings match (ignoring case), and #FALSE otherwise
/*!
**	@returns #TRUE if the first `n` chars of the two given strings match (ignoring case), and #FALSE otherwise
*/
t_bool					String_Equals_N_IgnoreCase(t_char const* str1, t_char const* str2, t_size n);
#define c_strniequ		String_Equals_N_IgnoreCase //!< @alias{String_Equals_N_IgnoreCase}
#define c_strncaseequ	String_Equals_N_IgnoreCase //!< @alias{String_Equals_N_IgnoreCase}

// TODO String_EqualsUntil_Char()
// TODO String_EqualsUntil_Charset()
// TODO String_EqualsUntil_String()



/*!
**	Returns 1 if the given string `str` contains at least one occurence
**	of any character found inside `charset`, returns 0 otherwise.
*/
t_bool						String_Has(t_char const* str, t_char const* charset);
#define c_strhas			String_Has //!< @alias{String_Has}

/*!
**	Returns 1 if all the characters inside the given string `str`
**	are contained within the string `charset`, returns 0 otherwise.
*/
t_bool						String_HasOnly(t_char const* str, t_char const* charset);
#define c_strhasonly		String_HasOnly //!< @alias{String_HasOnly}

/*!
**	Returns the amount of occurences of t_char `c` in the given string `str`.
*/
t_size						String_Count_Char(t_char const* str, t_char c);
#define c_strcount_chr		String_Count_Char //!< @alias{String_Count_Char}

/*!
**	Returns the amount of occurences of chars in `charset` in the given string
**	`str`.
*/
t_size						String_Count_Charset(t_char const* str, t_char const* charset);
#define c_strcount_chrset	String_Count_Charset //!< @alias{String_Count_Charset}

/*!
**	Returns the amount of occurences of `query` in the given string `str`.
*/
t_size						String_Count_String(t_char const* str, t_char const* query);
#define c_strcount_str		String_Count_String //!< @alias{String_Count_String}



/*
** ************************************************************************** *|
**                         String Searching/Replacing                         *|
** ************************************************************************** *|
*/

//! Returns the first occurence of the given t_char `c` within `str`, or #NULL if no t_char matched.
t_char*							String_Find_Char(t_char const* str, t_char c);
#define c_strchr				String_Find_Char //!< @alias{String_Find_Char}
//! Returns the first occurence of any t_char in the given `charset` within `str`, or #NULL if no t_char matched.
t_char*							String_Find_Charset(t_char const* str, t_char const* charset);
#define c_strchrset				String_Find_Charset //!< @alias{String_Find_Charset}
//! Returns the first occurence of the string `query` inside the given string `str`, or #NULL if nothing matched.
t_char*							String_Find_String(t_char const* str, t_char const* query);
#define c_strstr				String_Find_String //!< @alias{String_Find_String}

//! Returns the last occurence of the given t_char `c` within `str`, or #NULL if no t_char matched.
t_char*							String_Find_R_Char(t_char const* str, t_char c);
#define c_strrchr				String_Find_R_Char //!< @alias{String_Find_R_Char}
#define String_FindLast_Char	String_Find_R_Char //!< @alias{String_Find_R_Char}
//! Returns the last occurence of any t_char in the given `charset` within `str`, or #NULL if no t_char matched.
t_char*							String_Find_R_Charset(t_char const* str, t_char const* charset);
#define c_strrchrset			String_Find_R_Charset //!< @alias{String_Find_R_Charset}
#define String_FindLast_Charset	String_Find_R_Charset //!< @alias{String_Find_R_Charset}
//! Returns the last occurence of the string `query` inside the given string `str`, or #NULL if nothing matched.
t_char*							String_Find_R_String(t_char const* str, t_char const* query);
#define c_strrstr				String_Find_R_String //!< @alias{String_Find_R_String}
#define String_FindLast_String	String_Find_R_String //!< @alias{String_Find_R_String}

//! Returns the first occurence of the given t_char `c` within `str`, or #NULL if no t_char matched. (checks only `n` chars in `str`).
t_char*							String_Find_N_Char(t_char const* str, t_char c, t_size n);
#define c_strnchr				String_Find_N_Char //!< @alias{String_Find_N_Char}
//! Returns the first occurence of any t_char in the given `charset` within `str`, or #NULL if no t_char matched. (checks only `n` chars in `str`).
t_char*							String_Find_N_Charset(t_char const* str, t_char const* charset, t_size n);
#define c_strnchrset			String_Find_N_Charset //!< @alias{String_Find_N_Charset}
//! Returns the first occurence of the string `query` inside the given string `str`, or #NULL if nothing matched. (checks only `n` chars in `str`).
t_char*							String_Find_N_String(t_char const* str, t_char const* query, t_size n);
#define c_strnstr				String_Find_N_String //!< @alias{String_Find_N_String}



//! Returns the index of the first occurrence at which `c` is found in `str`, or -1 if `c` does not exist in `str`.
t_ptrdiff							String_IndexOf_Char(t_char const* str, t_char c);
#define c_strichr					String_IndexOf_Char //!< @alias{String_IndexOf_Char}
//! Returns the index of the first occurrence at which `c` is found in `str`, or -1 if `c` does not exist in `str`.
t_ptrdiff							String_IndexOf_Charset(t_char const* str, t_char const* charset);
#define c_strichrset				String_IndexOf_Charset //!< @alias{String_IndexOf_Charset}
//! Returns the index of the first occurrence at which `query` is found in `str`, or -1 if `query` does not exist in str.
t_ptrdiff							String_IndexOf_String(t_char const* str, t_char const* query);
#define c_stristr					String_IndexOf_String //!< @alias{String_IndexOf_String}

//! Returns the last occurence of the given t_char `c` within `str`, or #NULL if no t_char matched.
t_ptrdiff							String_IndexOf_R_Char(t_char const* str, t_char c);
#define c_strirchr					String_IndexOf_R_Char //!< @alias{String_IndexOf_R_Char}
#define String_LastIndexOf_Char		String_IndexOf_R_Char //!< @alias{String_IndexOf_R_Char}
//! Returns the last occurence of any t_char in the given `charset` within `str`, or #NULL if no t_char matched.
t_ptrdiff							String_IndexOf_R_Charset(t_char const* str, t_char const* charset);
#define c_strirchrset				String_IndexOf_R_Charset //!< @alias{String_IndexOf_R_Charset}
#define String_LastIndexOf_Charset	String_IndexOf_R_Charset //!< @alias{String_IndexOf_R_Charset}
//! Returns the last occurence of the string `query` inside the given string `str`, or #NULL if nothing matched.
t_ptrdiff							String_IndexOf_R_String(t_char const* str, t_char const* query);
#define c_strirstr					String_IndexOf_R_String //!< @alias{String_IndexOf_R_String}
#define String_LastIndexOf_String	String_IndexOf_R_String //!< @alias{String_IndexOf_R_String}

//! Returns the first occurence of the given t_char `c` within `str`, or #NULL if no t_char matched. (checks only `n` chars in `str`).
t_ptrdiff							String_IndexOf_N_Char(t_char const* str, t_char c, t_size n);
#define c_strinchr					String_IndexOf_N_Char //!< @alias{String_IndexOf_N_Char}
//! Returns the first occurence of any t_char in the given `charset` within `str`, or #NULL if no t_char matched. (checks only `n` chars in `str`).
t_ptrdiff							String_IndexOf_N_Charset(t_char const* str, t_char const* charset, t_size n);
#define c_strinchrset				String_IndexOf_N_Charset //!< @alias{String_IndexOf_N_Charset}
//! Returns the first occurence of the string `query` inside the given string `str`, or #NULL if nothing matched. (checks only `n` chars in `str`).
t_ptrdiff							String_IndexOf_N_String(t_char const* str, t_char const* query, t_size n);
#define c_strinstr					String_IndexOf_N_String //!< @alias{String_IndexOf_N_String}



/*!
**	Returns a new null-terminated string which is a copy of `str`,
**	in which all occurences of the string `query` have been removed.
*/
_MALLOC()
t_char*					String_Remove(t_char const* str, t_char const* query);
#define c_strremove		String_Remove //!< @alias{String_Remove}

/*!
**	Returns a new null-terminated string which is a copy of `str`,
**	in which every occurence of an `old` t_char is replaced with a `new` t_char.
*/
//TODO implement
_MALLOC()
t_char*						String_Replace_Char(t_char const* str, t_char const char_old, t_char const char_new);
#define c_strrep_char		String_Replace_Char //!< @alias{String_Replace_Char}

/*!
**	Returns a new null-terminated string which is a copy of `str`,
**	in which every char in the `old` charset is replaced by the
**	corresponding character in the `new` charset (at the same index).
*/
//TODO implement
_MALLOC()
t_char*						String_Replace_Charset(t_char const* str, t_char const* charset_old, t_char const* charset_new);
#define c_strrep_charset	String_Replace_Charset //!< @alias{String_Replace_Charset}

/*!
**	Returns a new null-terminated string which is a copy of `str`,
**	in which every occurence of the string `old` is replaced with `new`.
**	NB: see `stringarray.h` -> `String_Split_String` for extra notes on bevahior.
*/
_MALLOC()
t_char*						String_Replace_String(t_char const* str, t_char const* str_old, t_char const* str_new);
#define c_strrep_str		String_Replace_String //!< @alias{String_Replace_String}



/*
** ************************************************************************** *|
**                      String Concatenation Operations                       *|
** ************************************************************************** *|
*/

/*!
**	Returns a new null-terminated string which is the result of
**	the concatenation of the two given strings `str1` and `str2`.
*/
_MALLOC()
t_char*					String_Join(t_char const* str1, t_char const* str2);
#define c_strjoin		String_Join //!< @alias{String_Join}

/*!
**	Returns a newly allocated string which is the concatenation of `s1` and `s2`.
**	Deletes both inputs from memory. Also, returns the result.
*/
_MALLOC()
t_char*					String_Merge(t_char* *a_s1, t_char* *a_s2);
#define c_strmerge		String_Merge //!< @alias{String_Merge}

/*!
**	Returns a newly allocated string which is the concatenation of `dest` and `src`.
**	Deletes `dest`, replacing it by the result. Also, returns the result.
*/
_MALLOC()
t_char*					String_Append(t_char* *dest, t_char const* src);
#define c_strappend		String_Append //!< @alias{String_Append}


/*!
**	Returns a newly allocated string which is the concatenation of `src` and `dest`.
**	Deletes `dest`, replacing it by the result. Also, returns the result.
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
**	Inserts the string `src` at index `index` in `dest`; deletes `dest` and
**	replaces it by the result. Also returns the result.
*/
t_char*							String_Insert_InPlace(t_char* *dest, t_char const* src, t_u32 index);
#define c_strinsert_inplace		String_Insert_InPlace //!< @alias{String_Insert_InPlace}



/*!
**	Replaces every occurence of `old` by `new` in `str`.
*/
void								String_Replace_Char_InPlace(t_char* str, t_char const char_old, t_char const char_new);
#define c_strrep_char_inplace		String_Replace_Char_InPlace //!< @alias{String_Replace_Char_InPlace}

/*!
**	Replaces `old` charset by `new` charset in `str`.
**	Works like the bash function tr. Substitutes old[i] by new[i] in `str`.
**	Fails silently if strlen is different for `old` and `new`, or if a
**	character is repeated in `old` (only one image for every antecedent), or if
**	`old` or `new` are the empty string.
*/
void								String_Replace_Charset_InPlace(t_char* str, t_char const* charset_old, t_char const* charset_new);
#define c_strrep_charset_inplace	String_Replace_Charset_InPlace //!< @alias{String_Replace_Charset_InPlace}

/*!
**	Replaces every occurence of the query old by the string new in str.
**	NB: see stringarray.h -> c_strsplit_str for extra notes on bevahior.
*/
void								String_Replace_String_InPlace(t_char* *a_str, t_char const* str_old, t_char const* str_new);
#define c_strrep_str_inplace		String_Replace_String_InPlace //!< @alias{String_Replace_String_InPlace}



/*!
**	Changes the content of '*a_str' by applying f to each of its chars.
**	Deletes `a_str`, and sets the result in it instead. Also returns the 
**	result.
*/
t_char*								String_Map_InPlace(t_char* *a_str, t_char (*map)(t_char));
#define c_strmap_inplace			String_Map_InPlace //!< @alias{String_Map_InPlace}



/*
** ************************************************************************** *|
**                        Common Whitespace Operations                        *|
** ************************************************************************** *|
*/

/*!
**	Returns a new string from `str` in which all leading and trailing
**	whitespace characters (' ', '\\t', '\\n', '\\r', '\\v', '\\f') have been removed.
*/
_MALLOC()
t_char*					String_Trim(t_char const* str, t_char const* charset);
#define c_strtrim		String_Trim //!< @alias{String_Trim}

/*!
**	Returns a new string from `str` in which all leading
**	characters present in `charset` have been removed.
*/
_MALLOC()
t_char*					String_Trim_L(t_char const* str, t_char const* charset);
#define c_strtrim_l		String_Trim_L //!< @alias{String_Trim_L}

/*!
**	Returns a new string from `str` in which all trailing
**	characters present in `charset` have been removed.
*/
_MALLOC()
t_char*					String_Trim_R(t_char const* str, t_char const* charset);
#define c_strtrim_r		String_Trim_R //!< @alias{String_Trim_R}

/*!
**	Returns a new null-terminated string duplicate of `str` which is
**	`length` characters long, by padding it with `c` chars on both sides
**	if the desired `length` is larger than `str`.
*/
_MALLOC()
t_char*					String_Pad(t_char const* str, t_char c, t_size length);
#define c_strpad		String_Pad //!< @alias{String_Pad}

/*!
**	Returns a new null-terminated string duplicate of `str` which is
**	`length` characters long, by padding it with `c` chars on its
**	left side if the desired `length` is larger than `str`.
*/
_MALLOC()
t_char*					String_Pad_L(t_char const* str, t_char c, t_size length);
#define c_strpad_l		String_Pad_L //!< @alias{String_Pad_L}

/*!
**	Returns a new null-terminated string duplicate of `str` which is
**	`length` characters long, by padding it with `c` chars on its
**	right side if the desired `length` is larger than `str`.
*/
_MALLOC()
t_char*					String_Pad_R(t_char const* str, t_char c, t_size length);
#define c_strpad_r		String_Pad_R //!< @alias{String_Pad_R}



/*
** ************************************************************************** *|
**                          Other String Operations                           *|
** ************************************************************************** *|
*/

//! Creates a new string with character escape-sequences
/*!
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
**	@param	str				The string to duplicate with escape-sequences
**	@param	charset_extra	A string containing any extra characters which should be escaped (ie: preceded by a backslash)
**	@returns a newly allocated modified copy of the given `str`, with special characters being escape-sequenced.
*/
_MALLOC()
t_char*							String_Print(t_char const* str, t_char const* charset_extra);
#define c_strprint				String_Print //!< @alias{String_Print}
#define String_Encode			String_Print //!< @alias{String_Print}
#define String_ToPrintable		String_Print //!< @alias{String_Print}



//! Creates a new string, replacing escape-sequences with their corresponding char value
/*!
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
**	@param	any_escape	If `TRUE`, every backslash will be understood as an escape character (any single backslash will dissappear)
**	@returns a newly allocated modified copy of the given `str`, with escape-sequences transformed into their target value.
*/
_MALLOC()
t_char*							String_Parse(t_char const* str, t_bool any_escape);
#define c_strparse				String_Parse //!< @alias{String_Parse}
#define String_Decode			String_Parse //!< @alias{String_Parse}
#define String_FromPrintable	String_Parse //!< @alias{String_Parse}



/*!
**	Returns a newly allocated string which is a copy of the given string `str`,
**	but in reverse order (except for the \0 terminator, obviously).
*/
_MALLOC()
t_char*					String_Reverse(t_char const* str);
#define c_strrev		String_Reverse //!< @alias{String_Reverse}

/*!
**	Returns a reallocated version of the given string `dest`, in which
**	the string `str` has been inserted at the index `offset`.
*/
_MALLOC()
t_char*					String_Insert(t_char const* dest, t_char const* src, t_size offset);
#define c_strinsert		String_Insert //!< @alias{String_Insert}

/*!
**	Returns a new null-terminated string which is a subsection of `str`,
**	starting at t_char index `index` and copying `n` characters.
*/
_MALLOC()
t_char*					String_Sub(t_char const* str, t_size index, t_size n);
#define c_strsub		String_Sub //!< @alias{String_Sub}



/*
** ************************************************************************** *|
**                           Functional Operations                            *|
** ************************************************************************** *|
*/

/*!
**	Iterates upon each character of the given string `str`,
**	applying the given function `f` to each of its characters.
*/
void					String_Iterate(t_char* str, void (*f)(t_char* c));
#define c_striter		String_Iterate //!< @alias{String_Iterate}

/*!
**	Iterates upon each character of the given string `str`,
**	applying the function `f` to each of its chars (with index information).
*/
void					String_Iterate_I(t_char* str, void (*f)(t_char* c, t_size index));
#define c_striteri		String_Iterate_I //!< @alias{String_Iterate_I}



//! Creates a string with each character mapped to another
/*!
**	Creates a new null-terminated string by iterating upon the string `str`,
**	applying the function `map` to each of its chars.
*/
_MALLOC()
t_char*					String_Map(t_char const* str, t_char (*map)(t_char c));
#define c_strmap		String_Map //!< @alias{String_Map}

//! Creates a string with each character mapped to another
/*!
**	Creates a new null-terminated string by iterating upon the string `str`,
**	applying the function `map` to each of its chars (with index information).
*/
_MALLOC()
t_char*					String_Map_I(t_char const* str, t_char (*map)(t_char c, t_size index));
#define c_strmapi		String_Map_I //!< @alias{String_Map_I}



/*!
**	Creates a new null-terminated string by iterating upon the string `str`,
**	removing any chars for which the given `filter` function returns `FALSE`.
*/
_MALLOC()
t_char*					String_Filter(t_char const* str, t_bool (*filter)(t_char c)); // TODO implement
#define c_strfilt		String_Filter //!< @alias{String_Map}

/*!
**	Creates a new null-terminated string by iterating upon the string `str`,
**	removing any chars for which the given `filter` function returns `FALSE`.
*/
_MALLOC()
t_char*					String_Filter_I(t_char const* str, t_bool (*filter)(t_char c, t_size index)); // TODO implement
#define c_strfilti		String_Filter_I //!< @alias{String_Map_I}



/*! @} */
HEADER_END
#endif
