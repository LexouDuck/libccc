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

#include "libft_list.h"



void	ft_lstadd(s_list **alst, s_list *elem)
{
#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (alst == NULL || elem == NULL)
		return ;
#endif
	if (*alst == NULL)
	{
		*alst = elem;
		return ;
	}
	elem->next = *alst;
	*alst = elem;
}



void	ft_lstappend(s_list **alst, s_list *elem)
{
	s_list *lst;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (alst == NULL || elem == NULL)
		return ;
#endif
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



void	ft_lstinsert(s_list **alst, s_list *elem, t_u32 index)
{
	s_list	*lst;
	s_list	*tmp;
	t_u32	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (alst == NULL || elem == NULL)
		return ;
#endif
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
