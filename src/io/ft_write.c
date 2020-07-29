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

#include "libft_convert.h"
#include "libft_io.h"



inline int	ft_write_char(int fd, char c)
{
	return (write(fd, &c, 1));
}



inline int	ft_write_str(int fd, const char *str)
{
	if (str)
	{
		return (write(fd, str, ft_strlen(str)));
	}
	return (OK);
}



inline int	ft_write_line(int fd, const char *str)
{
	int result = OK;
	if (str)
	{
		if ((result = write(fd, str, ft_strlen(str))))	return (result);
		if ((result = write(fd, "\n", 1)))				return (result);
	}
	return (result);
}



int		ft_write_strls(int fd, const char **strls)
{
	if (!strls)
		return (OK);
	int result = OK;
	int i = 0;
	while (strls[i])
	{
		if ((result = write(fd, strls[i], ft_strlen(strls[i]))))	return (result);
		if ((result = write(fd, "\n", 1)))							return (result);
		++i;
	}
	return (result);
}



int		ft_write_memory(int fd, t_u8 const *ptr, t_size n, t_u8 cols)
{
	if (!ptr || n == 0 || cols == 0)
		return (OK);
	int result = OK;
	t_u8	nibble;
	t_size	i = 0;
	while (i < n)
	{
		nibble = (ptr[i] & 0xF0) >> 4;
		nibble += (nibble < 10 ? '0' : 'A' - 10);
		result = write(fd, &nibble, 1);
		if (result)	return (result);
		nibble = (ptr[i] & 0x0F);
		nibble += (nibble < 10 ? '0' : 'A' - 10);
		result = write(fd, &nibble, 1);
		if (result)	return (result);
		++i;
		result = write(fd, (i % cols == 0 ? "\n" : " "), 1);
		if (result)	return (result);
	}
	return (result);
}
