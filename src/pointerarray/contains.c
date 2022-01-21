
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_bool	PointerArray_Contains(void const* const* ptrarr, void const* ptr)
{
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (FALSE);)
	HANDLE_ERROR(NULLPOINTER, (ptr    == NULL), return (FALSE);)
	length = PointerArray_Length(ptrarr);
	for (t_uint i = 0; i < length; ++i)
	{
		if (ptrarr[i] == ptr)
			return (TRUE);
	}
	return (FALSE);
}
