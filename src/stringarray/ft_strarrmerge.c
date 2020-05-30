/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringarray/ft_strarrmerge.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_string.h"
#include "libft_stringarray.h"


static char		**ft_strarrcombine(char const** strarr1, char const** strarr2) //see strjoin
{
	char	**result;
	t_size	length1;
	t_size	length2;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (strarr1 == NULL || strarr2 == NULL)
		return (NULL);
#endif
	length1 = ft_strarrlen(strarr1);
	length2 = ft_strarrlen(strarr2);
	if (!(result = (char**)ft_memalloc(sizeof(char*) * (length1 + length2 + 1))))
		return (NULL);
	i = 0;
	while (i < length1)
	{
		result[i] = ft_strdup(strarr1[i]);
		++i;
	}
	i = 0;
	while (i < length2)
	{
		result[length1 + i] = ft_strdup(strarr2[i]);
		++i;
	}
	result[length1 + length2] = NULL;
	return (result);
}



char	**ft_strarrmerge(char** *a_strarr1, char** *a_strarr2)
{
	char	**result;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_strarr1 == NULL || a_strarr2 == NULL)
		return (NULL);
#endif
	result = ft_strarrcombine((char const**)*a_strarr1, (char const**)*a_strarr2);
	ft_strarrdel(a_strarr1);
	ft_strarrdel(a_strarr2);
	*a_strarr1 = result;
	*a_strarr2 = result;
	return (result);
}



char	**ft_strarrappend(char** *a_dest, char const** src)
{
	char	**tmp;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_dest == NULL || src == NULL)
		return (NULL);
#endif
	tmp = ft_strarrcombine((char const**)*a_dest, src);
	ft_strarrdel(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



char	**ft_strarrprepend(char const** src, char** *a_dest)
{
	char	**tmp;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_dest == NULL || src == NULL)
		return (NULL);
#endif
	tmp = ft_strarrcombine(src, (char const**)*a_dest);
	ft_strarrdel(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



char	**ft_strarrinsert_inplace(char** *a_dest, char const** src, t_u32 index)
{
	char	**tmp;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_dest == NULL || src == NULL)
		return (NULL);
#endif
	tmp = ft_strarrsub((char const**)*a_dest, 0, index);
	ft_strarrappend(&tmp, src);
	ft_strarrappend(&tmp, (char const**)(*a_dest) + index);
	ft_strarrdel(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}
