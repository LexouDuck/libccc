/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io/ft_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Functions used from <stdlib.h>:
**	-	void	read(int fd, char* buffer, size_t n);
*/
#include <unistd.h>

#include "libft_memory.h"
#include "libft_string.h"
#include "libft_stringarray.h"
#include "libft_io.h"


static int	ft_readfile_error(int result, char* *a_file)
{
	if (result < 0)
	{
		if (*a_file)
		{
			ft_memfree(*a_file);
			*a_file = NULL;
		}
		return (ERROR);
	}
	else
		return (OK);
}

int			ft_readfile(int const fd, char* *a_file, t_size max)
{
	int		result;
	char	buffer[BUFF_SIZE + 1];
	char	*temp;
	t_size	length;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_file == NULL)
		return (ERROR);
#endif
	if (!(*a_file = ft_strnew(1)))
		return (ERROR);
	buffer[BUFF_SIZE] = '\0';
	length = 0;
	while ((result = read(fd, buffer, BUFF_SIZE)) > 0 &&
		(length += result) < max)
	{
		temp = *a_file;
		if (result < BUFF_SIZE)
			buffer[result] = '\0';
		if (!(*a_file = ft_strjoin(temp, buffer)))
			return (ERROR);
		ft_memfree(temp);
	}
	return (ft_readfile_error(result, a_file));
}



int			ft_readlines(int const fd, char** *a_strls)
{
	char	**result;
	int		status;
	int		i;
	char	**line;

	status = -2;
	line = ft_strarrnew(1);
	result = ft_strarrnew(0);
	i = 0;
	while ((status = ft_getnextline(fd, line)) == GNL_LINE)
	{
		result = ft_strarrappend(&result, (char const **)line);
		ft_strdel(line);
	}
	ft_strarrdel(&line);
	if (status == GNL_ERROR)
	{
		ft_strarrdel(&result);
		return (ERROR);
	}
	*a_strls = result;
	return (OK);
}
