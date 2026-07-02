/*============================================================================*\
||                                            ______________________________  ||
||  libccc/text/string/utf8.h                |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_STRING_UTF8_H
#define __LIBCCC_STRING_UTF8_H
/*!@group{libccc_string_utf8,18,libccc/text/string/utf8.h}
**
**	This header defines the common standard UTF8 text string manipulation functions.
**
**	@isostd{C,https://en.cppreference.com/w/c/string/multibyte.html}
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"

#include "libccc/text/char/unicode.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//! Type definition for a string of characters (UTF8 format)
/*!
**	This typedef is only provided for certain niche purposes (such as use with generics),
**	since it is typically not very good practice in C to hide pointers within `typedef` types.
*/
//!@{
typedef t_utf8*	p_mbs;
typedef t_utf8*	p_mbstr;
typedef t_utf8*	p_mbstring;
typedef t_utf8*	p_strutf8;
typedef t_utf8*	p_stringutf8;
//!@}



typedef void	(*f_string_utf8_iterate)	(t_utf8* c);
typedef void	(*f_string_utf8_iterate_i)	(t_utf8* c, t_size i);
typedef t_utf8	(*f_string_utf8_map)		(t_utf8 c);
typedef t_utf8	(*f_string_utf8_map_i)		(t_utf8 c, t_size i);
typedef t_bool	(*f_string_utf8_filter)		(t_utf8 c);
typedef t_bool	(*f_string_utf8_filter_i)	(t_utf8 c, t_size i);



/*============================================================================*\
||                          Basic String Operations                           ||
\*============================================================================*/

#if 0 // These functions do not yet exist and/or are a work in progress

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
t_utf8*				StringUTF8_New(t_size n);
#define c_mbsnew		StringUTF8_New
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
t_utf8*				StringUTF8_New_C(t_size n, t_utf8 c);
#define c_mbscnew	StringUTF8_New_C
//!@}



//!@doc Deallocates the given string `str`.
/*!
**	@nonstd
*/
//!@{
void				StringUTF8_Free(t_utf8* str);
#define c_mbsfree	StringUTF8_Free
//!@}

//!@doc Deallocates the string pointed to by `*a_str`, and sets the pointer to `NULL`.
/*!
**	@nonstd
*/
//!@{
void				StringUTF8_Delete(t_utf8* *a_str);
#define c_mbsdel	StringUTF8_Delete
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
t_utf8*				StringUTF8_Duplicate(t_utf8 const* str);
#define c_mbsdup		StringUTF8_Duplicate
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
t_utf8*				StringUTF8_Duplicate_N(t_utf8 const* str, t_size n);
#define c_mbsndup	StringUTF8_Duplicate_N
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
t_utf8*				StringUTF8_Duplicate_Char(t_utf8 const* str, t_utf32 c);
#define c_mbschrdup	StringUTF8_Duplicate_Char
//!@}

//!@doc Duplicates the given `str`, the copy stops at the first occurence of any glyph in `charset`
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
t_utf8*				StringUTF8_Duplicate_Charset(t_utf8 const* str, t_utf8 const* charset);
#define c_mbscstdup	StringUTF8_Duplicate_Charset
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
t_utf8*				StringUTF8_Duplicate_String(t_utf8 const* str, t_utf8 const* target);
#define c_mbsstrdup	StringUTF8_Duplicate_String
//!@}



//!@doc Clears the given string `str`, setting each byte to `'\0'`.
/*!
**	@nonstd
*/
//!@{
void				StringUTF8_Clear(t_utf8* str);
#define c_mbsclr		StringUTF8_Clear
//!@}

//!@doc Sets every bytes of the given string `str` to `c`, only stopping upon reading a `'\0'` null-terminator.
/*!
**	@nonstd
**
**	Fills the given string `str` with the character `c`
**
**	@param	str	The string to fill
**	@param	c	The character value to fill with
*/
//!@{
void					StringUTF8_SetBytes(t_utf8* str, t_utf8 c);
#define c_mbssetbytes	StringUTF8_SetBytes
//!@}

