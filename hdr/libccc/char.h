/*============================================================================*\
||                                            ______________________________  ||
||  libccc/char.h                            |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_CHAR_H
#define __LIBCCC_CHAR_H
/*!@group{libccc_char,10,libccc/char.h}
**
**	This header defines all the functions/sets related to single ASCII chars.
**
**	@isostd{C,https://en.cppreference.com/w/c/string/byte}
**
**	@see
**	- libccc/text/ascii.h
**	- libccc/text/unicode.h
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#ifndef __NOSTD__
	#include <stdint.h>
#else
	typedef unsigned short	uint_least16_t;
	typedef unsigned long	uint_least32_t;
#endif

#include "libccc.h"

#include "libccc/text/ascii.h"
#include "libccc/text/unicode.h"

HEADER_CPP

#ifndef __LIBCCC_CHAR_T
#define __LIBCCC_CHAR_T

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! Primitive type: `char`, configurable (ASCII or UTF8)
/*!
**	@isostd{C,https://en.cppreference.com/w/c/string/byte}
*/
typedef t_ascii	t_char;
TYPEDEF_ALIAS(	t_char, CHAR, PRIMITIVE)



// TODO add option with wrapper functions for the ones in C11 <uchar.h>



//!@doc String literal macro: Set of all of the different whitespace characters
//!@{
#define CHARSET_SPACE		CHARSET_WHITESPACE
#define CHARSET_WHITESPACE	" \t\n\r\v\f"
//!@}

//!@doc String literal macro: Set of all of the ASCII punctuation characters
//!@{
#define CHARSET_PUNCT		CHARSET_PUNCTUATION
#define CHARSET_PUNCTUATION	"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
//!@}



//!@doc Set of characters for the lowercase latin alphabet
//!@{
#define CHARSET_LOWER		CHARSET_LOWERCASE
#define CHARSET_LOWERCASE	"abcdefghijklmnopqrstuvwxyz"
//!@}

//!@doc Set of characters for the uppercase latin alphabet
//!@{
#define CHARSET_UPPER		CHARSET_UPPERCASE
#define CHARSET_UPPERCASE	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//!@}

//!@doc Set of characters for the latin alphabet (both lowercase and uppercase)
//!@{
#define CHARSET_ALPHA		CHARSET_ALPHABET
#define CHARSET_ALPHABET	"aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ"
//!@}



//!@doc Set of characters for base-2 numbers (binary)
//!@{
#define CHARSET_BIN			CHARSET_BINARY
#define CHARSET_BINARY		"01"
//!@}

//!@doc Set of characters for base-8 numbers (octal)
//!@{
#define CHARSET_OCT			CHARSET_OCTAL
#define CHARSET_OCTAL		"01234567"
//!@}

//!@doc Set of characters for base-10 numbers (decimal)
//!@{
#define CHARSET_DEC			CHARSET_DECIMAL
#define CHARSET_DECIMAL		"0123456789"
#define CHARSET_DIGIT		CHARSET_DECIMAL
//!@}

//!@doc Set of characters for base-16 numbers (hexadecimal)
//!@{
#define CHARSET_HEX			CHARSET_HEXADECIMAL
#define CHARSET_HEXADECIMAL	"0123456789aAbBcCdDeEfF"
#define CHARSET_HEX_LOWER	"0123456789abcdef"
#define CHARSET_HEX_UPPER	"0123456789ABCDEF"
//!@}



#endif
#ifndef __LIBCCC_CHAR_F
#define __LIBCCC_CHAR_F

/*
** ************************************************************************** *|
**                              Character Checks                              *|
** ************************************************************************** *|
*/

//!@doc Check if the given char `c` is a letter character (lowercase or uppercase)
/*!
**	@see
**	- ASCII_IsLetter()
**	- UTF32_IsLetter()
*/
//!@{
#define					Char_IsLetter	CONCAT(LIBCONFIG_CHAR_NAME,_IsLetter)
#define c_isalpha		Char_IsLetter
#define Char_IsAlpha	Char_IsLetter
//!@}

//!@doc Check if the given char `c` is a uppercase letter character
/*!
**	@see
**	- ASCII_IsUppercase()
**	- UTF32_IsUppercase()
*/
//!@{
#define					Char_IsUppercase	CONCAT(LIBCONFIG_CHAR_NAME,_IsUppercase)
#define c_isupper		Char_IsUppercase
#define Char_IsUpper	Char_IsUppercase
//!@}

//!@doc Check if the given char `c` is an lowercase letter character
/*!
**	@see
**	- ASCII_IsLowercase()
**	- UTF32_IsLowercase()
*/
//!@{
#define					Char_IsLowercase	CONCAT(LIBCONFIG_CHAR_NAME,_IsLowercase)
#define c_islower		Char_IsLowercase
#define Char_IsLower	Char_IsLowercase
//!@}

//!@doc Check if the given char `c` is alphanumeric (letter or digit) character
/*!
**	@see
**	- ASCII_IsAlphaNumeric()
**	- UTF32_IsAlphaNumeric()
*/
//!@{
#define					Char_IsAlphaNumeric	CONCAT(LIBCONFIG_CHAR_NAME,_IsAlphaNumeric)
#define c_isalnum		Char_IsAlphaNumeric
#define Char_IsAlNum	Char_IsAlphaNumeric
//!@}



