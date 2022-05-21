/*============================================================================*\
||                                            ______________________________  ||
||  libccc/stringutf8.h                      |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_STRING_UTF8_H
#define __LIBCCC_STRING_UTF8_H
/*!@group{libccc_mbstringUTF8,18,libccc/string.h}
**
**	This header defines the common standard UTF8 text string manipulation functions.
**
**	@isostd{C,https://en.cppreference.com/w/c/string/byte#StringUTF8_manipulation}
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"

#include "libccc/text/char_unicode.h"

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
typedef t_utf8*	p_strUTF8;
typedef t_utf8*	p_stringUTF8;
//!@}



/* TODO function pointers
typedef void	(*f_string_UTF8_iterate)		(t_utf8* )
typedef void	(*f_string_UTF8_iterate_i)		(unsigned int, t_utf8* )
typedef t_utf8	(*f_string_UTF8_map)			(t_utf8)
typedef t_utf8	(*f_string_UTF8_map_i)			(unsigned int, t_utf8)
*/



#define StringUTF8_Print	StringUTF8_ToASCIIEscapedBuf

//! Creates a new string from `str`, replacing special characters with ascii escape-sequences
/*!
**	@nonstd
**
**	Returns a new null-terminated string where every non-printable or non-ascii
**	character of `str` is replaced by either its "normal" escape sequence (if 
**	available) or encodes the character with either a `\xFF`, `\uFFFF`, or `\UFFFFFFFF`
**	escape sequence if no simple alias sequence exists (like `"\n"` for instance).
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
t_ascii*					StringUTF8_ToASCIIEscaped(t_utf8 const* str);
#define c_mbstrtoUTF8esc	StringUTF8_ToASCIIEscaped


//! Equivalent of `StringUTF8_ToUtf8Escaped` but writes in the given `dest` buffer.
/*!
**	@nonstd
**
**	One can call with NULL `dest` to get the size it would write
**
**	@returns
**	The amount of byte written to `dest`, or that would have been written to `dest` if `dest` wasn't NULL
*/
t_size					StringUTF8_ToASCIIEscapedBuf(t_ascii *dest, size_t max_writelen, t_utf8 const* str);

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
t_utf8*					StringUTF8_ToJsonEscaped(t_utf8 const* str);
#define c_mbstrtojsonesc	StringUTF8_ToJsonEscaped

//! Equivalent of `StringUTF8_ToJsonEscaped` but writes in the given `dest` buffer.
/*!
**	@nonstd
**
**	One can call with NULL `dest` to get the size it would write
**
**	@returns
**	The amount of byte written to `dest`, or that would have been written to `dest` if `dest` wasn't NULL
*/
t_size					StringUTF8_ToJsonEscapedBuf(t_utf8 *dest, size_t max_writelen, t_utf8 const* str);


//! Function to encode (or 'spell out') a unicode character to an UTF8 string
/*!
**	if `dest` is not NULL, writes down the UTF8 string to `dest` without a final '\0'
**	One can call the function with a NULL `dest` to just get the number of bytes that would be written to `dest`, and ensure the buffer is big enough
**
**	@param	dest	The buffer in which the output will be written, if non NULL
**	@param	c		The unicode character to encode
**	@returns
**	`ERROR` if the given character cannot be encoded, or
**	The number of byte written on `dest`, or that would have been written to `dest` if `dest` wasn't NULL
*/
typedef size_t (*f_char_encoder)(t_utf8 *dest, t_utf32 c);

#define ENCODER_xFF				CharUTF32_ToEscaped_xFF
#define ENCODER_uFFFF			CharUTF32_ToEscaped_uFFFF
#define ENCODER_UFFFFFFFF		CharUTF32_ToEscaped_UFFFFFFFF
#define ENCODER_smart			CharUTF32_ToEscaped_smart


//! Functor to determine if given (potentially multi-byte) character should be encoded by the `f_char_encoder`
typedef t_bool (*f_force_encoding_for)(t_utf8 const* str);

