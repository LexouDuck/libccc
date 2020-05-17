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



s_list	*ft_lstget(s_list *lst, t_u32 index)
{
	t_u32	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL)
		return (NULL);
#endif
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



s_list	*ft_lstfind(s_list *lst, void const *query)
{
#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL)
		return (NULL);
#endif
	if (query == NULL)
		return (NULL);
	while (lst)
	{
		if (lst->item == query)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
