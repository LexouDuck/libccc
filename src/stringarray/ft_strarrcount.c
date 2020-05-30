/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringarray/ft_strarrcount.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"
#include "libft_stringarray.h"



t_u32		ft_strarrcount_char(char const** strarr, char const c)
{
	t_u32		i;
	t_u32		count;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (strarr == NULL)
		return (0);
#endif
	count = 0;
	i = 0;
	while (strarr[i])
	{
		count += ft_strcount_char(strarr[i], c);
		++i;
	}
	return (count);
}



t_u32		ft_strarrcount_charset(char const** strarr, char const* cset)
{
	t_u32		i;
	t_u32		count;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (strarr == NULL || cset == NULL)
		return (0);
#endif
	count = 0;
	i = 0;
	while (strarr[i])
	{
		count += ft_strcount_charset(strarr[i], cset);
		++i;
	}
	return (count);
}



t_u32		ft_strarrcount_str(char const** strarr, char const* query)
{
	t_u32		i;
	t_u32		count;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (strarr == NULL || query == NULL)
		return (0);
#endif
	count = 0;
	i = 0;
	while (strarr[i])
	{
		count += ft_strcount_str(strarr[i], query);
		++i;
	}
	return (count);
}
