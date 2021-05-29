
#include "libccc/pointerarray.h"

#include LIBCONFIG_HANDLE_INCLUDE



t_u32	PointerArray_Length(void const** a_ptrarr)
{
	t_u32	i;

	HANDLE_ERROR(NULLPOINTER, (a_ptrarr == NULL), return (0);)
	i = 0;
	while (((void**)a_ptrarr)[i])
	{
		++i;
	}
	return (i);
}
