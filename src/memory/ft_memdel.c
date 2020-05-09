/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory/ft_memdel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"

inline void	ft_memdel(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
/*
**	if (ptr == NULL)
**		return (NULL);
*/
