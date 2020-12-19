/*============================================================================*/
/*                                            ______________________________  */
/*  libccc_char.h                            |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBFT_CHAR_H
#define __LIBFT_CHAR_H
/*! @file libft_char.h
**	This header defines all the functions/sets related to single ASCII chars.
**	@addtogroup libft_char
**	@{
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

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

//! Check if the given char 'c' is a letter (lowercase or uppercase)
/*!
**	Check if the given char 'c' is a letter (lowercase or uppercase)
**
**	@param	c	The character to check (UTF-8)
**	@return 1 if the given char 'c' is a letter (lowercase or uppercase),
**			and returns 0 otherwise.
*/
t_bool				Char_IsLetter(int c);
#define ft_isalpha	Char_IsLetter

//! Check if the given char 'c' is a uppercase letter character
/*!
**	Check if the given char 'c' is a uppercase letter character
**
**	@param	c	The character to check (UTF-8)
**	@return 1 if the given char 'c' is a uppercase letter character,
**			and returns 0 otherwise.
*/
t_bool				Char_IsUppercase(int c);
#define ft_isupper	Char_IsUppercase

//! Check if the given char 'c' is an lowercase letter character
/*!
**	Check if the given char 'c' is an lowercase letter character
**
**	@param	c	The character to check (UTF-8)
**	@return 1 if the given char 'c' is an lowercase letter character,
**			and returns 0 otherwise.
*/
t_bool				Char_IsLowercase(int c);
#define ft_islower	Char_IsLowercase

//! Check if the given char 'c' is alphanumeric (letter or digit) character
/*!
**	Check if the given char 'c' is alphanumeric (letter or digit) character
**
**	@param	c	The character to check (UTF-8)
**	@return 1 if the given char 'c' is alphanumeric (letter or digit),
**			and returns 0 otherwise.
*/
t_bool				Char_IsAlphaNumeric(int c);
#define ft_isalnum	Char_IsAlphaNumeric

//! Check if the given char 'c' is a numerical digit character
/*!
**	Check if the given char 'c' is a numerical digit character
**
**	@param	c	The character to check (UTF-8)
**	@return 1 if the given char 'c' is a numerical digit character,
**			and returns 0 otherwise.
*/
t_bool				Char_IsDigit(int c);
#define ft_isdigit	Char_IsDigit

//! Check if the given char 'c' is a hexadecimal character
/*!
**	Check if the given char 'c' is a hexadecimal character
**
**	@param	c	The character to check (UTF-8)
**	@return 1 if the given char 'c' is a hexadecimal character
**			(either 0-9 or  A-F lowercase or uppercase), and returns 0 otherwise.
*/
t_bool				Char_IsHexDigit(int c);
#define ft_ishexdigit	Char_IsHexDigit

//! Check if the given char 'c' is whitespace character (\r,\n,\f,\v,\t,' ')
/*!
**	Check if the given char 'c' is whitespace character (\r,\n,\f,\v,\t,' ')
**
**	@param	c	The character to check (UTF-8)
**	@return 1 if the given char 'c' is whitespace character: \r,\n,\f,\v,\t,' '
**			(carriage return, newline, form feed, vertical tab, tab, or space), and returns 0 otherwise.
*/
t_bool				Char_IsSpace(int c);
#define ft_isspace	Char_IsSpace

//! Check if the given char 'c' is a punctuation character
/*!
**	Check if the given char 'c' is a punctuation character
**
**	@param	c	The character to check (UTF-8)
**	@return 1 if the given char 'c' is a punctuation character,
**			and returns 0 otherwise.
*/
t_bool				Char_IsPunctuation(int c);
#define ft_ispunct	Char_IsPunctuation

//! Check if the given char 'c' is a printable ASCII character
/*!
**	Check if the given char 'c' is a printable ASCII character
**
**	@param	c	The character to check (UTF-8)
**	@return 1 if the given char 'c' is a printable ASCII character,
**			(0x20 <= c && c <= 0x7E) and returns 0 otherwise.
*/
t_bool				Char_IsPrintable(int c);
#define ft_isprint	Char_IsPrintable

//! Check if the given char 'c' is an ASCII-compatible char (non UTF-8)
/*!
**	Check if the given char 'c' is an ASCII-compatible char (non UTF-8)
**
**	@param	c	The character to check (UTF-8)
**	@return 1 if the given char 'c' has a value between 0 and 127,
**			(0x00 <= c && c <= 0x7F) and returns 0 otherwise.
*/
t_bool				Char_IsASCII(int c);
#define ft_isascii	Char_IsASCII



/*
** ************************************************************************** *|
**                           Character Substitutions                          *|
** ************************************************************************** *|
*/

//! Get the uppercase version of the given char 'c'
/*!
**	Get the uppercase version of the given char 'c'
**
**	@param	c	The character to uppercase-ify (UTF-8)
**	@return the uppercase equivalent of the given character 'c'
**			(nothing is done if 'c' is not a letter character).
*/
char				Char_ToUppercase(char c);
#define ft_toupper	Char_ToUppercase

//! Get the lowercase version of the given char 'c'
/*!
**	Get the lowercase version of the given char 'c'
**
**	@param	c	The character to lowercase-ify (UTF-8)
**	@return the lowercase equivalent of the given character 'c'
**			(nothing is done if 'c' is not a letter character).
*/
char				Char_ToLowercase(char c);
#define ft_tolower	Char_ToLowercase



/*! @} */
HEADER_END
#endif
