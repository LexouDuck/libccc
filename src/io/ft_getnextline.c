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

/*
**	Functions used from <unistd.h>:
**	-	void	read(int fd, char* buffer, size_t n);
*/
#include <unistd.h>
#include <stdio.h>

#include "libft_memory.h"
#include "libft_string.h"
#include "libft_list.h"
#include "libft_io.h"



static	int		gnl_read(t_fd const fd, char* *a_newline)
{
	static t_size	buf_pos = 0;
	static char		buffer[BUFF_SIZE + 1] = {0};
	int				status = 0;
	int				offset = 0;
	char			*temp = NULL;
	t_bool			end_of_buffer = FALSE;
	t_bool			done_new_line = FALSE;

	if (!(*a_newline = ft_strnew(0)))
		return (GNL_ERROR);
	while (!done_new_line)
	{
		if (buf_pos == BUFF_SIZE)
			end_of_buffer = TRUE;
		if (end_of_buffer)
		{
			buf_pos = 0;
			end_of_buffer = FALSE;
			ft_memclr(buffer, BUFF_SIZE);
			status = read(fd, buffer, BUFF_SIZE);
			if (status < 0)
			{
				perror("getnextline: couldn't read file");
				return (GNL_ERROR);
			}
			if (status == 0)
				return (GNL_END);
		}
		temp = ft_strchr(buffer + buf_pos, '\n');
		if (temp == NULL)
		{
			ft_strappend(a_newline, buffer + buf_pos);
			end_of_buffer = TRUE;
		}
		else
		{
			offset = temp - (buffer + buf_pos);
			temp = ft_strndup(buffer + buf_pos, offset);
			ft_strappend(a_newline, temp);
			ft_strdel(&temp);
			buf_pos += offset + 1;
			return (GNL_LINE);
		}
	}
	return (status);
}

int				ft_getnextline(t_fd const fd, char* *a_line)
{
	char			*new_line = NULL;
	int				status = GNL_ERROR;

	if (a_line == NULL || BUFF_SIZE < 0 || fd < 0)
		return (GNL_ERROR);
	new_line = NULL;
	status = gnl_read(fd, &new_line);
	if (status < 0)
	{
		ft_strdel(&new_line);
		return (GNL_ERROR);
	}
	*a_line = new_line;
	return (status);
}
