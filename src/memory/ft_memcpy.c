/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory/ft_memcpy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"

void	*ft_memcpy(void *dest, void const *src, size_t n)
{
	t_u8	*result;
	t_u8	*source;
	size_t	i;

	result = (t_u8 *)dest;
	source = (t_u8 *)src;
	i = 0;
	while (i < n)
	{
		result[i] = source[i];
		++i;
	}
	return (dest);
}

/*
**	if (dest == NULL)
**		return (NULL);
**	if (src == NULL)
**		return (dest);
*/

void	*ft_memccpy(void *dest, void const *src, t_u8 byte, size_t n)
{
	t_u8	*result;
	t_u8	*source;
	size_t	i;

	byte &= 0xFF;
	result = (t_u8 *)dest;
	source = (t_u8 *)src;
	i = 0;
	while (i < n)
	{
		result[i] = source[i];
		if (result[i] == byte)
			return (result + i + 1);
		++i;
	}
	return (NULL);
}

/*
**	if (dest == NULL || src == NULL)
**		return (NULL);
*/
