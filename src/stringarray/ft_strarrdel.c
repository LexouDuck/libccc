
#include "libft_memory.h"
#include "libft_string.h"
#include "libft_stringarray.h"



void	ft_strarrdel(char** *a_strarr)
{
	int		i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_strarr == NULL)
		return ;
#endif
	if (*a_strarr)
	{
		i = 0;
		while ((*a_strarr)[i])
		{
			ft_strdel((*a_strarr) + i);
			++i;
		}
		ft_memdel((void**)a_strarr);
	}
}
