/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory/ft_memset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"

void	ft_memset(void *ptr, t_u8 byte, size_t n)
{
	t_u8	*result;
	size_t	i;

	byte &= 0xFF;
	result = (t_u8 *)ptr;
	i = 0;
	while (i < n)
	{
		result[i] = byte;
		++i;
	}
}

/*
**	if (ptr == NULL)
**		return (NULL);
*/

void	ft_memclr(void *ptr, size_t n)
{
	t_u8	*result;
	size_t	i;

	result = (t_u8 *)ptr;
	i = 0;
	while (i < n)
	{
		result[i] = 0;
		++i;
	}
}

/*
**	if (ptr == NULL)
**		return (NULL);
*/
