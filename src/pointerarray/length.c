
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_uint	PointerArray_Length(void const* const* ptrarr)
{
	t_uint	i;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (0);)
	i = 0;
	while (ptrarr[i])
	{
		++i;
	}
	return (i);
}
