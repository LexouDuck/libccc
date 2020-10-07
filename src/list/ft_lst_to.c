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

#include "libft_memory.h"
#include "libft_list.h"



void	**ft_lst_to_array(s_list **alst)
{
	void	**result;
	t_size	length;
	s_list	*lst;
	t_u32	count;
	t_u32	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (alst == NULL)
		return (NULL);
#endif
	lst = *alst;
	count = ft_lstsize(lst);
	length = (count + 1) * sizeof(void *);
	if (!(result = (void **)ft_memalloc(length)))
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



s_tuple	*ft_lst_to_tuple(s_list **alst, s_tuple *result)
{
	s_list	*lst;
	t_u32	count;
	t_u32	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (alst == NULL || *alst == NULL)
		return (NULL);
#endif
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
	if (!(result->items = (void *)ft_memalloc(result->length)))
		return (NULL);
	i = (t_u32)-1;
	while (lst && ++i < count)
	{
		ft_memcpy((t_u8 *)result->items + (i * result->item_size),
			lst->item, result->item_size);
		lst = lst->next;
	}
	ft_memclr(result + (i * result->item_size), result->item_size);
	return (result);
}
