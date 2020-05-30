/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strrep.c                                 :+:      :+:    :+:   */
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



char		*ft_strrep_char(char const *str, char const old, char const new)
{
	char	*result;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (old == new)
		return (ft_strdup(str));
	if (str == NULL)
		return (NULL);
#endif
	if (old == '\0')
		return (NULL);
	i = 0;
	while (str[i])
		++i;
	if (!(result = (char *)ft_memalloc(i + 1)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		result[i] = (str[i] == old) ? new : str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}



char		*ft_strrep_charset(char const *str, char const *old, char const *new)
{
	char	*result;
	t_size	i;
	t_size	j;
	int		c_index;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (old == new)
		return (ft_strdup(str));
	if (str == NULL || old == NULL || new == NULL)
		return (NULL);
#endif
	if (ft_strlen(old) != ft_strlen(new))
		return (NULL);
	i = 0;
	while (old[i])
	{
		j = i;
		while (old[++j])
			if (old[i] == old[j])
				return (NULL);
		++i;
	}
	if (!(result = (char *)ft_memalloc(i + 1)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		if ((c_index = ft_strichr(old, str[i])) >= 0)
			result[i] = new[c_index];
		++i;
	}
	result[i] = '\0';
	return (result);
}



char		*ft_strrep_str(char const *str, char const *old, char const *new)
{
	char	*result;
	char	**strarr;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (old == new)
		return (ft_strdup(str));
	if (str == NULL || old == NULL || new == NULL)
		return (NULL);
#endif
	strarr = ft_strsplit_str(str, old);
	result = ft_strarrjoin((const char **)strarr, new);
	ft_strarrdel(&strarr);
	return (result);
}



void		ft_strrep_char_inplace(char *str, char const old, char const new)
{
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return ;
#endif
	if (old == '\0')
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == old)
			str[i] = new;
		++i;
	}
}



void		ft_strrep_charset_inplace(char *str, char const *old, char const *new)
{
	t_size	i;
	t_size	j;
	int		c_index;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || old == NULL || new == NULL)
		return ;
#endif
	if (ft_strlen(old) != ft_strlen(new))
		return ;
	i = 0;
	while (old[i])
	{
		j = i;
		while (old[++j])
			if (old[i] == old[j])
				return ;
		++i;
	}
	i = 0;
	while (str[i])
	{
		if ((c_index = ft_strichr(old, str[i])) >= 0)
			str[i] = new[c_index];
		++i;
	}
}



void	ft_strrep_str_inplace(char **a_str, char const *old, char const *new)
{
	char	*tmp;
	tmp = ft_strrep_str(*a_str, old, new);
	ft_strdel(a_str);
	*a_str = tmp;
}
