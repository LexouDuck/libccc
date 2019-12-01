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

#ifndef LIBFT_CHAR_H
#define LIBFT_CHAR_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

/*
** ************************************************************************** *|
**                                    Macros                                  *|
** ************************************************************************** *|
*/

#define FT_IsLetter(c)			ft_isalpha(c)
#define FT_IsUppercase(c)		ft_isupper(c)
#define FT_IsLowercase(c)		ft_islower(c)
#define FT_IsAlphanumeric(c)	ft_isalnum(c)
#define FT_IsDigit(c)			ft_isdigit(c)
#define FT_IsHexDigit(c)		ft_ishexdigit(c)
#define FT_IsSpace(c)			ft_isspace(c)
#define FT_IsPunctuation(c)		ft_ispunct(c)
#define FT_IsPrintable(c)		ft_isprint(c)
#define FT_IsASCII(c)			ft_isascii(c)

#define FT_ToUppercase(c)		ft_toupper(c)
#define FT_ToLowercase(c)		ft_tolower(c)



/*
** ************************************************************************** *|
**                              Character Checks                              *|
** ************************************************************************** *|
*/

/*
**	Returns 1 if the given char 'c' is a letter (lowercase or uppercase),
**	and returns 0 otherwise.
*/
int		ft_isalpha(int c);

/*
**	Returns 1 if the given char 'c' is a uppercase letter character,
**	and returns 0 otherwise.
*/
int		ft_isupper(int c);

/*
**	Returns 1 if the given char 'c' is an lowercase letter character,
**	and returns 0 otherwise.
*/
int		ft_islower(int c);

/*
**	Returns 1 if the given char 'c' is alphanumeric (number or letter),
**	and returns 0 otherwise.
*/
int		ft_isalnum(int c);

/*
**	Returns 1 if the given char 'c' is a numerical digit,
**	and returns 0 otherwise.
*/
int		ft_isdigit(int c);

/*
**	Returns 1 if the given char 'c' is a hexadecimal character
**	(either 0-9 or  A-F lowercase or uppercase), and returns 0 otherwise.
*/
int		ft_ishexdigit(int c);

/*
**	Returns 1 if the given char 'c' is whitespace character: \r,\n,\f,\v,\t,' '
**	(carriage return, newline, form feed, vertical tab, tab, or space),
**	and returns 0 otherwise.
*/
int		ft_isspace(int c);

/*
**	Returns 1 if the given char 'c' is a printable ASCII character,
**	and returns 0 otherwise.
*/
int		ft_ispunct(int c);

/*
**	Returns 1 if the given char 'c' is a printable ASCII character,
**	and returns 0 otherwise.
*/
int		ft_isprint(int c);

/*
**	Returns 1 if the given char 'c' has a value between 0 and 127,
**	and returns 0 otherwise.
*/
int		ft_isascii(int c);



/*
** ************************************************************************** *|
**                           Character Substitutions                          *|
** ************************************************************************** *|
*/

/*
**	Returns the uppercase equivalent of the given character 'c'
**	(nothing is done if 'c' is not a letter character).
*/
int		ft_toupper(int c);

/*
**	Returns the lowercase equivalent of the given character 'c'
**	(nothing is done if 'c' is not a letter character).
*/
int		ft_tolower(int c);

#endif
