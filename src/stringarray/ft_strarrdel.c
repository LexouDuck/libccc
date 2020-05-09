/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringarray/ft_strarrdel.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_string.h"
#include "libft_stringarray.h"



void	ft_strarrdel(char ***a_strarr)
{
	int		i;

#if HANDLE_NULLPOINTERS
	if (a_strarr == NULL)
		return ;
#endif
	if (*a_strarr)
	{
		i = 0;
		while ((*a_strarr)[i])
		{
			ft_strdel((*a_strarr) + i);
			++i;
		}
		ft_memdel((void**)a_strarr);
	}
}
