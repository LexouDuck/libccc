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



void	ft_memset(void *ptr, t_u8 byte, t_size n)
{
	t_u8	*result;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (ptr == NULL)
		return ;
#endif
	byte &= 0xFF;
	result = (t_u8 *)ptr;
	i = 0;
	while (i < n)
	{
		result[i] = byte;
		++i;
	}
}



void	ft_memclr(void *ptr, t_size n)
{
	t_u8	*result;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (ptr == NULL)
		return ;
#endif
	result = (t_u8 *)ptr;
	i = 0;
	while (i < n)
	{
		result[i] = 0;
		++i;
	}
}
