/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory/ft_memdup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"



void	*ft_memdup(const void *ptr, size_t n)
{
	t_u8	*result;
	t_u8	*source;
	size_t	i;

#if HANDLE_NULLPOINTERS
	if (ptr == NULL)
		return (NULL);
#endif
	if (!(result = (t_u8 *)malloc(n)))
		return (NULL);
	source = (t_u8 *)ptr;
	i = 0;
	while (i < n)
	{
		result[i] = source[i];
		++i;
	}
	return ((void *)result);
}
