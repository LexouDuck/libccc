
#include "libccc_memory.h"



void	*c_memcpy(void *dest, void const *src, t_size n)
{
	t_u8	*result;
	t_u8	*source;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (dest == NULL)
		return (NULL);
	if (src == NULL)
		return (dest);
#endif
	result = (t_u8 *)dest;
	source = (t_u8 *)src;
	i = 0;
	while (i < n)
	{
		result[i] = source[i];
		++i;
	}
	return (dest);
}



void	*c_memccpy(void *dest, void const *src, t_u8 byte, t_size n)
{
	t_u8	*result;
	t_u8	*source;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (dest == NULL || src == NULL)
		return (NULL);
#endif
	result = (t_u8 *)dest;
	source = (t_u8 *)src;
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
