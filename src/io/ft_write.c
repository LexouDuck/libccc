/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/07 02:48:44 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Functions used from <stdlib.h>:
**	-	int	write(int fd, char* buffer, size_t n);
*/
#include <unistd.h>

#include "libft_io.h"
#include "libft_string.h"
#include "libft_convert.h"



inline int	ft_write_char(int fd, char c)
{
	if (write(fd, &c, 1) < 0)
		return (ERROR);
	return (OK);
}



inline int	ft_write_str(int fd, const char *str)
{
	if (str == NULL)
		return (OK);
	if (write(fd, str, ft_strlen(str)) < 0)
		return (ERROR);
	return (OK);
}



inline int	ft_write_line(int fd, const char *str)
{
	if (str == NULL)
		return (OK);
	if (write(fd, str, ft_strlen(str)) < 0)	return (ERROR);
	if (write(fd, "\n", 1) < 0)				return (ERROR);
	return (OK);
}



int		ft_write_strls(int fd, const char **strls)
{
	if (strls == NULL)
		return (OK);
	int i = 0;
	while (strls[i])
	{
		if (write(fd, strls[i], ft_strlen(strls[i])) < 0)	return (ERROR);
		if (write(fd, "\n", 1) < 0)							return (ERROR);
		++i;
	}
	return (OK);
}



int		ft_write_memory(int fd, t_u8 const *ptr, t_size n, t_u8 cols)
{
	if (ptr == NULL || n == 0 || cols == 0)
		return (OK);
	t_u8	nibble;
	t_size	i = 0;
	while (i < n)
	{
		nibble = (ptr[i] & 0xF0) >> 4;
		nibble += (nibble < 10 ? '0' : 'A' - 10);
		if (write(fd, &nibble, 1) < 0)	return (ERROR);
		nibble = (ptr[i] & 0x0F);
		nibble += (nibble < 10 ? '0' : 'A' - 10);
		if (write(fd, &nibble, 1) < 0)	return (ERROR);
		++i;
		if (write(fd, (i % cols == 0 ? "\n" : " "), 1) < 0)	return (ERROR);
	}
	return (OK);
}
