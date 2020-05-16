/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io/ft_getnextline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"
#include "libft_list.h"
#include "libft_string.h"



static	void	gnl_deletelistitem(s_list **store, int fd, char **line)
{
	s_list	*lst;
	s_list	*result;

	*line = NULL;
	result = NULL;
	lst = *store;
	while (lst)
	{
		if (lst->next && (int)lst->next->item_size == fd)
		{
			result = lst->next;
			lst->next = result->next;
			break ;
		}
		lst = lst->next;
	}
	if (result)
	{
		free(result->item);
		free(result);
		result = NULL;
	}
}

static	int		gnl_read(s_list *lst)
{
	int		result;
	char	buffer[BUFF_SIZE + 1];
	char	*temp;

	result = 0;
	buffer[BUFF_SIZE] = '\0';
	while (!ft_strchr(lst->item, '\n') &&
		(result = read((int)lst->item_size, buffer, BUFF_SIZE)) > 0)
	{
		temp = (char *)lst->item;
		if (result < BUFF_SIZE)
			buffer[result] = '\0';
		if (!(lst->item = ft_strjoin(temp, buffer)))
			return (0);
		free(temp);
	}
	return (result);
}

static	int		gnl_makeline(s_list *lst, char **line)
{
	size_t	length;
	size_t	space;
	char	*str;

	length = ft_strlen(lst->item);
	str = lst->item;
	space = (size_t)ft_strchr(str, '\n');
	space = space ? (size_t)((char *)space - str) : length;
	*line = ft_strsub(lst->item, 0, space);
	if (space == length)
	{
		ft_strclr(lst->item);
		return (GNL_LINE);
	}
	str = NULL;
	if (!(str = (char *)malloc(length + 1)))
		return (GNL_ERROR);
	ft_strcpy(str, (char *)lst->item + space + 1);
	ft_strclr(lst->item);
	ft_strcpy(lst->item, str);
	free(str);
	return (GNL_LINE);
}

int				ft_getnextline(int const fd, char **line)
{
	static s_list	*store = NULL;
	s_list			*lst;

	if (line == NULL || BUFF_SIZE < 0 || fd < 0)
		return (GNL_ERROR);
	if (!store && !(store = ft_lstnew(NULL, fd)))
		return (GNL_ERROR);
	lst = store;
	while (lst && (int)lst->item_size != fd)
		lst = lst->next;
	if (!lst)
		ft_lstadd(&store, (lst = ft_lstnew(NULL, fd)));
	if (!lst->item && !(lst->item = ft_strnew(2)))
		return (GNL_ERROR);
	if (gnl_read(lst) < 0)
		return (GNL_ERROR);
	if (*(char *)lst->item == '\0')
	{
		gnl_deletelistitem(&store, fd, line);
		return (GNL_END);
	}
	if (gnl_makeline(lst, line) < 0)
		return (GNL_ERROR);
	return (GNL_LINE);
}
