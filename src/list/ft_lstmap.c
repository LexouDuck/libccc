/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list/ft_lstmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

static void	ft_lstmap_delete(void *content, size_t content_size)
{
	if (content && content_size > 0)
	{
		free(content);
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*result;
	t_list	*current;

	result = NULL;
	while (lst)
	{
		current = f(lst);
		if (current == NULL)
		{
			ft_lstdel(&result, ft_lstmap_delete);
			return (NULL);
		}
		ft_lstappend(&result, current);
		lst = lst->next;
	}
	return (result);
}

/*
**	if (lst == NULL || f == NULL)
**		return ;
*/

t_list		*ft_lstmapi(t_list *lst, t_list *(*f)(t_list *elem, t_u32 index))
{
	t_list	*result;
	t_list	*current;
	t_u32	i;

	result = NULL;
	i = 0;
	while (lst)
	{
		current = f(lst, i);
		if (current == NULL)
		{
			ft_lstdel(&result, ft_lstmap_delete);
			return (NULL);
		}
		ft_lstappend(&result, current);
		lst = lst->next;
		++i;
	}
	return (result);
}

/*
**	if (lst == NULL || f == NULL)
**		return ;
*/
