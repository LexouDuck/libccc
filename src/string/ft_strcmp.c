/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strcmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"



int	ft_strcmp(char const *str1, char const *str2)
{
	t_size	i;

#if HANDLE_NULLPOINTERS
	if (str1 == str2)
		return (0);
	if (str1 == NULL || str2 == NULL)
		return ((str1 == NULL ? 0 : str1[0]) -
				(str2 == NULL ? 0 : str2[0]));
#endif
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return ((int)((t_u8)str1[i] - (t_u8)str2[i]));
		++i;
	}
	return ((int)((t_u8)str1[i] - (t_u8)str2[i]));
}



int	ft_strncmp(char const *str1, char const *str2, t_size n)
{
	t_size	i;

#if HANDLE_NULLPOINTERS
	if (str1 == str2)
		return (0);
	if (str1 == NULL || str2 == NULL)
		return ((str1 == NULL ? 0 : str1[0]) -
				(str2 == NULL ? 0 : str2[0]));
#endif
	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return ((int)((t_u8)str1[i] - (t_u8)str2[i]));
		++i;
		if (i == n)
			return (0);
	}
	return ((int)((t_u8)str1[i] - (t_u8)str2[i]));
}
