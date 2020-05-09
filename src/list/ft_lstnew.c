/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list/ft_lstnew.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

t_list	*ft_lstnew(void *item, size_t item_size)
{
	t_list *result;

	if (!(result = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	result->item = item;
	result->item_size = (item ? item_size : 0);
	result->next = NULL;
	return (result);
}
