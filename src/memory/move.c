
#include "libccc/memory.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
void*	Memory_Move(void* dest, void const* src, t_size n)
{ return (memmove(dest, src, n)); }
#else
void*	Memory_Move(void* dest, void const* src, t_size n)
{
	t_u8*	result;
	t_u8*	source;
	t_size	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, NULL)
		return (dest);
	if (dest && dest == src)
		return (dest);
	result = (t_u8*)dest;
	source = (t_u8*)src;
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
#endif