//!@doc Sets every glyphs of the given string `str` to `c`, only stopping upon reading a `'\0'` null-terminator.
/*!
**	@nonstd
**
**	TODO: better doc
**	Fills the given string `str` with the character `c`
**
**	@param	str	The string to fill
**	@param	c	The character value to fill with
*/
//!@{
void					StringUTF8_SetChars(t_utf8* str, t_utf8 c);
#define c_mbssetglyphs	StringUTF8_SetChars
//!@}

// TODO strnsetbytes() StringUTF8_SetBytes_N
// TODO strnsetglyphs() StringUTF8_SetChars_N



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
t_utf8*				StringUTF8_Copy(t_utf8* dest, t_utf8 const* src);
#define c_mbscpy	StringUTF8_Copy
//!@}

//!@doc Copies the first `n` bytes of the given string `src` into `dest`, and returns `dest`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strncpy}
**
**	Copies the first `n` characters of the given string `src` into `dest`
**
**	@returns
**	`dest` (no allocation is performed).
*/
//!@{
t_utf8*				StringUTF8_Copy_N(t_utf8* dest, t_utf8 const* src, t_size n);
#define c_mbsncpy	StringUTF8_Copy_N
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
t_size				StringUTF8_Copy_L(t_utf8* dest, t_utf8 const* src, t_size size);
#define c_mbslcpy	StringUTF8_Copy_L
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
t_utf8*				StringUTF8_Add(t_utf8* dest, t_utf8 const* src);
#define c_mbscat	StringUTF8_Add
#define c_mbsadd	StringUTF8_Add
//!@}

//!@doc Concatenates the given string `src` to the end of `dest`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strncat}
**
**	Concatenates the first `n` bytes of the given string `src` to the end of `dest`.
**
**	@returns
**	`dest` (no allocation is performed).
*/
//!@{
t_utf8*				StringUTF8_Add_N(t_utf8* dest, t_utf8 const* src, t_size n);
#define c_mbsncat	StringUTF8_Add_N
#define c_mbsnadd	StringUTF8_Add_N
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
t_size				StringUTF8_Add_L(t_utf8* dest, t_utf8 const* src, t_size size);
#define c_mbslcat	StringUTF8_Add_L
#define c_mbsladd	StringUTF8_Add_L
//!@}

#endif

/*============================================================================*\
||                                String Checks                               ||
\*============================================================================*/

//!@doc Get the length (in bytes) of a string, excluding final '\0'
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strlen}
**
**	@returns
**	The length of the given null-terminated string `str`.
*/
//!@{
t_size				StringUTF8_Length(t_utf8 const* str);
#define c_mbslen	StringUTF8_Length
//!@}

//!@doc Get the length (in bytes) of a string, excluding final '\0', but at most `n` bytes 
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strlen}
**
**	@returns
**	`StringUTF8_Length(str)` if that is less than `n`, or `n` if there is no '\0' among the first `n` bytes of the string
*/
//!@{
t_size				StringUTF8_Length_N(t_utf8 const* str, t_size n);
#define c_mbsnlen	StringUTF8_Length_N
//!@}

//!@doc Get the amount of characters of a UTF-8 string, excluding final '\0'
/*!
**	@nonstd
**
**	@returns
**	The amount of characters in the given null-terminated UTF-8 string `str`.
*/
//!@{
t_size				StringUTF8_Chars(t_utf8 const* str);
#define c_mbsclen	StringUTF8_Chars
//!@}

//!@doc Get the amount of characters of a UTF-8 string, excluding final '\0', but at most `n` chars 
/*!
**	@nonstd
**
**	@returns
**	`StringUTF8_Chars(str)` if that is less than `n`, or `n` if there is no `'\0'` among the first `n` chars of the string
*/
//!@{
t_size				StringUTF8_Chars_N(t_utf8 const* str, t_size n);
#define c_mbsnclen	StringUTF8_Chars_N
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
t_bool					StringUTF8_Equals(t_utf8 const* str1, t_utf8 const* str2);
#define c_mbsequ		StringUTF8_Equals
//!@}

