
#include "libccc_memory.h"



void	*c_memmove(void *dest, void const *src, t_size n)
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
	if (dest && dest == src)
		return (dest);
	result = (t_u8 *)dest;
	source = (t_u8 *)src;
	if (source < result && source + n >= result)
	{
		i = n;
		while (i--)
			result[i] = source[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			result[i] = source[i];
			++i;
		}
	}
	return (dest);
}
