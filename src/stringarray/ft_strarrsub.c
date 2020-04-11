/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringarray/ft_strarrsub.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_memory.h"
#include "../../libft_string.h"
#include "../../libft_stringarray.h"

char	**ft_strarrsub(const char **strarr, t_u32 start, t_u32 len)
{
	t_u32		i;
	char		**result;

	if (!(result = ft_strarrnew(len)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (!(result[i] = ft_strdup(strarr[i + start])))
		{
			ft_strarrdel(&result);
			return (NULL);
		}
		++i;
	}
	result[i] = NULL;
	return (result);
}

/*
**	if (!strarr || start + len >= ft_ptrarrlen(strarr))
**		return (NULL);
*/