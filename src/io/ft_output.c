/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/07 02:47:29 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_io.h"

inline void	ft_output_char(char c)
{
	write(STDOUT, &c, 1);
}

inline void	ft_output_str(char const *str)
{
	if (str)
		write(STDOUT, str, ft_strlen(str));
}

inline void	ft_output_line(char const *str)
{
	if (str)
	{
		write(STDOUT, str, ft_strlen(str));
		write(STDOUT, "\n", 1);
	}
}

inline void	ft_output_strls(char const **strls)
{
	if (strls)
		ft_write_strls(STDOUT, strls);
}

inline void	ft_output_memory(t_u8 const *ptr, size_t n, t_u8 cols)
{
	if (ptr)
		ft_write_memory(STDOUT, ptr, n, cols);
}
