/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strtrim.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_string.h"

static t_bool	charset_contains(char const *charset, char c)
{
	size_t	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (TRUE);
		++i;
	}
	return (FALSE);
}

char			*ft_strtrim(char const *str, char const *charset)
{
	size_t	offset;
	size_t	length;

	offset = 0;
	length = 0;
	while (str[length])
		++length;
	while (offset < length && charset_contains(charset, str[offset]))
		++offset;
	if (offset == length)
		return (ft_strnew(0));
	length -= 1;
	while (length > offset && charset_contains(charset, str[length]))
		--length;
	length -= offset - 1;
	return (ft_strsub(str, offset, length));
}

/*
**	if (str == NULL)
**		return (NULL);
*/

char			*ft_strtrim_l(char const *str, char const *charset)
{
	size_t	i;
	size_t	length;

	length = ft_strlen(str);
	i = 0;
	while (i < length)
	{
		if (charset_contains(charset, str[i]))
			++i;
		else
			break ;
	}
	length -= i;
	return (ft_strsub(str, i, length));
}

/*
**	if (str == NULL || charset == NULL)
**		return (NULL);
*/

char			*ft_strtrim_r(char const *str, char const *charset)
{
	size_t	i;
	size_t	length;

	length = ft_strlen(str);
	i = length;
	while (--i)
	{
		if (!charset_contains(charset, str[i]))
			break ;
	}
	return (ft_strsub(str, 0, i));
}

/*
**	if (str == NULL || charset == NULL)
**		return (NULL);
*/
