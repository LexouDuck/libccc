
#include "libccc/memory.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
void*	Memory_Copy(void* dest, void const* src, t_size n)
{ return (memcpy(dest, src, n)); }
#else
void*	Memory_Copy(void* dest, void const* src, t_size n)
{
	t_u8*	result;
	t_u8*	source;
	t_size	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, NULL)
		return (dest);
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
#endif



void*	Memory_Copy_C(void* dest, void const* src, t_u8 byte, t_size n)
{
	t_u8*	result;
	t_u8*	source;
	t_size	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, NULL)
		return (dest);
	result = (t_u8*)dest;
	source = (t_u8*)src;
	i = 0;
	while (i < n && source[i] != byte)
	{
		result[i] = source[i];
		++i;
	}
	if (i == n)
		return (NULL);
	result[i] = byte;
	return (result + i + 1);
}
