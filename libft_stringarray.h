/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_stringarray.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRINGARRAY_H
# define LIBFT_STRINGARRAY_H

# include "libft.h"

/*
** ************************************************************************** *|
**                                  Macros                                    *|
** ************************************************************************** *|
*/

/*
**	#define	FT_StringSplit(str, c)			ft_strsplit(str, c)
*/

/*
** ************************************************************************** *|
**                        Basic StringArray Operations                        *|
** ************************************************************************** *|
*/

/*
**	Returns a string array made up of substrings of 'str', where each element
**	is a section delimited by 'c' separators, or the edges of the string.
*/
char	**ft_strsplit(char const *str, char c);

#endif
