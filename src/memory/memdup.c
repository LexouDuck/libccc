
#include "libccc_memory.h"



void	*c_memdup(const void *ptr, t_size n)
{
	t_u8	*result;
	t_u8	*source;
	t_size	i;

#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
	if (ptr == NULL)
		return (NULL);
#endif
	if (!(result = (t_u8 *)c_memalloc(n)))
		return (NULL);
	source = (t_u8 *)ptr;
	i = 0;
	while (i < n)
	{
		result[i] = source[i];
		++i;
	}
	return ((void *)result);
}
