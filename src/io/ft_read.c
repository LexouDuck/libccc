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

#include "libft_io.h"
#include "libft_string.h"

static int	ft_readfile_error(int result, char **file)
{
	if (result < 0)
	{
		if (*file)
		{
			free(*file);
			*file = NULL;
		}
		return (ERROR);
	}
	else
		return (OK);
}

int			ft_readfile(int const fd, char **file, size_t max)
{
	int		result;
	char	buffer[BUFF_SIZE + 1];
	char	*temp;
	size_t	length;

	if (!(*file = ft_strnew(1)))
		return (ERROR);
	buffer[BUFF_SIZE] = '\0';
	length = 0;
	while ((result = read(fd, buffer, BUFF_SIZE)) > 0 &&
		(length += result) < max)
	{
		temp = *file;
		if (result < BUFF_SIZE)
			buffer[result] = '\0';
		if (!(*file = ft_strjoin(temp, buffer)))
			return (ERROR);
		free(temp);
	}
	return (ft_readfile_error(result, file));
}

/*
** TODO actually code this
*/

int			ft_readlines(int const fd, char ***strls)
{
	return (fd || strls);
}
