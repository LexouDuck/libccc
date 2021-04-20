
#include "libccc/memory.h"



void	c_memset(void *ptr, t_u8 byte, t_size n)
{
	t_u8	*result;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (ptr == NULL)
		return ;
#endif
	byte &= 0xFF;
	result = (t_u8 *)ptr;
	i = 0;
	while (i < n)
	{
		result[i] = byte;
		++i;
	}
}



void	c_memclr(void *ptr, t_size n)
{
	t_u8	*result;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (ptr == NULL)
		return ;
#endif
	result = (t_u8 *)ptr;
	i = 0;
	while (i < n)
	{
		result[i] = 0;
		++i;
	}
}
