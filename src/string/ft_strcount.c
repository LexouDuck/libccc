/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strcount.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

size_t	ft_strcount_char(char const *str, char c)
{
	size_t	result;
	size_t	i;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			++result;
		++i;
	}
	return (result);
}

/*
**	if (str == NULL)
**		return (0);
*/

size_t	ft_strcount_charset(char const *str, char const *cset)
{
	size_t	result;
	size_t	i;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (ft_strchr(cset, str[i]))
			++result;
		++i;
	}
	return (result);
}

/*
**	if (str == NULL || cset == NULL)
**		return (0);
*/

size_t	ft_strcount_str(char const *str, char const *query)
{
	size_t	result;
	size_t	length;
	size_t	i;
	size_t	j;

	result = 0;
	length = 0;
	while (query[length])
		++length;
	if (length == 0)
		return (0);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == query[j])
			++j;
		if (j == length)
			++result;
		++i;
	}
	return (result);
}

/*
**	if (str == NULL || query == NULL)
**		return (0);
*/
