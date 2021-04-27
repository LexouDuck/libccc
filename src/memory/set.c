
#include "libccc/memory.h"



void	Memory_Set(void* ptr, t_u8 byte, t_size n)
{
	t_u8*	result;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(, ptr)
	byte &= 0xFF;
	result = (t_u8* )ptr;
	i = 0;
	while (i < n)
	{
		result[i] = byte;
		++i;
	}
}



void	Memory_Clear(void* ptr, t_size n)
{
	t_u8*	result;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(, ptr)
	result = (t_u8* )ptr;
	i = 0;
	while (i < n)
	{
		result[i] = 0;
		++i;
	}
}
