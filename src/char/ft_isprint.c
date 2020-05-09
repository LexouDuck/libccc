/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char/ft_isprint.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_char.h"

inline int		ft_isprint(int c)
{
	return (0x20 <= c && c <= 0x7E);
}

inline int		ft_isascii(int c)
{
	return (0x00 <= c && c <= 0x7F);
}

inline int		ft_isspace(int c)
{
	return ((c == ' ') || ('\t' <= c && c <= '\r'));
}

inline int		ft_ispunct(int c)
{
	return (('!' <= c && c <= '/') ||
			(':' <= c && c <= '@') ||
			('[' <= c && c <= '`') ||
			('{' <= c && c <= '~'));
}
