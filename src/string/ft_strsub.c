/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strsub.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_string.h"



char	*ft_strsub(char const *str, t_size index, t_size n)
{
	char	*result;
	t_size	length;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	length = 0;
	while (str[length])
		++length;
	if (index > length || index + n > length)
		return (NULL);
	if (!(result = (char *)ft_memalloc(n + 1)))
		return (NULL);
	i = 0;
	while (i < n)
	{
		result[i] = str[index + i];
		++i;
	}
	result[i] = '\0';
	return (result);
}
