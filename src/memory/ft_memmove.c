/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory/ft_memmove.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_memory.h"

void	*ft_memmove(void *dest, void const *src, size_t n)
{
	t_u8	*result;
	t_u8	*source;
	size_t	i;

	if (dest && dest == src)
		return (dest);
	result = (t_u8 *)dest;
	source = (t_u8 *)src;
	if (src < dest && src + n >= dest)
	{
		i = n;
		while (i--)
			result[i] = source[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			result[i] = source[i];
			++i;
		}
	}
	return (dest);
}
/*
** if (dest == NULL)
**		return (NULL);
**	if (src == NULL)
**		return (dest);
*/
