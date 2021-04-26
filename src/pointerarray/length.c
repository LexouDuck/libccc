
#include "libccc/memory.h"



t_u32		PointerArray_Length(void const** a_ptrarr)
{
	t_u32		i;

	LIBCONFIG_HANDLE_NULLPOINTER(a_ptrarr, 0)
	i = 0;
	while (((void**)a_ptrarr)[i])
	{
		++i;
	}
	return (i);
}