//!@doc Check if the given char `c` is a decimal digit character (ie: #CHARSET_DEC: `0123456789`)
/*!
**	@see
**	- ASCII_IsDigit_Decimal()
**	- UTF32_IsDigit_Decimal()
*/
//!@{
#define						Char_IsDigit_Decimal	CONCAT(LIBCONFIG_CHAR_NAME,_IsDigit)
#define c_isdigit			Char_IsDigit_Decimal
#define c_isdigitdec		Char_IsDigit_Decimal
#define Char_IsDigit		Char_IsDigit_Decimal
#define Char_IsDigit_Dec	Char_IsDigit_Decimal
//!@}

//!@doc Checks if the given char `c` is a hexadecimal digit character (ie: #CHARSET_HEX: `0123456789abcdefABCDEF`)
/*!
**	@see
**	- ASCII_IsDigit_Hexadecimal()
**	- UTF32_IsDigit_Hexadecimal()
*/
//!@{
#define						Char_IsDigit_Hexadecimal	CONCAT(LIBCONFIG_CHAR_NAME,_IsDigit_Hex)
#define c_isxdigit			Char_IsDigit_Hexadecimal
#define c_isdigithex		Char_IsDigit_Hexadecimal
#define Char_IsDigit_Hex	Char_IsDigit_Hexadecimal
//!@}

//!@doc Checks if the given char `c` is a octal-base digit character (ie: #CHARSET_OCT: `01234567`)
/*!
**	@see
**	- ASCII_IsDigit_Octal()
**	- UTF32_IsDigit_Octal()
*/
//!@{
#define						Char_IsDigit_Octal	CONCAT(LIBCONFIG_CHAR_NAME,_IsDigit_Oct)
#define c_isodigit			Char_IsDigit_Octal
#define c_isdigitoct		Char_IsDigit_Octal
#define Char_IsDigit_Oct	Char_IsDigit_Octal
//!@}

//!@doc Checks if the given char `c` is a binary-base digit character (ie: '0' or '1')
/*!
**	@see
**	- ASCII_IsDigit_Binary()
**	- UTF32_IsDigit_Binary()
*/
//!@{
#define						Char_IsDigit_Binary	CONCAT(LIBCONFIG_CHAR_NAME,_IsDigit_Bin)
#define c_isbdigit			Char_IsDigit_Binary
#define c_isdigitbin		Char_IsDigit_Binary
#define Char_IsDigit_Bin	Char_IsDigit_Binary
//!@}



//!@doc Check if the given char `c` is whitespace character (' ','\\t','\\r','\\n','\\f','\\v')
/*!
**	@see
**	- ASCII_IsWhiteSpace()
**	- UTF32_IsWhiteSpace()
*/
//!@{
#define					Char_IsWhiteSpace	CONCAT(LIBCONFIG_CHAR_NAME,_IsWhiteSpace)
#define c_isspace		Char_IsWhiteSpace
#define Char_IsSpace	Char_IsWhiteSpace
//!@}

//!@doc Check if the given char `c` is a punctuation character
/*!
**	@see
**	- ASCII_IsPunctuation()
**	- UTF32_IsPunctuation()
*/
//!@{
#define					Char_IsPunctuation	CONCAT(LIBCONFIG_CHAR_NAME,_IsPunctuation)
#define c_ispunct		Char_IsPunctuation
#define Char_IsPunct	Char_IsPunctuation
//!@}

// TODO https://en.cppreference.com/w/c/string/byte/iscntrl

//!@doc Check if the given char `c` is a printable ASCII character
/*!
**	@see
**	- ASCII_IsPrintable()
**	- UTF32_IsPrintable()
*/
//!@{
#define					Char_IsPrintable	CONCAT(LIBCONFIG_CHAR_NAME,_IsPrintable)
#define c_isprint		Char_IsPrintable
#define Char_IsPrint	Char_IsPrintable
//!@}

// TODO https://en.cppreference.com/w/c/string/byte/isgraph

//!@doc Check if the given char `c` is a valid character integer
/*!
**	@see
**	- ASCII_IsValid()
**	- UTF32_IsValid()
**	- UTF32_IsASCII()
*/
//!@{
#define					Char_IsValid	CONCAT(LIBCONFIG_CHAR_NAME,_IsValid)
#define c_isascii		Char_IsValid
#define c_isvalid		Char_IsValid
//!@}



//!@doc Check if the given char `c` is contained in the given 'charset'
/*!
**	@see
**	- ASCII_IsInCharset()
**	- UTF32_IsInCharset()
*/
//!@{
#define					Char_IsInCharset	CONCAT(LIBCONFIG_CHAR_NAME,_IsInCharset)
#define c_isincharset	Char_IsInCharset
//!@}



/*
** ************************************************************************** *|
**                           Character Substitutions                          *|
** ************************************************************************** *|
*/

//!@doc Get the uppercase version of the given char `c`, if possible
/*!
**	@see
**	- ASCII_ToUppercase()
**	- UTF32_ToUppercase()
*/
//!@{
#define					Char_ToUppercase	CONCAT(LIBCONFIG_CHAR_NAME,_ToUppercase)
#define c_toupper		Char_ToUppercase
#define Char_ToUpper	Char_ToUppercase
//!@}

//!@doc Get the lowercase version of the given char `c`, if possible
/*!
**	@see
**	- ASCII_ToLowercase()
**	- UTF32_ToLowercase()
*/
//!@{
#define					Char_ToLowercase	CONCAT(LIBCONFIG_CHAR_NAME,_ToLowercase)
#define c_tolower		Char_ToLowercase
#define Char_ToLower	Char_ToLowercase
//!@}

// TODO Char_ToASCII()



#endif

/*! @endgroup */
HEADER_END
#endif
