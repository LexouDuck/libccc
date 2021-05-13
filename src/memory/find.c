
#include "libccc/memory.h"



void*	Memory_Find(void const* ptr, t_u8 byte, t_size n)
{
	t_u8*	result;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, ptr)
	byte &= 0xFF;
	result = (t_u8* )ptr;
	i = 0;
	while (i < n)
	{
		if (result[i] == byte)
			return (result + i);
		++i;
	}
	return (NULL);
}
/*
**	if (ptr == NULL)
**		return (NULL);
*/
