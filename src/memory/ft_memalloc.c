/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory/ft_memalloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"



void	*ft_memalloc(size_t size)
{
	t_u8	*result;
	size_t	i;

	if (!(result = (t_u8 *)malloc(size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		result[i] = 0;
		++i;
	}
	return ((void *)result);
}
