/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strcpy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"



char	*ft_strcpy(char *dest, char const *src)
{
	t_size	i;

#if HANDLE_NULLPOINTERS
	if (dest == NULL)
		return (NULL);
	if (src == NULL)
		return (dest);
#endif
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}



char	*ft_strncpy(char *dest, char const *src, t_size n)
{
	char	*str;
	t_size	i;

#if HANDLE_NULLPOINTERS
	if (dest == NULL)
		return (NULL);
	if (src == NULL)
		return (dest);
#endif
	str = dest;
	i = 0;
	while (n > 0 && src[i])
	{
		str[i] = src[i];
		++i;
		--n;
	}
	while (n > 0)
	{
		str[i] = '\0';
		++i;
		--n;
	}
	return (dest);
}



t_size	ft_strlcpy(char *dest, char const *src, t_size size)
{
	t_size	i;

#if HANDLE_NULLPOINTERS
	if (dest == NULL || src == NULL)
		return (0);
#endif
	i = 0;
	while (i < size - 1 && src[i])
	{
		if (size)
			dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	i = 0;
	while (src[i])
		++i;
	return (i);
}
