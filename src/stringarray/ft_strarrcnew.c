/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringarray/ft_strarrcnew.c                        :+:      :+:    :+:   */
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



char	**ft_strarrcnew(t_u32 y, size_t x, const char c)
{
	char	**strarr;
	t_u32	i;

	if (!(strarr = ft_strarrnew(y)))
		return (NULL);
	i = 0;
	while (i < y)
	{
		if (!(strarr[i] = ft_strnew(x)))
		{
			strarr[i] = NULL;
			ft_strarrdel(&strarr);
			return (NULL);
		}
		ft_memset(strarr[i], c, x);
		strarr[i][x] = '\0';
		++i;
	}
	strarr[y] = NULL;
	return (strarr);
}
