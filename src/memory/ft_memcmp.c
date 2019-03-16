/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory/ft_memcmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_memory.h"

int	ft_memcmp(void const *ptr1, void const *ptr2, size_t n)
{
	t_u8	*p1;
	t_u8	*p2;
	size_t	i;

	p1 = (t_u8 *)ptr1;
	p2 = (t_u8 *)ptr2;
	i = 0;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		++i;
	}
	return (0);
}
/*
**	if (ptr1 == ptr2)
**		return (0);
**	return (ptr1 == NULL ? 0 : ptr1[0]) -
**		   (ptr2 == NULL ? 0 : ptr2[0]);
*/