// TODO: These should take a utf32 instead. That would also allow to be used with ascii without cast
t_bool ForceEncodingFor_NonPrintable(t_utf8 const* str);
t_bool ForceEncodingFor_NonASCII(t_utf8 const* str);
t_bool ForceEncodingFor_NonASCIIOrNonPrintable(t_utf8 const* str);



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
t_utf8*	StringUTF8_ToEscaped(
		t_utf8 const* str,
		t_utf8 const* charset,
		t_utf8 const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder);

#define c_mbstrtoesc	StringUTF8_ToEscaped

//! Exhaustive version of `StringUTF8_ToEscaped`
/*
**	@see StringUTF8_ToEscaped, only additional parameters are documented here
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
t_utf8*	StringUTF8_ToEscaped_e(
		t_size *out_len,
		t_size *out_readlen,
		t_size max_resultlen,
		t_utf8 const* str,
		t_utf8 const* charset,
		t_utf8 const* const* aliases,
		f_force_encoding_for  force_encoding_for,
		f_char_encoder char_encoder);

#define c_mbstrtoesc_e	StringUTF8_ToEscaped_e

//! Same as `StringUTF8_ToEscaped` except it will write the escaped string directly to `dest`
/*
**	@see StringUTF8_ToEscaped, only additional parameters are documented here
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
t_size StringUTF8_ToEscapedBuf(
		t_utf8 *dest,
		size_t max_writelen,
		t_utf8 const* str,
		t_utf8 const* charset,
		t_utf8 const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder);

//! Exhaustive version of `StringUTF8_ToEscapedBuf`
/*
**	@see StringUTF8_ToEscapedBuf
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
t_size StringUTF8_ToEscapedBuf_e(
		t_utf8 *dest,
		t_size *out_readlen,
		size_t max_writelen,
		t_utf8 const* str,
		t_utf8 const* charset,
		t_utf8 const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder);

//!@}




// These functions do not yet exist and are a work in progress on the `StringUTF8` branch
#if 0

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
t_utf8*				StringUTF8_New(t_size n);
#define c_mbstrnew		StringUTF8_New
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
#define c_mbstrcnew	StringUTF8_New_C
//!@}



//!@doc Deallocates the given string `str`.
/*!
**	@nonstd
*/
//!@{
void				StringUTF8_Free(t_utf8* str);
#define c_mbstrfree	StringUTF8_Free
//!@}

//!@doc Deallocates the string pointed to by `*a_str`, and sets the pointer to `NULL`.
/*!
**	@nonstd
*/
//!@{
void				StringUTF8_Delete(t_utf8* *a_str);
#define c_mbstrdel		StringUTF8_Delete
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
#define c_mbstrdup		StringUTF8_Duplicate
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
#define c_mbstrndup	StringUTF8_Duplicate_N
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
#define c_mbstrchrdup	StringUTF8_Duplicate_Char
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
#define c_mbstrcstdup	StringUTF8_Duplicate_Charset
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
#define c_mbstrstrdup	StringUTF8_Duplicate_String
//!@}



//!@doc Clears the given string `str`, setting each byte to `'\0'`.
/*!
**	@nonstd
*/
//!@{
void				StringUTF8_Clear(t_utf8* str);
#define c_mbstrclr		StringUTF8_Clear
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
#define c_mbstrsetbytes	StringUTF8_SetBytes
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
void					StringUTF8_SetGlyphs(t_utf8* str, t_utf8 c);
#define c_mbstrsetglyphs	StringUTF8_SetGlyphs
//!@}

// TODO strnsetbytes() StringUTF8_SetBytes_N
// TODO strnsetglyphs() StringUTF8_SetGlyphs_N



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
t_utf8*			StringUTF8_Copy(t_utf8* dest, t_utf8 const* src);
#define c_mbstrcpy	StringUTF8_Copy
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
#define c_mbstrncpy	StringUTF8_Copy_N
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
#define c_mbstrlcpy	StringUTF8_Copy_L
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
#define c_mbstrcat	StringUTF8_Add
#define c_mbstradd	StringUTF8_Add
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
#define c_mbstrncat	StringUTF8_Add_N
#define c_mbstrnadd	StringUTF8_Add_N
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
#define c_mbstrlcat	StringUTF8_Add_L
#define c_mbstrladd	StringUTF8_Add_L
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
t_size				StringUTF8_Length(t_utf8 const* str, t_size *out_glyphcount);
#define c_mbstrlen	StringUTF8_Length
//!@}

