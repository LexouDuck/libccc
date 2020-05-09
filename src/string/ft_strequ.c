/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strequ.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"



t_bool	ft_strequ(char const *str1, char const *str2)
{
	size_t i;

#if HANDLE_NULLPOINTERS
	if (str1 == str2)
		return (TRUE);
	if (str1 == NULL || str2 == NULL)
		return (FALSE);
#endif
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (FALSE);
		++i;
	}
	return (str1[i] == str2[i]);
}



t_bool	ft_strnequ(char const *str1, char const *str2, size_t n)
{
	size_t i;

#if HANDLE_NULLPOINTERS
	if (str1 == str2 || n == 0)
		return (TRUE);
	if (str1 == NULL || str2 == NULL)
		return (FALSE);
#endif
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (FALSE);
		++i;
		if (i == n)
			return (TRUE);
	}
	return (str1[i] == str2[i]);
}
