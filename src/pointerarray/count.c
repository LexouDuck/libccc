
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_uint	PointerArray_Count(void* const* ptrarr, void const* ptr)
{
	t_uint	result = 0;
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (0);)
	length = PointerArray_Length(ptrarr);
	HANDLE_ERROR(NULLPOINTER, (ptr    == NULL), return (0);)
	for (t_uint i = 0; i < length; ++i)
	{
		if (ptrarr[i] == ptr)
			result += 1;
	}
	return (result);
}