//!@doc Get the length (in bytes) of a string, excluding final '\0', but at most `n` bytes 
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strlen}
**
**	@returns
**	`StringUTF8_Length(str)` if that is less than `n`, or `n` if there is no '\0' among the first `n` bytes of the string
*/
//!@{
t_size				StringUTF8_Length_N(t_utf8 const* str, t_size *out_glyphcount, t_size n);
#define c_mbstrnlen	StringUTF8_Length_N
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
#define c_mbstrequ		StringUTF8_Equals
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
#define c_mbstrnequ		StringUTF8_Equals_N
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
#define c_mbstriequ		StringUTF8_Equals_IgnoreCase
#define c_mbstrcaseequ	StringUTF8_Equals_IgnoreCase
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
#define c_mbstrniequ		StringUTF8_Equals_N_IgnoreCase
#define c_mbstrncaseequ	StringUTF8_Equals_N_IgnoreCase
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
#define c_mbstrcmp		StringUTF8_Compare
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
#define c_mbstrncmp		StringUTF8_Compare_N
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
#define c_mbstricmp		StringUTF8_Compare_IgnoreCase
#define c_mbstrcasecmp	StringUTF8_Compare_IgnoreCase
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
#define c_mbstrnicmp		StringUTF8_Compare_N_IgnoreCase
#define c_mbstrncasecmp	StringUTF8_Compare_N_IgnoreCase
//!@}

// TODO StringUTF8_CompareUntil_Char()
// TODO StringUTF8_CompareUntil_Charset()
// TODO StringUTF8_CompareUntil_String()



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
#define c_mbstrhas			StringUTF8_Has
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
#define c_mbstrhasonly		StringUTF8_HasOnly
//!@}



// TODO strspn()
// TODO strcspn()



//!@doc Count the total occurences of the given char `c` in the given string `str`
/*!
**	@nonstd
**
**	@returns
**	The amount of occurences of t_utf8 `c` in the given string `str`.
*/
//!@{
t_size						StringUTF8_Count_Char(t_utf8 const* str, t_utf32 c);
#define c_mbstrcount_char		StringUTF8_Count_Char
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
#define c_mbstrcount_cset		StringUTF8_Count_Charset
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
#define c_mbstrcount_str		StringUTF8_Count_String
//!@}



/*
** ************************************************************************** *|
**                              String Searching                              *|
** ************************************************************************** *|
*/

//!@doc Finds the first occurence of the given char `c` inside the given string `str`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strchr} but with support for unicode if t_utf8 is of type t_utf8
**
**	@returns
**	The first occurence of the given char `c` within `str`,
**	or `NULL` if no char matched.
*/
//!@{
t_utf8*							StringUTF8_Find_Char(t_utf8 const* str, t_utf32 c, t_size *out_glyphindex);
#define c_mbstrchr				StringUTF8_Find_Char
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
#define c_mbstrpbrk				StringUTF8_Find_Charset
#define c_mbstrchrset				StringUTF8_Find_Charset
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
#define c_mbstrstr				StringUTF8_Find_String
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
#define c_mbstrrchr				StringUTF8_Find_R_Char
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
#define c_mbstrrpbrk				StringUTF8_Find_R_Charset
#define c_mbstrrchrset			StringUTF8_Find_R_Charset
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
#define c_mbstrrstr				StringUTF8_Find_R_String
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
#define c_mbstrnchr				StringUTF8_Find_N_Char
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
#define c_mbstrnpbrk				StringUTF8_Find_N_Charset
#define c_mbstrnchrset			StringUTF8_Find_N_Charset
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
#define c_mbstrnstr				StringUTF8_Find_N_String
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
#define c_mbstrichr					StringUTF8_IndexOf_Char
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
#define c_mbstripbrk					StringUTF8_IndexOf_Charset
#define c_mbstrichrset				StringUTF8_IndexOf_Charset
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
#define c_mbstristr					StringUTF8_IndexOf_String
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
#define c_mbstrirchr					StringUTF8_IndexOf_R_Char
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
#define c_mbstrirpbrk					StringUTF8_IndexOf_R_Charset
#define c_mbstrirchrset				StringUTF8_IndexOf_R_Charset
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
#define c_mbstrirstr					StringUTF8_IndexOf_R_String
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
#define c_mbstrinchr					StringUTF8_IndexOf_N_Char
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
#define c_mbstrinpbrk					StringUTF8_IndexOf_N_Charset
#define c_mbstrinchrset				StringUTF8_IndexOf_N_Charset
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
#define c_mbstrinstr					StringUTF8_IndexOf_N_String
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
t_utf8*					StringUTF8_Remove(t_utf8 const* str, t_utf8 const* query);
#define c_mbstrremove		StringUTF8_Remove
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
#define c_mbstrrep_char		StringUTF8_Replace_Char
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
#define c_mbstrrep_cset		StringUTF8_Replace_Charset
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
#define c_mbstrrep_str		StringUTF8_Replace_String
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
t_utf8*					StringUTF8_Concat(t_utf8 const* str1, t_utf8 const* str2);
#define c_mbstrconcat		StringUTF8_Concat
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
#define c_mbstrappend		StringUTF8_Append
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
#define c_mbstrprepend	StringUTF8_Prepend
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
#define c_mbstrmerge		StringUTF8_Merge
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
#define c_mbstrjoin		StringUTF8_Join
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
t_utf8*							StringUTF8_Insert_InPlace(t_utf8* *dest, t_utf8 const* src, t_u32 index);
#define c_mbstrinsert_inplace		StringUTF8_Insert_InPlace
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
#define c_mbstrrep_char_inplace		StringUTF8_Replace_Char_InPlace
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
#define c_mbstrrep_cset_inplace		StringUTF8_Replace_Charset_InPlace
//!@}