//!@doc	Checks whether the first `n` bytes of the two given strings match
/*!
**	@nonstd
**
**	TODO: decide: We probably do not want to start comparing charcter we know we can't finish, to keep consistent with other functions
**
**	@returns
**	`TRUE` if the first `n` chars of the two given strings are identical,
**	`FALSE` otherwise
*/
//!@{
t_bool					StringUTF8_Equals_N(t_utf8 const* str1, t_utf8 const* str2, t_size n);
#define c_mbsnequ		StringUTF8_Equals_N
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
t_bool					StringUTF8_Equals_IgnoreCase(t_utf8 const* str1, t_utf8 const* str2);
#define c_mbsiequ		StringUTF8_Equals_IgnoreCase
#define c_mbscaseequ	StringUTF8_Equals_IgnoreCase
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
t_bool					StringUTF8_Equals_N_IgnoreCase(t_utf8 const* str1, t_utf8 const* str2, t_size n);
#define c_mbsniequ		StringUTF8_Equals_N_IgnoreCase
#define c_mbsncaseequ	StringUTF8_Equals_N_IgnoreCase
//!@}

// TODO StringUTF8_EqualsUntil_Char()
// TODO StringUTF8_EqualsUntil_Charset()
// TODO StringUTF8_EqualsUntil_String()



//!@doc Compares the content of the two given strings
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strcmp}
**
**	@returns
**	The first difference between chars encountered: `(str1[i] - str2[i])`,
**	or `0` if `str1` and `str2` have identical content.
*/
//!@{
t_sint					StringUTF8_Compare(t_utf8 const* str1, t_utf8 const* str2);
#define c_mbscmp		StringUTF8_Compare
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
t_sint					StringUTF8_Compare_N(t_utf8 const* str1, t_utf8 const* str2, t_size n);
#define c_mbsncmp		StringUTF8_Compare_N
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
t_sint					StringUTF8_Compare_IgnoreCase(t_utf8 const* str1, t_utf8 const* str2);
#define c_mbsicmp		StringUTF8_Compare_IgnoreCase
#define c_mbscasecmp	StringUTF8_Compare_IgnoreCase
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
t_sint					StringUTF8_Compare_N_IgnoreCase(t_utf8 const* str1, t_utf8 const* str2, t_size n);
#define c_mbsnicmp		StringUTF8_Compare_N_IgnoreCase
#define c_mbsncasecmp	StringUTF8_Compare_N_IgnoreCase
//!@}

// TODO StringUTF8_CompareUntil_Char()
// TODO StringUTF8_CompareUntil_Charset()
// TODO StringUTF8_CompareUntil_String()

#if 0 // These functions do not yet exist and/or are a work in progress

//!@doc Check if the given `str` contains characters from `charset`
/*!
**	@nonstd
**
**	@returns
**	`TRUE` if the given string `str` contains at least one occurence
**	of any character found inside `charset`, otherwise returns `FALSE`.
*/
//!@{
t_bool						StringUTF8_Has(t_utf8 const* str, t_utf8 const* charset);
#define c_mbshas			StringUTF8_Has
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
t_bool						StringUTF8_HasOnly(t_utf8 const* str, t_utf8 const* charset);
#define c_mbshasonly		StringUTF8_HasOnly
//!@}



// TODO strspn()
// TODO strcspn()

#endif

//!@doc Count the total occurences of the given char `c` in the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The amount of occurences of t_utf8 `c` in the given string `str`.
*/
//!@{
t_size						StringUTF8_Count_Char(t_utf8 const* str, t_utf32 c);
#define c_mbscount_char		StringUTF8_Count_Char
//!@}

//!@doc Count the total occurences of chars from `charset` in the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The amount of occurences of chars in `charset` in the given string `str`.
*/
//!@{
t_size						StringUTF8_Count_Charset(t_utf8 const* str, t_utf8 const* charset);
#define c_mbscount_cset		StringUTF8_Count_Charset
//!@}

