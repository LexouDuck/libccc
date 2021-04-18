
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"



char		**c_strarrmap(char const** strarr, char* (*f)(char const*))
{
	t_u32	i;
	char	**result;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (strarr == NULL || *strarr == NULL || f == NULL)
		return (NULL);
#endif
	if (!(result = c_strarrnew(c_strarrlen(strarr))))
		return (NULL);
	i = 0;
	while (strarr[i])
	{
		result[i] = (*f)(strarr[i]);
		++i;
	}
	return (result);
}



void		c_strarrmap_inplace(char** *a_strarr, char* (*f)(char*))
{
	t_u32	i;
	char	*tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_strarr == NULL || *a_strarr == NULL || f == NULL)
		return ;
#endif
	i = 0;
	while ((*a_strarr)[i])
	{
		tmp = (*f)((*a_strarr)[i]);
		if (tmp != (*a_strarr)[i])
			c_strdel(*a_strarr + i);
		(*a_strarr)[i] = tmp;
		++i;
	}
}
