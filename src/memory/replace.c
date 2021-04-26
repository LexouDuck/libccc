
#include "libccc/memory.h"



void	Memory_Replace(void* ptr, t_u8 old, t_u8 new, t_size n)
{
	t_u8*	result;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(ptr, )
	result = (t_u8*)ptr;
	i = 0;
	while (i < n)
	{
		if (result[i] == old)
			result[i] = new;
		++i;
	}
}
