/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list/ft_lst_to.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_memory.h"
#include "../../libft_list.h"

void	**ft_lst_to_array(t_list **alst)
{
	void	**result;
	size_t	length;
	t_list	*lst;
	t_u32	count;
	t_u32	i;

	lst = *alst;
	count = ft_lstsize(lst);
	length = (count + 1) * sizeof(void *);
	if (!(result = (void **)malloc(length)))
		return (NULL);
	i = 0;
	while (lst && i < count)
	{
		result[i] = lst->item;
		lst = lst->next;
		++i;
	}
	result[i] = NULL;
	return (result);
}

/*
**	if (alst == NULL)
**		return (NULL);
*/

t_tuple	*ft_lst_to_tuple(t_list **alst, t_tuple *result)
{
	t_list	*lst;
	t_u32	count;
	t_u32	i;

	lst = *alst;
	result->item_size = lst->item_size;
	count = 0;
	while (lst && ++count)
	{
		lst = lst->next;
		if (lst->item_size != result->item_size)
			return (NULL);
	}
	result->length = (count + 1) * result->item_size;
	if (!(result->items = (void *)malloc(result->length)))
		return (NULL);
	i = -1;
	while (lst && ++i < count)
	{
		ft_memcpy((t_u8 *)result->items + (i * result->item_size),
			lst->item, result->item_size);
		lst = lst->next;
	}
	ft_memclr(result + (i * result->item_size), result->item_size);
	return (result);
}

/*
**	if (alst == NULL || *alst == NULL)
**		return (NULL);
*/
