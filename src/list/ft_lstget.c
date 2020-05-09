/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list/ft_lstget.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

t_list	*ft_lstget(t_list *lst, t_u32 index)
{
	t_u32	i;

	if (lst == NULL)
		return (NULL);
	i = 0;
	while (i < index)
	{
		if (lst->next == NULL)
			return (NULL);
		else
			lst = lst->next;
		++i;
	}
	return (lst);
}

t_list	*ft_lstfind(t_list *lst, void const *query)
{
	while (lst)
	{
		if (lst->item == query)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