//!@doc Replaces every occurence in `str` of `str_old` with `str_new`
/*!
**	@nonstd
**
**	@see `stringarray.h` -> StringUTF8_Split_String() for extra notes.
*/
//!@{
void								StringUTF8_Replace_String_InPlace(t_utf8* *a_str, t_utf8 const* str_old, t_utf8 const* str_new);
#define c_mbstrrep_str_inplace		StringUTF8_Replace_String_InPlace
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
#define c_mbstrmap_inplace		StringUTF8_Map_InPlace
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
t_utf8*					StringUTF8_Trim(t_utf8 const* str, t_utf8 const* charset);
#define c_mbstrtrim		StringUTF8_Trim
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
#define c_mbstrtriml		StringUTF8_Trim_L
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
#define c_mbstrtrimr		StringUTF8_Trim_R
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
#define c_mbstrpad		StringUTF8_Pad
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
#define c_mbstrpadl		StringUTF8_Pad_L
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
#define c_mbstrpadr		StringUTF8_Pad_R
//!@}



/*
** ************************************************************************** *|
**                          Other String Operations                           *|
** ************************************************************************** *|
*/



//! Creates a new string from `str`, replacing escape-sequences with their corresponding char value
/*!
**	@nonstd
**
**	Inverse of `StringUTF8_ToUtf8Escaped`
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
t_size							StringUTF8_Parse(t_utf8* *dest, t_utf8 const* str, t_size n, t_bool any_escape);
#define c_mbstrparse				StringUTF8_Parse
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
t_utf8*							StringUTF8_FromEscape(t_utf8 const* str, t_bool any_escape);
#define c_esctostr				StringUTF8_FromEscape
#define StringUTF8_Decode			StringUTF8_FromEscape
#define StringUTF8_FromPrintable	StringUTF8_FromEscape
//!@}

//!@}



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
#define c_mbstrrev		StringUTF8_Reverse
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
#define c_mbstrinsert		StringUTF8_Insert
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
#define c_mbstrsub		StringUTF8_Sub
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
void					StringUTF8_Iterate(t_utf8* str, void (*f)(t_utf32 c));
#define c_mbstriter		StringUTF8_Iterate
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
#define c_mbstriiter		StringUTF8_Iterate_I
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
#define c_mbstrmap		StringUTF8_Map
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
#define c_mbstrimap		StringUTF8_Map_I
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
#define c_mbstrfilter		StringUTF8_Filter
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
#define c_mbstrifilter	StringUTF8_Filter_I
//!@}

#endif // if 0

/*! @endgroup */
HEADER_END
#endif
