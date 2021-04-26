
#include "libccc/memory.h"



void*	Memory_Copy(void* dest, void const* src, t_size n)
{
	t_u8*	result;
	t_u8*	source;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(dest, NULL)
	LIBCONFIG_HANDLE_NULLPOINTER(src, dest)
	result = (t_u8*)dest;
	source = (t_u8*)src;
	i = 0;
	while (i < n)
	{
		result[i] = source[i];
		++i;
	}
	return (dest);
}



void*	Memory_Copy_C(void* dest, void const* src, t_u8 byte, t_size n)
{
	t_u8*	result;
	t_u8*	source;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(dest, NULL)
	LIBCONFIG_HANDLE_NULLPOINTER(src, dest)
	result = (t_u8*)dest;
	source = (t_u8*)src;
	i = 0;
	while (source[i] != byte)
	{
		if (i == n)
			return (NULL);
		result[i] = source[i];
		++i;
	}
	result[i] = byte;
	return (result + i + 1);
}
