/*============================================================================*\
||                                            ______________________________  ||
||  libccc/text/escape.h                     |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_TEXT_ESCAPE_H
#define __LIBCCC_TEXT_ESCAPE_H
/*!@group{libccc_text_escape,20,libccc/text/escape.h}
**
**	This header defines functions for converting to/from strings with escaped characters
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/


// String Escaping Operations
#define String_Print                   (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_ToAsciiEscapedBuf))
#define String_ToAsciiEscaped          (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_ToAsciiEscaped))
#define String_ToAsciiEscapedBuf       (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_ToAsciiEscapedBuf))
#define String_ToJsonEscaped           (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_ToJsonEscaped))
#define String_ToJsonEscapedBuf        (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_ToJsonEscapedBuf))
#define String_ToEscaped               (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_ToEscaped))
#define String_ToEscaped_e             (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_ToEscaped_e))
#define String_ToEscapedBuf            (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_ToEscapedBuf))
#define String_ToEscapedBuf_e          (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_ToEscapedBuf_e))
#define String_Parse                   (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_Parse))
#define String_FromEscape              (CONCAT(CONCAT(String,LIBCONFIG_STRING_FORMAT),_FromEscape))



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
t_bool		ForceEncodingFor_NonPrintable(t_utf8 const* str);
t_bool		ForceEncodingFor_NonASCII(t_utf8 const* str);
t_bool		ForceEncodingFor_NonASCIIOrNonPrintable(t_utf8 const* str);



/*============================================================================*\
||                                  Functions                                 ||
\*============================================================================*/

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
#define c_mbstoutf8esc	StringUTF8_ToASCIIEscaped


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
#define c_mbstojsonesc	StringUTF8_ToJsonEscaped

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

#define c_mbstoesc	StringUTF8_ToEscaped

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

#define c_mbstoesc_e	StringUTF8_ToEscaped_e

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



/*! @endgroup */
HEADER_END
#endif
