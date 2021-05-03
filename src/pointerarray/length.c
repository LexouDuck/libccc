
#include "libccc/pointerarray.h"



t_u32		PointerArray_Length(void const** a_ptrarr)
{
	t_u32		i;

	LIBCONFIG_HANDLE_NULLPOINTER(0, a_ptrarr)
	i = 0;
	while (((void**)a_ptrarr)[i])
	{
		++i;
	}
	return (i);
}
