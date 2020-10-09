/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_char.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
**                                    Macros                                  *|
** ************************************************************************** *|
*/

#define Char_IsLetter			ft_isalpha
#define Char_IsUppercase		ft_isupper
#define Char_IsLowercase		ft_islower
#define Char_IsAlphanumeric		ft_isalnum
#define Char_IsDigit			ft_isdigit
#define Char_IsHexDigit			ft_ishexdigit
#define Char_IsSpace			ft_isspace
#define Char_IsPunctuation		ft_ispunct
#define Char_IsPrintable		ft_isprint
#define Char_IsASCII			ft_isascii

#define Char_ToUppercase		ft_toupper
#define Char_ToLowercase		ft_tolower



/*
** ************************************************************************** *|
**                              Character Checks                              *|
** ************************************************************************** *|
*/

//! Check if the given char 'c' is a letter (lowercase or uppercase)
/*!
**	@param	c	The ASCII character to check
**	@return 1 if the given char 'c' is a letter (lowercase or uppercase),
**			and returns 0 otherwise.
*/
t_bool	ft_isalpha(int c);

//! Check if the given char 'c' is a uppercase letter character
/*!
**	@param	c	The ASCII character to check
**	@return 1 if the given char 'c' is a uppercase letter character,
**			and returns 0 otherwise.
*/
t_bool	ft_isupper(int c);

//! Check if the given char 'c' is an lowercase letter character
/*!
**	@param	c	The ASCII character to check
**	@return 1 if the given char 'c' is an lowercase letter character,
**			and returns 0 otherwise.
*/
t_bool	ft_islower(int c);

//! Check if the given char 'c' is alphanumeric (letter or digit) character
/*!
**	@param	c	The ASCII character to check
**	@return 1 if the given char 'c' is alphanumeric (letter or digit),
**			and returns 0 otherwise.
*/
t_bool	ft_isalnum(int c);

//! Check if the given char 'c' is a numerical digit character
/*!
**	@param	c	The ASCII character to check
**	@return 1 if the given char 'c' is a numerical digit character,
**			and returns 0 otherwise.
*/
t_bool	ft_isdigit(int c);

//! Check if the given char 'c' is a hexadecimal character
/*!
**	@param	c	The ASCII character to check
**	@return 1 if the given char 'c' is a hexadecimal character
**			(either 0-9 or  A-F lowercase or uppercase), and returns 0 otherwise.
*/
t_bool	ft_ishexdigit(int c);

//! Check if the given char 'c' is whitespace character (\r,\n,\f,\v,\t,' ')
/*!
**	@param	c	The ASCII character to check
**	@return 1 if the given char 'c' is whitespace character: \r,\n,\f,\v,\t,' '
**			(carriage return, newline, form feed, vertical tab, tab, or space), and returns 0 otherwise.
*/
t_bool	ft_isspace(int c);

//! Check if the given char 'c' is a punctuation character
/*!
**	@param	c	The ASCII character to check
**	@return 1 if the given char 'c' is a punctuation character,
**			and returns 0 otherwise.
*/
t_bool	ft_ispunct(int c);

//! Check if the given char 'c' is a printable ASCII character
/*!
**	@param	c	The ASCII character to check
**	@return 1 if the given char 'c' is a printable ASCII character,
**			(0x20 <= c && c <= 0x7E) and returns 0 otherwise.
*/
t_bool	ft_isprint(int c);

//! Check if the given char 'c' is an ASCII-compatible char (non UTF-8)
/*!
**	@param	c	The ASCII character to check
**	@return 1 if the given char 'c' has a value between 0 and 127,
**			(0x00 <= c && c <= 0x7F) and returns 0 otherwise.
*/
t_bool	ft_isascii(int c);



/*
** ************************************************************************** *|
**                           Character Substitutions                          *|
** ************************************************************************** *|
*/

//! Get the uppercase version of the given char 'c'
/*!
**	@param	c	The ASCII character to uppercase-ify
**	@return the uppercase equivalent of the given character 'c'
**			(nothing is done if 'c' is not a letter character).
*/
char	ft_toupper(char c);

//! Get the lowercase version of the given char 'c'
/*!
**	@param	c	The ASCII character to lowercase-ify
**	@return the lowercase equivalent of the given character 'c'
**			(nothing is done if 'c' is not a letter character).
*/
char	ft_tolower(char c);



/*! @} */
HEADER_END
#endif
