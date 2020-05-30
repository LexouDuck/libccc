/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringarray/ft_strarrpad_l.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"
#include "libft_stringarray.h"



char	**ft_strarrpad_l(char const** strarr, char const c, t_u32 n)
{
	char		**result;
	t_u32		strarr_length;
	t_u32		i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (strarr == NULL)
		return (NULL);
#endif
	strarr_length = ft_strarrlen(strarr);
	if (!(result = ft_strarrnew(strarr_length)))
		return (NULL);
	i = 0;
	while (strarr[i])
	{
		result[i] = ft_strpad_l(strarr[i], c, n);
		if (!result[i])
		{
			ft_strarrdel(&result);
			return (NULL);
		}
		++i;
	}
	result[i] = NULL;
	return (result);
}
