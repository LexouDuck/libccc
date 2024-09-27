/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_striter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_string.h"

void	ft_striter(char *str, void (*f)(char *))
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		f(str + i);
		++i;
	}
}

/*
**	if (str == NULL || f == NULL)
**		return ;
*/

void	ft_striteri(char *str, void (*f)(size_t, char *))
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		f(i, str + i);
		++i;
	}
}

/*
**	if (str == NULL || f == NULL)
**		return ;
*/
