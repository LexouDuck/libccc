
#include "libft_memory.h"



t_u32		ft_ptrarrlen(const void **a_ptrarr)
{
	t_u32		i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_ptrarr == NULL)
		return (0);
#endif
	i = 0;
	while (((void**)a_ptrarr)[i])
	{
		i++;
	}
	return (i);
}
