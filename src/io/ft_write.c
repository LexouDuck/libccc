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
**	-	void	write(int fd, char* buffer, size_t n);
*/
#include <unistd.h>

#include "libft_convert.h"
#include "libft_io.h"



inline void	ft_write_char(int fd, char c)
{
	write(fd, &c, 1);
}



inline void	ft_write_str(int fd, const char *str)
{
	if (str)
	{
		write(fd, str, ft_strlen(str));
	}
}



inline void	ft_write_line(int fd, const char *str)
{
	if (str)
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
}



void		ft_write_strls(int fd, const char **strls)
{
	int i;

	if (!strls)
		return ;
	i = 0;
	while (strls[i])
	{
		write(fd, strls[i], ft_strlen(strls[i]));
		write(fd, "\n", 1);
		++i;
	}
}



void		ft_write_memory(int fd, t_u8 const *ptr, t_size n, t_u8 cols)
{
	t_u8	nibble;
	t_size	i;

	if (!ptr || n == 0 || cols == 0)
		return ;
	i = 0;
	while (i < n)
	{
		nibble = (ptr[i] & 0xF0) >> 4;
		nibble += (nibble < 10 ? '0' : 'A' - 10);
		write(fd, &nibble, 1);
		nibble = (ptr[i] & 0x0F);
		nibble += (nibble < 10 ? '0' : 'A' - 10);
		write(fd, &nibble, 1);
		++i;
		write(fd, (i % cols == 0 ? "\n" : " "), 1);
	}
}
