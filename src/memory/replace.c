
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



void	Memory_Replace(void* ptr, t_u8 byte_old, t_u8 byte_new, t_size n)
{
	t_u8*	result;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (ptr == NULL), return;)
	result = (t_u8*)ptr;
	i = 0;
	while (i < n)
	{
		if (result[i] == byte_old)
			result[i] = byte_new;
		++i;
	}
}
