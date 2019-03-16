/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_string.h"

char	*ft_strmap(char const *str, char (*f)(char))
{
	char	*result;
	size_t	length;
	size_t	i;

	length = 0;
	while (str[length])
		++length;
	if (!(result = (char *)malloc(length + 1)))
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = f(str[i]);
		++i;
	}
	result[i] = '\0';
	return (result);
}

/*
**	if (str == NULL || f == NULL)
**		return (NULL);
*/

char	*ft_strmapi(char const *str, char (*f)(size_t, char))
{
	char	*result;
	size_t	length;
	size_t	i;

	length = 0;
	while (str[length])
		++length;
	if (!(result = (char *)malloc(length + 1)))
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = f(i, str[i]);
		++i;
	}
	result[i] = '\0';
	return (result);
}

/*
**	if (str == NULL || f == NULL)
**		return (NULL);
*/
