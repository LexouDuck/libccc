/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strchr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"



char	*ft_strchr(char const *str, char c)
{
	size_t	i;

#if HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	i = 0;
	while (TRUE)
	{
		if (str[i] == c)
			return ((char *)str + i);
		if (str[i] == '\0')
			break ;
		++i;
	}
	return (NULL);
}



char	*ft_strrchr(char const *str, char c)
{
	size_t	i;

#if HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	i = 0;
	while (str[i])
		++i;
	if (c == '\0')
		return ((char *)(str + i));
	else if (i == 0)
		return (NULL);
	while (i--)
	{
		if (str[i] == c)
			return ((char *)str + i);
	}
	return (NULL);
}



char	*ft_strnchr(char const *str, char c, size_t n)
{
	size_t	i;

#if HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	i = 0;
	while (i < n)
	{
		if (str[i] == c)
			return ((char *)str + i);
		if (str[i] == '\0')
			break ;
		++i;
	}
	return (NULL);
}



t_s32	ft_strichr(char const *str, char c)
{
	t_s32	i;

#if HANDLE_NULLPOINTERS
	if (str == NULL)
		return (-1);
#endif
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}
