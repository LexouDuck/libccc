/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strdup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

char	*ft_strdup(char const *str)
{
	char	*result;
	size_t	i;

	i = 0;
	while (str[i])
		++i;
	if (!(result = (char *)malloc(i + 1)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}
/*
**	if (str == NULL)
**		return (NULL);
*/
