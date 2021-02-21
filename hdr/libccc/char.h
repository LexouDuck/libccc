/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/char.h                            |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_CHAR_H
#define __LIBCCC_CHAR_H
/*!@group{libccc_char}
** @{
**	This header defines all the functions/sets related to single ASCII chars.
**
**	@isostd{https://en.cppreference.com/w/c/language/ascii}
**	- https://en.wikipedia.org/wiki/UTF-8
**	- https://en.wikipedia.org/wiki/UTF-16
**	- https://en.wikipedia.org/wiki/UTF-32
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

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

//! Primitive type: `char`, ie: a text character (1 byte: ANSI/ASCII)
/*!
**	@isostd{https://en.cppreference.com/w/c/string/byte}
*/
typedef char	t_char;
TYPEDEF_ALIAS(	t_char, CHAR, PRIMITIVE)

//! Primitive type: Unicode UTF-8 character (variable length: 1 to 4 bytes)
/*!
**	@isostd{https://en.cppreference.com/w/c/string/multibyte}
*/
typedef char		t_utf8;
TYPEDEF_ALIAS(		t_utf8, UTF8, PRIMITIVE)

//! Primitive type: Unicode UTF-16 character (variable length: 2 or 4 bytes)
/*!
**	@isostd{https://en.cppreference.com/w/c/string/multibyte/char16_t}
**	@isostd{https://en.cppreference.com/w/c/string/multibyte}
*/
typedef uint_least16_t	t_utf16;
TYPEDEF_ALIAS(			t_utf16, UTF16, PRIMITIVE)

//! Primitive type: Unicode UTF-32 character code point value (fixed length: 4 bytes)
/*!
**	@isostd{https://en.cppreference.com/w/c/string/multibyte/char32_t}
**	@isostd{https://en.cppreference.com/w/c/string/wide}
*/
typedef uint_least32_t	t_utf32;
TYPEDEF_ALIAS(			t_utf32, UTF32, PRIMITIVE)




/*
**	Define string literals for alphabet characters
*/
//! Set of characters for the lowercase latin alphabet
#define CHARSET_LOWERCASE	"abcdefghijklmnopqrstuvwxyz"
//! Set of characters for the uppercase latin alphabet
#define CHARSET_UPPERCASE	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//! Set of characters for the latin alphabet (both lowercase and uppercase)
#define CHARSET_ALPHABET	"aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ"

/*
**	Define string literals for some of the commonly used number bases.
*/
#define CHARSET_BINARY		"01"
#define CHARSET_OCTAL		"01234567"
#define CHARSET_DECIMAL		"0123456789"
#define CHARSET_HEX_LOWER	"0123456789abcdef"
#define CHARSET_HEX_UPPER	"0123456789ABCDEF"
#define CHARSET_HEX			CHARSET_HEXADECIMAL
#define CHARSET_HEXADECIMAL	"0123456789aAbBcCdDeEfF"

//! A charset containing all of the different whitespace characters
#define CHARSET_WHITESPACE	" \t\n\r\v\f"

//! A charset containing all of the ASCII punctuation characters
#define CHARSET_PUNCTUATION	"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"



/*
** ************************************************************************** *|
**                              Character Checks                              *|
** ************************************************************************** *|
*/

//! Check if the given char `c` is a letter (lowercase or uppercase)
/*!
**	Check if the given char `c` is a letter (lowercase or uppercase)
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns 1(TRUE) if the given char `c` is a letter (lowercase or uppercase),
**			and returns 0(FALSE) otherwise.
*/
t_bool					Char_IsLetter(t_utf32 c);
#define c_isalpha		Char_IsLetter
#define Char_IsAlpha	Char_IsLetter

//! Check if the given char `c` is a uppercase letter character
/*!
**	Check if the given char `c` is a uppercase letter character
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns 1(TRUE) if the given char `c` is a uppercase letter character,
**			and returns 0(FALSE) otherwise.
*/
t_bool					Char_IsUppercase(t_utf32 c);
#define c_isupper		Char_IsUppercase
#define Char_IsUpper	Char_IsUppercase