//!@doc Count the total occurences of the given string `query` in the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The amount of occurences of `query` in the given string `str`.
*/
//!@{
t_size						StringUTF8_Count_String(t_utf8 const* str, t_utf8 const* query);
#define c_mbscount_str		StringUTF8_Count_String
//!@}



/*============================================================================*\
||                              String Searching                              ||
\*============================================================================*/

//!@doc Finds the first occurence of the given char `c` inside the given string `str`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strchr} but with support for unicode if t_utf8 is of type t_utf8
**
**	@returns
**	The first occurence of the given char `c` within `str`,
**	or `NULL` if no char matched.
*/
//!@{
t_utf8*							StringUTF8_Find_Char(t_utf8 const* str, t_utf32 c);
#define c_mbschr				StringUTF8_Find_Char
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
t_utf8*							StringUTF8_Find_Charset(t_utf8 const* str, t_utf8 const* charset);
#define c_mbspbrk				StringUTF8_Find_Charset
#define c_mbschrset				StringUTF8_Find_Charset
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
t_utf8*							StringUTF8_Find_String(t_utf8 const* str, t_utf8 const* query);
#define c_mbsstr				StringUTF8_Find_String
//!@}



//!@doc Finds the last occurence of the given char `c` inside the given string `str`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strrchr}
**
**	@returns
**	The last occurence of the given char `c` within `str`,
**	or `NULL` if no char matched.
*/
//!@{
t_utf8*							StringUTF8_Find_R_Char(t_utf8 const* str, t_utf32 c);
#define c_mbsrchr				StringUTF8_Find_R_Char
#define StringUTF8_FindLast_Char	StringUTF8_Find_R_Char
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
t_utf8*							StringUTF8_Find_R_Charset(t_utf8 const* str, t_utf8 const* charset);
#define c_mbsrpbrk				StringUTF8_Find_R_Charset
#define c_mbsrchrset			StringUTF8_Find_R_Charset
#define StringUTF8_FindLast_Charset	StringUTF8_Find_R_Charset
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
t_utf8*							StringUTF8_Find_R_String(t_utf8 const* str, t_utf8 const* query);
#define c_mbsrstr				StringUTF8_Find_R_String
#define StringUTF8_FindLast_String	StringUTF8_Find_R_String
//!@}



//!@doc Finds the first occurence of the given char `c` inside the first `n` chars of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The first occurence of the given char `c` inside the given string `str`,
**	or `NULL` if no char matched. (checks only `n` chars in `str`).
*/
//!@{
t_utf8*							StringUTF8_Find_N_Char(t_utf8 const* str, t_utf32 c, t_size n);
#define c_mbsnchr				StringUTF8_Find_N_Char
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
t_utf8*							StringUTF8_Find_N_Charset(t_utf8 const* str, t_utf8 const* charset, t_size n);
#define c_mbsnpbrk				StringUTF8_Find_N_Charset
#define c_mbsnchrset			StringUTF8_Find_N_Charset
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
t_utf8*							StringUTF8_Find_N_String(t_utf8 const* str, t_utf8 const* query, t_size n);
#define c_mbsnstr				StringUTF8_Find_N_String
//!@}



//!@doc Finds the first occurence of the given char `c` inside the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The index of the first occurrence at which `c` is found in `str`,
**	or -1 if `c` does not exist in `str`.
*/
//!@{
t_sintmax							StringUTF8_IndexOf_Char(t_utf8 const* str, t_utf32 c);
#define c_mbsichr					StringUTF8_IndexOf_Char
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
t_sintmax							StringUTF8_IndexOf_Charset(t_utf8 const* str, t_utf8 const* charset);
#define c_mbsipbrk					StringUTF8_IndexOf_Charset
#define c_mbsichrset				StringUTF8_IndexOf_Charset
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
t_sintmax							StringUTF8_IndexOf_String(t_utf8 const* str, t_utf8 const* query);
#define c_mbsistr					StringUTF8_IndexOf_String
//!@}



