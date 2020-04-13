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

#include "../../libft_string.h"

char	*ft_strmerge(char **a_s1, char **a_s2)
{
	char	*result;

	result = ft_strjoin(*a_s1, *a_s2);
	ft_strdel(a_s1);
	ft_strdel(a_s2);
	*a_s1 = result;
	*a_s2 = result;
	return (result);
}

char	*ft_strappend(char **dest, char const *src)
{
	char	*tmp;

	tmp = ft_strjoin(*dest, src);
	ft_strdel(dest);
	*dest = tmp;
	return (*dest);
}

char	*ft_strprepend(char const *src, char **dest)
{
	char	*tmp;

	tmp = ft_strjoin(src, *dest);
	ft_strdel(dest);
	*dest = tmp;
	return (*dest);
}

char	*ft_strinsert_inplace(char **dest, char const *src, t_u32 index)
{
	char	*tmp;

	tmp = ft_strsub(*dest, 0, index);
	ft_strappend(&tmp, src);
	ft_strappend(&tmp, (*dest) + index);
	ft_strdel(dest);
	*dest = tmp;
	return (*dest);
}