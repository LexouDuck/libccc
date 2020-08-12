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

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

HEADER_CPP

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
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/*
**	Define string literals for alphabet characters
*/

#define CHARSET_LOWERCASE	"abcdefghijklmnopqrstuvwxyz"
#define CHARSET_UPPERCASE	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
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

/*
**	A charset containing all of the different whitespace characters
*/
#define CHARSET_WHITESPACE	" \t\n\r\v\f"

/*
**	A charset containing all of the ASCII punctuation characters
*/
#define CHARSET_PUNCTUATION	"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"



/*
** ************************************************************************** *|
**                              Character Checks                              *|
** ************************************************************************** *|
*/

/*
**	Returns 1 if the given char 'c' is a letter (lowercase or uppercase),
**	and returns 0 otherwise.
*/
t_bool	ft_isalpha(int c);

/*
**	Returns 1 if the given char 'c' is a uppercase letter character,
**	and returns 0 otherwise.
*/
t_bool	ft_isupper(int c);

/*
**	Returns 1 if the given char 'c' is an lowercase letter character,
**	and returns 0 otherwise.
*/
t_bool	ft_islower(int c);

/*
**	Returns 1 if the given char 'c' is alphanumeric (number or letter),
**	and returns 0 otherwise.
*/
t_bool	ft_isalnum(int c);

/*
**	Returns 1 if the given char 'c' is a numerical digit,
**	and returns 0 otherwise.
*/
t_bool	ft_isdigit(int c);

/*
**	Returns 1 if the given char 'c' is a hexadecimal character
**	(either 0-9 or  A-F lowercase or uppercase), and returns 0 otherwise.
*/
t_bool	ft_ishexdigit(int c);

/*
**	Returns 1 if the given char 'c' is whitespace character: \r,\n,\f,\v,\t,' '
**	(carriage return, newline, form feed, vertical tab, tab, or space),
**	and returns 0 otherwise.
*/
t_bool	ft_isspace(int c);

/*
**	Returns 1 if the given char 'c' is a printable ASCII character,
**	and returns 0 otherwise.
*/
t_bool	ft_ispunct(int c);

/*
**	Returns 1 if the given char 'c' is a printable ASCII character,
**	and returns 0 otherwise.
*/
t_bool	ft_isprint(int c);

/*
**	Returns 1 if the given char 'c' has a value between 0 and 127,
**	and returns 0 otherwise.
*/
t_bool	ft_isascii(int c);



/*
** ************************************************************************** *|
**                           Character Substitutions                          *|
** ************************************************************************** *|
*/

/*
**	Returns the uppercase equivalent of the given character 'c'
**	(nothing is done if 'c' is not a letter character).
*/
char	ft_toupper(char c);

/*
**	Returns the lowercase equivalent of the given character 'c'
**	(nothing is done if 'c' is not a letter character).
*/
char	ft_tolower(char c);

HEADER_END
#endif
