
#include "libccc/memory.h"



void	c_memrep(void *ptr, t_u8 old, t_u8 new, t_size n)
{
	t_u8	*result;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (ptr == NULL)
		return ;
#endif
	result = (t_u8*)ptr;
	i = 0;
	while (i < n)
	{
		if (result[i] == old)
			result[i] = new;
		++i;
	}
}
