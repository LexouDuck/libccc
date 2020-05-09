/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory/ft_ptrarrnew.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"

void	*ft_ptrarrnew(t_u32 len)
{
	void	**result;

	if (!(result = ft_memalloc(sizeof(void**) * (len + 1))))
		return (NULL);
	result[len] = NULL;
	return (result);
}