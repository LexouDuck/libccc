
#include "libccc/memory.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_HANDLE_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
void*	Memory_Find(void const* ptr, t_u8 byte, t_size n)
{ return (memchr(ptr, byte, n)); }
#else
void*	Memory_Find(void const* ptr, t_u8 byte, t_size n)
{
	t_u8*	result;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (ptr == NULL), return (NULL);)
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
#endif
