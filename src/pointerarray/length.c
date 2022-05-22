
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_uint	PointerArray_Length(void const* const* ptrarr)
{
	t_uint	i;

	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, NULL)
		return (0);
	i = 0;
	while (ptrarr[i])
	{
		++i;
	}
	return (i);
}
