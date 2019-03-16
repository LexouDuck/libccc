/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list/ft_lstiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_list.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	while (lst)
	{
		f(lst);
		lst = lst->next;
	}
}

/*
**	if (lst == NULL || f == NULL)
**		return ;
*/

void	ft_lstiteri(t_list *lst, void (*f)(t_list *elem, t_u32 index))
{
	t_u32 i;

	i = 0;
	while (lst)
	{
		f(lst, i);
		lst = lst->next;
		++i;
	}
}

/*
**	if (lst == NULL || f == NULL)
**		return ;
*/
