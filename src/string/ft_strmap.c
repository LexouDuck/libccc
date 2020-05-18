/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_string.h"



char	*ft_strmap(char const *str, char (*f)(char))
{
	char	*result;
	t_size	length;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || f == NULL)
		return (NULL);
#endif
	length = 0;
	while (str[length])
		++length;
	if (!(result = (char *)ft_memalloc(length + 1)))
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = f(str[i]);
		++i;
	}
	result[i] = '\0';
	return (result);
}



char	*ft_strmapi(char const *str, char (*f)(t_size, char))
{
	char	*result;
	t_size	length;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || f == NULL)
		return (NULL);
#endif
	length = 0;
	while (str[length])
		++length;
	if (!(result = (char *)ft_memalloc(length + 1)))
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = f(i, str[i]);
		++i;
	}
	result[i] = '\0';
	return (result);
}



char	*ft_strmap_inplace(char **a_str, char (*f)(char))
{
	char	*tmp;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_str == NULL || *a_str == NULL || f == NULL)
		return (NULL);
#endif
	tmp = ft_strmap(*a_str, f);
	ft_strdel(a_str);
	*a_str = tmp;
	return (tmp);
}
