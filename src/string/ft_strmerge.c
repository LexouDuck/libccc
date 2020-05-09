/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strmerge.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"



char	*ft_strmerge(char **a_str1, char **a_str2)
{
	char	*result;

#if HANDLE_NULLPOINTERS
	if (a_str1 == NULL || a_str2 == NULL)
		return (NULL);
#endif
	result = ft_strjoin(*a_str1, *a_str2);
	ft_strdel(a_str1);
	ft_strdel(a_str2);
	*a_str1 = result;
	*a_str2 = result;
	return (result);
}



char	*ft_strappend(char **dest, char const *src)
{
	char	*tmp;

#if HANDLE_NULLPOINTERS
	if (dest == NULL || src == NULL)
		return (NULL);
#endif
	tmp = ft_strjoin(*dest, src);
	ft_strdel(dest);
	*dest = tmp;
	return (*dest);
}



char	*ft_strprepend(char const *src, char **dest)
{
	char	*tmp;

#if HANDLE_NULLPOINTERS
	if (dest == NULL || src == NULL)
		return (NULL);
#endif
	tmp = ft_strjoin(src, *dest);
	ft_strdel(dest);
	*dest = tmp;
	return (*dest);
}



char	*ft_strinsert_inplace(char **dest, char const *src, t_u32 index)
{
	char	*tmp;

#if HANDLE_NULLPOINTERS
	if (dest == NULL || src == NULL)
		return (NULL);
#endif
	tmp = ft_strsub(*dest, 0, index);
	ft_strappend(&tmp, src);
	ft_strappend(&tmp, (*dest) + index);
	ft_strdel(dest);
	*dest = tmp;
	return (*dest);
}
