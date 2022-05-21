
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**		PointerArray_Duplicate(void* const* ptrarr)
{
	t_uint	i;
	void**	result;

	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array address given is NULL")
		return (NULL);
	result = PointerArray_New(PointerArray_Length((void const* const*)ptrarr), NULL);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (ptrarr[i])
	{
		result[i] = ptrarr[i];
		++i;
	}
	return (result);
}
