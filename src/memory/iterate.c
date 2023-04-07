
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



void	Memory_Iterate(void* ptr, t_size n, void (*f)(t_u8 byte))
{
	t_uint i;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, "pointer given is NULL")
		return;
	for (i = 0; i < n; ++i)
	{
		f(((t_u8*)ptr)[i]);
	}
}


void	Memory_Iterate_I(void* ptr, t_size n, void (*f)(t_u8 byte, t_uint index))
{
	t_uint i;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, "pointer given is NULL")
		return;
	for (i = 0; i < n; ++i)
	{
		f(((t_u8*)ptr)[i], i);
	}
}
