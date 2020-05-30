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



char	*ft_strmerge(char* *a_str1, char* *a_str2)
{
	char	*result;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
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



char	*ft_strappend(char* *a_dest, char const* src)
{
	char	*tmp;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_dest == NULL || src == NULL)
		return (NULL);
#endif
	tmp = ft_strjoin(*a_dest, src);
	ft_strdel(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



char	*ft_strprepend(char const* src, char* *a_dest)
{
	char	*tmp;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_dest == NULL || src == NULL)
		return (NULL);
#endif
	tmp = ft_strjoin(src, *a_dest);
	ft_strdel(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



char	*ft_strinsert_inplace(char* *a_dest, char const* src, t_u32 index)
{
	char	*tmp;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_dest == NULL || src == NULL)
		return (NULL);
#endif
	tmp = ft_strsub(*a_dest, 0, index);
	ft_strappend(&tmp, src);
	ft_strappend(&tmp, (*a_dest) + index);
	ft_strdel(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}
