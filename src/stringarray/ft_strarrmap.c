/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringarray/ft_strarrmap.c                         :+:      :+:    :+:   */
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

char		**ft_strarrmap(char const **strarr, char *(*f)(char const *))
{
	t_u32	i;
	char	**result;

	if (!(result = ft_strarrnew(ft_strarrlen(strarr))))
		return (NULL);
	i = 0;
	while (strarr[i])
	{
		result[i] = (*f)(strarr[i]);
		++i;
	}
	return (result);
}

/*
**	if (!strarr || !*strarr || !f ||
**		!(result = ft_ptrarrnew(ft_ptrarrlen(strarr))))
**		return (NULL);
*/

void		ft_strarrmap_inplace(char ***a_strarr, char *(*f)(char *))
{
	t_u32	i;
	char	*tmp;

	i = 0;
	while ((*a_strarr)[i])
	{
		tmp = (*f)((*a_strarr)[i]);
		if (tmp != (*a_strarr)[i])
			ft_strdel(*a_strarr + i);
		(*a_strarr)[i] = tmp;
		++i;
	}
}

/*
**	if (!a_strarr || !*a_strarr || !f)
**		return ;
*/