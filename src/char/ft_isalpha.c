/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char/ft_isalpha.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_char.h"



inline t_bool	ft_isalpha(int c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z'));
}

inline t_bool	ft_isupper(int c)
{
	return ('A' <= c && c <= 'Z');
}

inline t_bool	ft_islower(int c)
{
	return ('a' <= c && c <= 'z');
}