//!@doc Finds the last occurence of the given char `c` inside the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The last occurence of the given char `c` within `str`,
**	or `NULL` if no char matched.
*/
//!@{
t_sintmax							StringUTF8_IndexOf_R_Char(t_utf8 const* str, t_utf32 c);
#define c_mbsirchr					StringUTF8_IndexOf_R_Char
#define StringUTF8_LastIndexOf_Char		StringUTF8_IndexOf_R_Char
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
t_sintmax							StringUTF8_IndexOf_R_Charset(t_utf8 const* str, t_utf8 const* charset);
#define c_mbsirpbrk					StringUTF8_IndexOf_R_Charset
#define c_mbsirchrset				StringUTF8_IndexOf_R_Charset
#define StringUTF8_LastIndexOf_Charset	StringUTF8_IndexOf_R_Charset
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
t_sintmax							StringUTF8_IndexOf_R_String(t_utf8 const* str, t_utf8 const* query);
#define c_mbsirstr					StringUTF8_IndexOf_R_String
#define StringUTF8_LastIndexOf_String	StringUTF8_IndexOf_R_String
//!@}



//!@doc Finds the first occurence of the given char `c` inside the first `n` chars of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The first occurence of the given char `c` within `str`,
**	or `NULL` if no char matched. (checks only `n` chars in `str`).
*/
//!@{
t_sintmax							StringUTF8_IndexOf_N_Char(t_utf8 const* str, t_utf32 c, t_size n);
#define c_mbsinchr					StringUTF8_IndexOf_N_Char
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
t_sintmax							StringUTF8_IndexOf_N_Charset(t_utf8 const* str, t_utf8 const* charset, t_size n);
#define c_mbsinpbrk					StringUTF8_IndexOf_N_Charset
#define c_mbsinchrset				StringUTF8_IndexOf_N_Charset
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
t_sintmax							StringUTF8_IndexOf_N_String(t_utf8 const* str, t_utf8 const* query, t_size n);
#define c_mbsinstr					StringUTF8_IndexOf_N_String
//!@}



/*============================================================================*\
||                              String Replacements                           ||
\*============================================================================*/

#if 0 // These functions do not yet exist and/or are a work in progress

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
t_utf8*					StringUTF8_Remove(t_utf8 const* str, t_utf8 const* query);
#define c_mbsremove		StringUTF8_Remove
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
t_utf8*						StringUTF8_Replace_Char(t_utf8 const* str, t_utf8 const* char_old, t_utf8* const char_new);
#define c_mbsrep_char		StringUTF8_Replace_Char
//!@}

//!@doc Replaces every occurence inside `str` of any char in `charset_old` with the corresponding char in `charset_new`
/*!
**	@nonstd
**
**	@returns
**	A new null-terminated string which is a copy of `str`,
**	in which every char in the `old` charset is replaced by the
**	corresponding character in the `new` charset (at the same glyph index).
*/
//!@{
_MALLOC()
t_utf8*						StringUTF8_Replace_Charset(t_utf8 const* str, t_utf8 const* cset_old, t_utf8 const* cset_new);
#define c_mbsrep_cset		StringUTF8_Replace_Charset
//!@}

//!@doc Replaces every occurence inside `str` of the given string `str_old` with `str_new`
/*!
**	@nonstd
**
**	@see `stringarray.h` -> StringUTF8_Split_String() for extra notes.
**
**	@returns
**	A new null-terminated string which is a copy of `str`,
**	in which every occurence of the string `old` is replaced with `new`.
*/
//!@{
_MALLOC()
t_utf8*						StringUTF8_Replace_String(t_utf8 const* str, t_utf8 const* str_old, t_utf8 const* str_new);
#define c_mbsrep_str		StringUTF8_Replace_String
//!@}

#endif

/*============================================================================*\
||                      String Concatenation Operations                       ||
\*============================================================================*/

#if 0 // These functions do not yet exist and/or are a work in progress

