/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

char	*ft_strstr(char const *str, char const *query)
{
	size_t	length;
	size_t	match;
	size_t	i;

	length = 0;
	while (query[length])
		++length;
	if (length == 0)
		return (NULL);
	i = 0;
	while (str[i])
	{
		match = 0;
		while (match < length)
		{
			if (str[i + match] == query[match])
				++match;
			else
				break ;
		}
		if (match == length)
			return ((char *)str + i);
		++i;
	}
	return (NULL);
}

/*
**	if (str == NULL || query == NULL)
**		return (NULL);
*/

char	*ft_strrstr(char const *str, char const *query)
{
	size_t	length;
	size_t	match;
	size_t	i;

	length = 0;
	while (query[length])
		++length;
	if (length == 0)
		return (NULL);
	i = ft_strlen(str);
	while (i--)
	{
		match = 0;
		while (match < length)
		{
			if (str[i + match] == query[match])
				++match;
			else
				break ;
		}
		if (match == length)
			return ((char *)str + i);
	}
	return (NULL);
}

/*
**	if (str == NULL || query == NULL)
**		return (NULL);
*/

char	*ft_strnstr(char const *str, char const *query, size_t n)
{
	size_t	length;
	size_t	match;
	size_t	i;

	length = ft_strlen(query);
	i = 0;
	while (str[i] && i + length <= n)
	{
		match = 0;
		while (match < length)
		{
			if (str[i + match] == query[match])
				match++;
			else
				break ;
		}
		if (match == length)
			return ((char *)str + i);
		++i;
	}
	return (NULL);
}

/*
**	if (str == NULL || query == NULL)
**		return (NULL);
*/

t_s32		ft_stristr(char const *str, char const *query)
{
	size_t	i;
	size_t	j;

	if (query[0] == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (query[j] == str[i + j])
		{
			if (query[j + 1] == '\0')
				return (i);
			if (str[i + j + 1] == '\0')
				return (-1);
			++j;
		}
		++i;
	}
	return (-1);
}

/*
**	if (str == NULL || query == NULL)
**		return (NULL);
*/