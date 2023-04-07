
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_bool	PointerArray_Has(void const* const* ptrarr, void const* const* target)
{
	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return (FALSE);
	for (t_uint i = 0; ptrarr[i]; ++i)
	{
		if (PointerArray_Contains(target, ptrarr[i]))
			return (TRUE);
	}
	return (FALSE);
}


t_bool	PointerArray_HasOnly(void const* const* ptrarr, void const* const* target)
{
	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return (FALSE);
	for (t_uint i = 0; ptrarr[i]; ++i)
	{
		if (!PointerArray_Contains(target, ptrarr[i]))
			return (FALSE);
	}
	return (TRUE);
}