//! Check if the given char `c` is an lowercase letter character
/*!
**	Check if the given char `c` is an lowercase letter character
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns 1(TRUE) if the given char `c` is an lowercase letter character,
**			and returns 0(FALSE) otherwise.
*/
t_bool					Char_IsLowercase(t_utf32 c);
#define c_islower		Char_IsLowercase
#define Char_IsLower	Char_IsLowercase

//! Check if the given char `c` is alphanumeric (letter or digit) character
/*!
**	Check if the given char `c` is alphanumeric (letter or digit) character
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns 1(TRUE) if the given char `c` is alphanumeric (letter or digit),
**			and returns 0(FALSE) otherwise.
*/
t_bool					Char_IsAlphaNumeric(t_utf32 c);
#define c_isalnum		Char_IsAlphaNumeric
#define Char_IsAlNum	Char_IsAlphaNumeric

//! Check if the given char `c` is a decimal digit character
/*!
**	Check if the given char `c` is a decimal digit character
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns 1(TRUE) if the given char `c` is a numerical digit character,
**			and returns 0(FALSE) otherwise.
*/
t_bool							Char_IsDigit(t_utf32 c);
#define c_isdigit				Char_IsDigit
#define Char_IsDigit			Char_IsDigit
#define Char_IsDigit_Dec		Char_IsDigit
#define Char_IsDigit_Decimal	Char_IsDigit

//! Check if the given char `c` is a hexadecimal digit character (0-9 or A-F, lowercase or uppercase)
t_bool								Char_IsDigit_Hex(t_utf32 c);
#define c_isdigit_hex				Char_IsDigit_Hex
#define Char_IsDigit_Hexadecimal	Char_IsDigit_Hex

//! Check if the given char `c` is a octal-base digit character (ie: '0' to '7')
t_bool								Char_IsDigit_Oct(t_utf32 c);
#define c_isdigit_oct				Char_IsDigit_Oct
#define Char_IsDigit_Octal			Char_IsDigit_Oct

//! Check if the given char `c` is a binary-base digit character (ie: '0' or '1')
t_bool								Char_IsDigit_Bin(t_utf32 c);
#define c_isdigit_bin				Char_IsDigit_Bin
#define Char_IsDigit_Binary			Char_IsDigit_Bin

//! Check if the given char `c` is whitespace character (' ','\\t','\\r','\\n','\\f','\\v')
/*!
**	Check if the given char `c` is whitespace character (' ','\\t','\\r','\\n','\\f','\\v')
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns 1(TRUE) if the given char `c` is whitespace character: ' ','\\t','\\r','\\n','\\f','\\v'
**			(carriage return, newline, form feed, vertical tab, tab, or space), and returns 0(FALSE) otherwise.
*/
t_bool						Char_IsSpace(t_utf32 c);
#define c_isspace			Char_IsSpace
#define Char_IsWhiteSpace	Char_IsSpace

//! Check if the given char `c` is a punctuation character
/*!
**	Check if the given char `c` is a punctuation character
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns 1(TRUE) if the given char `c` is a punctuation character,
**			and returns 0(FALSE) otherwise.
*/
t_bool					Char_IsPunctuation(t_utf32 c);
#define c_ispunct		Char_IsPunctuation
#define Char_IsPunct	Char_IsPunctuation

//! Check if the given char `c` is a printable ASCII character
/*!
**	Check if the given char `c` is a printable ASCII character
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns 1(TRUE) if the given char `c` is a printable ASCII character,
**			(0x20 <= c && c <= 0x7E) and returns 0(FALSE) otherwise.
*/
t_bool					Char_IsPrintable(t_utf32 c);
#define c_isprint		Char_IsPrintable
#define Char_IsPrint	Char_IsPrintable

//! Check if the given char `c` is an ASCII-compatible char (non-Unicode)
/*!
**	Check if the given char `c` is an ASCII-compatible char (non-Unicode)
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns 1(TRUE) if the given char `c` has a value between 0 and 127,
**			(0x00 <= c && c <= 0x7F) and returns 0(FALSE) otherwise.
*/
t_bool				Char_IsASCII(t_utf32 c);
#define c_isascii	Char_IsASCII



