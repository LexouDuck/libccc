
#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
void	Memory_Set(void* ptr, t_u8 byte, t_size n)
{ memset(ptr, byte, n); }
#else
void	Memory_Set(void* ptr, t_u8 byte, t_size n)
{
	t_u8*	result;
	t_size	i;

	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, "pointer given is NULL")
		return;
	byte &= 0xFF;
	result = (t_u8* )ptr;
	i = 0;
	while (i < n)
	{
		result[i] = byte;
		++i;
	}
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
void	Memory_Clear(void* ptr, t_size n)
{ memset(ptr, 0, n); }
#else
void	Memory_Clear(void* ptr, t_size n)
{
	t_u8*	result;
	t_size	i;

	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, "pointer given is NULL")
		return;
	result = (t_u8* )ptr;
	i = 0;
	while (i < n)
	{
		result[i] = 0;
		++i;
	}
}
#endif
