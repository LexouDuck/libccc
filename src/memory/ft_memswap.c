/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory/ft_memswap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_memory.h"

int			ft_memswap(void *ptr1, void *ptr2, size_t size)
{
	t_u8	*p1;
	t_u8	*p2;
	size_t	i;

	if (ptr1 && ptr2)
	{
		p1 = ptr1;
		p2 = ptr2;
		i = 0;
		while (i < size)
		{
			p1[i] = (p1[i] ^ p2[i]);
			p2[i] = (p2[i] ^ p1[i]);
			p1[i] = (p1[i] ^ p2[i]);
			++i;
		}
		return (OK);
	}
	return (ERROR);
}
