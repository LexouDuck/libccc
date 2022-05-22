
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



t_size	Memory_Print(t_char* *dest, void const* ptr, t_size n)
{
	t_char*	result;
	t_u8	byte;
	t_char	hi;
	t_char	lo;
	t_size	i = 0;

	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, NULL)
		return (0);
	result = (t_char*)Memory_Alloc(n * 3);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (0);
	for (i = 0; i < n; ++i)
	{
		byte = ((t_u8 const* )ptr)[i];
		hi = ((byte >> 4) & 0xF);
		lo = (byte & 0xF);
		result[i * 3 + 0] = hi + (hi < 10 ? '0' : 'A' - 10);
		result[i * 3 + 1] = lo + (lo < 10 ? '0' : 'A' - 10);
		result[i * 3 + 2] = (i + 1 == n) ? '\0' : ' ';
	}
	if (dest)	*dest = result;
	return (i * 3);
}



inline
t_char*	Memory_ToString(void const* ptr, t_size n)
{
	t_char*	result = NULL;
	Memory_Print(&result, ptr, n);
	return (result);
}
