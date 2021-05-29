
#include "libccc/memory.h"

#include LIBCONFIG_HANDLE_INCLUDE



t_u64	Memory_GetBits(t_u64 value, t_u8 bit, t_u8 length)
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
