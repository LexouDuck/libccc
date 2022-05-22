
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**		PointerArray_Map(void* const* ptrarr,
	void* (*map)(void const* ptr))
{
	void**	result;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return (NULL);
	result = PointerArray_New(PointerArray_Length((void const* const*)ptrarr), NULL);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (t_uint i = 0; ptrarr[i]; ++i)
	{
		result[i] = map(ptrarr[i]);
	}
	return (result);
}



void**		PointerArray_Map_I(void* const* ptrarr,
	void* (*map)(void const* ptr, t_uint index))
{
	void**	result;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return (NULL);
	result = PointerArray_New(PointerArray_Length((void const* const*)ptrarr), NULL);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (t_uint i = 0; ptrarr[i]; ++i)
	{
		result[i] = map(ptrarr[i], i);
	}
	return (result);
}
