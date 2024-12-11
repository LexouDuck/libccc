
#include "libccc/memory.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
extern inline
void*	Memory_Find(void const* ptr, t_u8 byte, t_size n)
{ return (memchr(ptr, byte, n)); }
#else
void*	Memory_Find(void const* ptr, t_u8 byte, t_size n)
{
	t_u8*	result;
	t_size	i;

	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, "pointer given is NULL")
		return (NULL);
	byte &= 0xFF;
	result = (t_u8* )ptr;
	i = 0;
	while (i < n)
	{
		if (result[i] == byte)
			return (result + i);
		++i;
	}
	CCCERROR(TRUE, ERROR_NOTFOUND,
		"no byte 0x%2.2X found in memory region 0x%p (length: "SF_SIZE")", byte, ptr, n);
	return (NULL);
}
#endif
