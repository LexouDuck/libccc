/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list/ft_lstsub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"



s_list	*ft_lstsub(s_list *lst, t_u32 index, t_u32 n)
{
	s_list	*result;
	s_list	*result_lst;
	s_list	*tmp;

#if HANDLE_NULLPOINTERS
	if (lst == NULL)
		return (NULL);
#endif
	while (lst && index--)
		lst = lst->next;
	if (n == 0)
		return (NULL);
	result = ft_lstnew(lst->item, lst->item_size);
	result_lst = result;
	lst = lst->next;
	while (lst && n--)
	{
		tmp = ft_lstnew(lst->item, lst->item_size);
		result_lst->next = tmp;
		result_lst = result_lst->next;
		lst = lst->next;
	}
	return (result);
}
