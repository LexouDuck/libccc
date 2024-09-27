/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list/ft_lstcpy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_list.h"

t_list	*ft_lstcpy(t_list *lst)
{
	t_list	*result;
	t_list	*result_lst;
	t_list	*tmp;

	if (lst == NULL)
		return (NULL);
	result = ft_lstnew(lst->item, lst->item_size);
	result_lst = result;
	lst = lst->next;
	while (lst)
	{
		tmp = ft_lstnew(lst->item, lst->item_size);
		result_lst->next = tmp;
		lst = lst->next;
		result_lst = result_lst->next;
	}
	return (result);
}
