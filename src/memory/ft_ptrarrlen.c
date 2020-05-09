/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory/ft_ptrarrlen.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"



t_u32		ft_ptrarrlen(const void **a_ptrarr)
{
	t_u32		i;

#if HANDLE_NULLPOINTERS
	if (a_ptrarr == NULL)
		return (0);
#endif
	i = 0;
	while (((void**)a_ptrarr)[i])
		i++;
	return (i);
}
