/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list/ft_lstdel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (*alst)
	{
		del((*alst)->item, (*alst)->item_size);
		free(*alst);
		*alst = NULL;
	}
}

/*
**	if (alst == NULL || del == NULL)
**		return ;
*/

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *lst;
	t_list *tmp;

	lst = *alst;
	while (lst)
	{
		del(lst->item, lst->item_size);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	*alst = NULL;
}

/*
**	if (alst == NULL || del == NULL)
**		return ;
*/

void	ft_lstpop(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*lst;
	t_list	*lst_prev;

	lst = *alst;
	lst_prev = NULL;
	while (lst)
	{
		if (lst->next == NULL)
		{
			del((lst)->item, (lst)->item_size);
			free(lst);
			if (lst_prev)
				lst_prev->next = NULL;
			return ;
		}
		lst_prev = lst;
		lst = lst->next;
	}
}

/*
**	if (alst == NULL || del == NULL)
**		return ;
*/
