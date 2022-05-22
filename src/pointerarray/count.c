
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_uint	PointerArray_Count(void const* const* ptrarr, void const* ptr)
{
	t_uint	result = 0;
	t_uint	length;

	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointerarray given is NULL")
		return (0);
	length = PointerArray_Length(ptrarr);
	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, "pointer given is NULL")
		return (0);
	for (t_uint i = 0; i < length; ++i)
	{
		if (ptrarr[i] == ptr)
			result += 1;
	}
	return (result);
}
