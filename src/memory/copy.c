
#include "libccc/memory.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_HANDLE_INCLUDE



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

	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (dest);)
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

#ifdef __IOS__ // TODO smarter check here
inline
void*	memcpy(void* dest, void const* src, size_t n)
{ return (Memory_Copy(dest, src, n)); }
#endif



void*	Memory_Copy_C(void* dest, void const* src, t_u8 byte, t_size n)
{
	t_u8*	result;
	t_u8*	source;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (dest);)
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
