/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strjoin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_string.h"



char	*ft_strjoin(char const *str1, char const *str2)
{
	char	*result;
	t_size	length1;
	t_size	length2;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str1 == NULL || str2 == NULL)
		return (NULL);
#endif
	length1 = ft_strlen(str1);
	length2 = ft_strlen(str2);
	if (!(result = (char *)ft_memalloc(length1 + length2 + 1)))
		return (NULL);
	i = 0;
	while (i < length1)
	{
		result[i] = str1[i];
		++i;
	}
	i = 0;
	while (i < length2)
	{
		result[length1 + i] = str2[i];
		++i;
	}
	result[length1 + length2] = '\0';
	return (result);
}
