/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strhas.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"



t_bool		ft_strhas(char const *str, char const *charset)
{
	size_t	i;
	size_t	c;

#if HANDLE_NULLPOINTERS
	if (str == NULL || charset == NULL)
		return (FALSE);
#endif
	i = 0;
	while (str[i])
	{
		c = 0;
		while (charset[c])
		{
			if (str[i] == charset[c])
				return (TRUE);
			++c;
		}
		++i;
	}
	return (FALSE);
}



t_bool		ft_strhasonly(char const *str, char const *charset)
{
	size_t	i;
	size_t	c;
	t_bool	match;

#if HANDLE_NULLPOINTERS
	if (str == NULL || charset == NULL)
		return (FALSE);
#endif
	i = 0;
	while (str[i])
	{
		match = FALSE;
		c = 0;
		while (charset[c])
		{
			if (str[i] == charset[c])
			{
				match = TRUE;
				break ;
			}
			++c;
		}
		if (match == FALSE)
			return (FALSE);
		++i;
	}
	return (TRUE);
}
