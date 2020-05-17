/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strpad.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_string.h"



char	*ft_strpad(char const *str, char c, t_size size)
{
	char	*result;
	t_size	offset;
	t_size	length;
	t_size	i;

#if HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	if (!(result = (char *)ft_memalloc(size + 1)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		result[i] = c;
		++i;
	}
	length = 0;
	while (str[length])
		++length;
	offset = (size - length) / 2;
	i = 0;
	while (str[i])
	{
		result[offset + i] = str[i];
		++i;
	}
	return (result);
}



char	*ft_strpad_l(char const *str, char c, t_size size)
{
	char	*result;
	t_size	offset;
	t_size	length;
	t_size	i;

#if HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	if (!(result = (char *)ft_memalloc(size + 1)))
		return (NULL);
	length = 0;
	while (str[length])
		++length;
	offset = size - length;
	i = 0;
	while (i < (t_size)offset)
	{
		result[i] = c;
		++i;
	}
	while (i < size)
	{
		result[i] = str[i - offset];
		++i;
	}
	result[size] = '\0';
	return (result);
}



char	*ft_strpad_r(char const *str, char c, t_size size)
{
	char	*result;
	t_size	i;

#if HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	if (!(result = (char *)ft_memalloc(size + 1)))
		return (NULL);
	i = 0;
	while (i < size && str[i])
	{
		result[i] = str[i];
		++i;
	}
	while (i < size)
	{
		result[i] = c;
		++i;
	}
	result[size] = '\0';
	return (result);
}