//!@doc Concatenates two strings into a new one
/*!
**	@nonstd
**
**	@returns
**	A new null-terminated string which is the concatenation of `str1` and `str2`.
*/
//!@{
_MALLOC()
t_utf8*					StringUTF8_Concat(t_utf8 const* str1, t_utf8 const* str2);
#define c_mbsconcat		StringUTF8_Concat
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
t_utf8*					StringUTF8_Append(t_utf8* *dest, t_utf8 const* src);
#define c_mbsappend		StringUTF8_Append
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
t_utf8*					StringUTF8_Prepend(t_utf8 const* src, t_utf8* *dest);
#define c_mbsprepend	StringUTF8_Prepend
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
t_utf8*					StringUTF8_Merge(t_utf8* *a_str1, t_utf8* *a_str2);
#define c_mbsmerge		StringUTF8_Merge
//!@}



//!@doc Concatenates the given set of strings `strarr`, putting the given separator string `sep` between each
/*!
**	@nonstd
**	
**	This function is the inverse operation of the StringUTF8_Split() function.
**
**	@param	strarr	The array of strings to join together (terminated by a `NULL` pointer).
**	@param	sep		The separator string, which is to be added between eahc joined string.
**	@returns
**	A new null-terminated string which is the concatenation of all the strings contained in
**	the given string array `strarr`, with the `sep` separator string in-between each string.
*/
//!@{
_MALLOC()
t_utf8*					StringUTF8_Join(t_utf8 const** strarr, t_utf8 const* sep);
#define c_mbsjoin		StringUTF8_Join
//!@}

#endif

/*============================================================================*\
||                           String In-Place Editing                          ||
\*============================================================================*/

#if 0 // These functions do not yet exist and/or are a work in progress

//!@doc Reallocates the given string `dest`, inserting the string `src` at the given `index`.
/*!
**	@nonstd
**
**	Inserts the string `src` at index `index` in `dest`; deletes `dest` and
**	replaces it with the result. Also returns the result.
*/
//!@{
t_utf8*							StringUTF8_Insert_InPlace(t_utf8* *dest, t_utf8 const* src, t_u32 index);
#define c_mbsinsert_inplace		StringUTF8_Insert_InPlace
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
void								StringUTF8_Replace_Char_InPlace(t_utf8* str, t_utf32 char_old, t_utf32 char_new);
#define c_mbsrep_char_inplace		StringUTF8_Replace_Char_InPlace
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
void								StringUTF8_Replace_Charset_InPlace(t_utf8* str, t_utf8 const* charset_old, t_utf8 const* charset_new);
#define c_mbsrep_cset_inplace		StringUTF8_Replace_Charset_InPlace
//!@}

//!@doc Replaces every occurence in `str` of `str_old` with `str_new`
/*!
**	@nonstd
**
**	@see `stringarray.h` -> StringUTF8_Split_String() for extra notes.
*/
//!@{
void								StringUTF8_Replace_String_InPlace(t_utf8* *a_str, t_utf8 const* str_old, t_utf8 const* str_new);
#define c_mbsrep_str_inplace		StringUTF8_Replace_String_InPlace
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
t_utf8*							StringUTF8_Map_InPlace(t_utf8* *a_str, t_utf32 (*map)(t_utf32));
#define c_mbsmap_inplace		StringUTF8_Map_InPlace
//!@}

#endif

/*============================================================================*\
||                        String Whitespace Operations                        ||
\*============================================================================*/

#if 0 // These functions do not yet exist and/or are a work in progress

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
t_utf8*					StringUTF8_Trim(t_utf8 const* str, t_utf8 const* charset);
#define c_mbstrim		StringUTF8_Trim
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
t_utf8*					StringUTF8_Trim_L(t_utf8 const* str, t_utf8 const* charset);
#define c_mbstriml		StringUTF8_Trim_L
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
t_utf8*					StringUTF8_Trim_R(t_utf8 const* str, t_utf8 const* charset);
#define c_mbstrimr		StringUTF8_Trim_R
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
t_utf8*					StringUTF8_Pad(t_utf8 const* str, t_utf32 c, t_size length);
#define c_mbspad		StringUTF8_Pad
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
t_utf8*					StringUTF8_Pad_L(t_utf8 const* str, t_utf32 c, t_size length);
#define c_mbspadl		StringUTF8_Pad_L
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
t_utf8*					StringUTF8_Pad_R(t_utf8 const* str, t_utf32 c, t_size length);
#define c_mbspadr		StringUTF8_Pad_R
//!@}

