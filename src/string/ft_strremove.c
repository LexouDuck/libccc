/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strremove.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"



char	*ft_strremove(char const *str, char const *query)
{
	char	*result;
	size_t	matches;
	size_t	length;
	size_t	length_query;
	size_t	i;

#if HANDLE_NULLPOINTERS
	if (str == NULL || query == NULL)
		return (NULL);
#endif
	matches = ft_strcount_str(str, query);
	length = ft_strlen(str);
	length_query = ft_strlen(query);
	i = matches * length_query;
	length = (length < i) ? 0 : length - i;
	if (!(result = (char *)malloc(length + 1)))
		return (NULL);
	matches = (size_t)(ft_strstr(str, query) - str);
	i = 0;
	while (i < length)
	{
		if (i == matches && (str += length_query))
			matches = (size_t)(ft_strstr(str, query) - str);
		result[i] = *(str++);
		++i;
	}
	result[i] = '\0';
	return (result);
}

/*
**	if (str == NULL)
**		return (NULL);
*/