//! Check if the given char `c` is contained in the given 'charset'
/*!
**	Check if the given char `c` is contained in the given 'charset'
**
**	@param	c		The character to check (ASCII or Unicode)
**	@param	charset	String, the set of characters to look through (the '\0' terminator ends the charset)
**	@returns 1(TRUE) if the given char `c` is a printable ASCII character,
**			(0x20 <= c && c <= 0x7E) and returns 0(FALSE) otherwise.
*/
t_bool					Char_IsInCharset(t_utf32 c, t_char const* charset);
#define c_isincharset	Char_IsInCharset
// TODO make charset UTF-8 compatible



/*
** ************************************************************************** *|
**                           Character Substitutions                          *|
** ************************************************************************** *|
*/

//! Get the uppercase version of the given char `c`
/*!
**	Get the uppercase version of the given char `c`
**
**	@param	c	The character to uppercase-ify (ASCII only)
**	@returns the uppercase equivalent of the given character `c`
**			(nothing is done if `c` is not a letter character).
*/
t_char					Char_ToUppercase(t_char c);
#define c_toupper		Char_ToUppercase
#define Char_ToUpper	Char_ToUppercase

//! Get the lowercase version of the given char `c`
/*!
**	Get the lowercase version of the given char `c`
**
**	@param	c	The character to lowercase-ify (ASCII only)
**	@returns the lowercase equivalent of the given character `c`
**			(nothing is done if `c` is not a letter character).
*/
t_char					Char_ToLowercase(t_char c);
#define c_tolower		Char_ToLowercase
#define Char_ToLower	Char_ToLowercase

// TODO add Char_ToMixedCase



/*
** ************************************************************************** *|
**                             Encoding Conversions                           *|
** ************************************************************************** *|
*/

//! Converts the given Unicode code point value `c` to its UTF-8 equivalent representation
/*!
**	Converts the given char `c` to UTF-8 representation, and writes it to 'dest'
**	@param	c		The character to convert (UTF-32 Unicode code point value)
**	@param	dest	The pointer at which to write the resulting UTF-8 char
**					(you must ensure that at least 4 bytes are writable to 'dest')
**	@returns The size (in bytes) of the character written (can be 0, 1, 2, 3, or 4)
*/
t_size					Char_ToUTF8(t_utf8* dest, t_utf32 c);
#define c_to_utf8		Char_ToUTF8

//! Converts the given Unicode code point value `c` to its UTF-16 equivalent representation
/*!
**	Converts the given char `c` to UTF-16 representation, and writes it to 'dest'
**	@param	c		The character to convert (UTF-32 Unicode code point value)
**	@param	dest	The pointer at which to write the resulting UTF-16 char
**					(you must ensure that at least 4 bytes are writable to 'dest')
**	@returns The size (in bytes) of the character written (can be 0, 2, or 4)
*/
t_size					Char_ToUTF16(t_utf16* dest, t_utf32 c);
#define c_to_utf16		Char_ToUTF16



//! Returns the Unicode code point value (UTF-32) for the UTF-8 character pointed to by 'str'
/*!
**	Reads up to 4 bytes in 'str', and converts these bytes to a Unicode code point value
**	@param	str		The string from which to read a UTF-8 character
**	@returns The Unicode code point value for the character pointed to by 'str'
*/
t_utf32					UTF8_Get(t_utf8 const* str);
#define c_utf8get		UTF8_Get

//! Returns the Unicode code point value (UTF-32) for the UTF-16 character pointed to by 'str'
/*!
**	Reads 2 or 4 bytes in 'str', and converts these bytes to a Unicode code point value
**	@param	str		The string from which to read a UTF-16 character
**	@returns The Unicode code point value for the character pointed to by 'str'
*/
t_utf32					UTF16_Get(t_utf16 const* str);
#define c_utf16get		UTF16_Get



/*! @} */
HEADER_END
#endif
