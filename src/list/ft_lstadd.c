/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list/ft_lstadd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_list.h"

void	ft_lstadd(t_list **alst, t_list *elem)
{
	if (*alst == NULL)
	{
		*alst = elem;
		return ;
	}
	elem->next = *alst;
	*alst = elem;
}

/*
**	if (alst == NULL || new == NULL)
**		return ;
*/

void	ft_lstappend(t_list **alst, t_list *elem)
{
	t_list *lst;

	lst = *alst;
	if (lst == NULL)
	{
		*alst = elem;
		return ;
	}
	while (lst->next)
	{
		lst = lst->next;
	}
	lst->next = elem;
}

/*
**	if (alst == NULL || elem == NULL)
**		return ;
*/

void	ft_lstinsert(t_list **alst, t_list *elem, t_u32 index)
{
	t_list	*lst;
	t_list	*tmp;
	t_u32	i;

	if (elem == NULL)
		return ;
	lst = *alst;
	if (lst == NULL || index == 0)
	{
		*alst = elem;
		if (lst == NULL || lst->next == NULL)
			return ;
		(*alst)->next = lst->next;
		return ;
	}
	i = 0;
	while (++i < index && lst->next)
	{
		lst = lst->next;
	}
	tmp = lst->next;
	lst->next = elem;
	elem->next = tmp;
}

/*
**	if (alst == NULL || elem == NULL)
**		return ;
*/
