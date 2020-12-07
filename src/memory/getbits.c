
#include "libft_memory.h"



t_u64	ft_getbits(t_u64 value, t_u8 bit, t_u8 length)
{
	t_u64	mask;
	t_u8	i;

	mask = 0;
	i = 0;
	while (i < length)
	{
		mask <<= 1;
		mask |= 1;
		++i;
	}
	return ((value >> bit) & mask);
}