#endif

/*============================================================================*\
||                          Other String Operations                           ||
\*============================================================================*/



//!@doc Get an inverted version of the given string `str`
/*!
**	@nonstd
**
**	@returns
**	A newly allocated string which is a copy of the given string `str`,
**	but in reverse order (except for the \0 terminator, obviously).
*/
//!@{
_MALLOC()
t_utf8*					StringUTF8_Reverse(t_utf8 const* str);
#define c_mbsrev		StringUTF8_Reverse
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
t_utf8*					StringUTF8_Insert(t_utf8 const* dest, t_utf8 const* src, t_size index);
#define c_mbsinsert		StringUTF8_Insert
//!@}



//!@doc Get a subsection which is `n` chars long of the given string `str`, starting at `index`
/*!
**	@nonstd
**
**	TODO: Split a version based on what indexing is used: bytes or glyphs ?
**
**	@returns
**	A newly allocated string which is a subsection of `str`,
**	starting at position `index` and copying `n` characters.
*/
//!@{
_MALLOC()
t_utf8*					StringUTF8_Sub(t_utf8 const* str, t_size index, t_size n);
#define c_mbssub		StringUTF8_Sub
//!@}



/*============================================================================*\
||                           Functional Operations                            ||
\*============================================================================*/

#if 0 // These functions do not yet exist and/or are a work in progress

//!@doc Calls a custom function `f` for each character of the given string `str`
/*!
**	@nonstd
**
**	Iterates upon each character of the given string `str`,
**	applying the given function `f` to each of its characters.
*/
//!@{
void					StringUTF8_Iterate(t_utf8* str, void (*f)(t_utf32 c));
#define c_mbsiter		StringUTF8_Iterate
//!@}

//!@doc Calls a custom function `f` for each character of the given string `str`
/*!
**	@nonstd
**
**	Iterates upon each character of the given string `str`, (with index information)
**	applying the function `f` to each of its chars.
*/
//!@{
void					StringUTF8_Iterate_I(t_utf8* str, void (*f)(t_utf32 c, t_size index));
#define c_mbsiiter		StringUTF8_Iterate_I
//!@}



// TODO: Handle the unconvenient cases where a single glyph could be multiple unicode code points....
// We might want to make a special type to represent a 'glyph' ? which would be a null-terminated `t_utf32 *` ?

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
t_utf8*					StringUTF8_Map(t_utf8 const* str, t_utf32 (*map)(t_utf32 c));
#define c_mbsmap		StringUTF8_Map
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
t_utf8*					StringUTF8_Map_I(t_utf8 const* str, t_utf32 (*map)(t_utf32 c, t_size index));
#define c_mbsimap		StringUTF8_Map_I
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
t_utf8*					StringUTF8_Filter(t_utf8 const* str, t_bool (*filter)(t_utf8 c));
#define c_mbsfilter		StringUTF8_Filter
//!@}

//!@doc Creates a new string from `str`, only keeping codepoints when the custom function `filter` returns `TRUE`
/*!
**	@nonstd
**
**	@returns
**	A new string by iterating upon the string `str`, (with index information)
**	removing any chars for which the given `filter` function returns `FALSE`.
*/
//!@{
_MALLOC()
t_utf8*					StringUTF8_Filter_I(t_utf8 const* str, t_bool (*filter)(t_utf32 c, t_size index));
#define c_mbsifilter	StringUTF8_Filter_I
//!@}

#endif

/*! @endgroup */
HEADER_END
#endif
