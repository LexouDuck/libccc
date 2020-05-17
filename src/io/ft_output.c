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

#include "libft_io.h"



inline void	ft_output_char(char c)
{
	ft_write_str(STDOUT, &c);
}



inline void	ft_output_str(char const *str)
{
	ft_write_str(STDOUT, str);
}



inline void	ft_output_line(char const *str)
{
	ft_write_line(STDOUT, str);
}



inline void	ft_output_strls(char const **strls)
{
	ft_write_strls(STDOUT, strls);
}



inline void	ft_output_memory(t_u8 const *ptr, t_size n, t_u8 cols)
{
	ft_write_memory(STDOUT, ptr, n, cols);
}
