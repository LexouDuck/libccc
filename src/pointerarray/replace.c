
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_Replace(void* const* ptrarr,
	void const* ptr_old,
	void const* ptr_new)
{
	void**	result;
	t_uint	length;

	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return (NULL);
	if CCCERROR((ptr_old == NULL), ERROR_NULLPOINTER,
		"cannot replace NULL values in pointer array, NULL is used as array terminator")
		return (NULL);
	length = PointerArray_Length((void const* const*)ptrarr);
	result = PointerArray_Duplicate(ptrarr);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if (result == NULL)
		return (result);
	for (t_uint i = 0; i < length; ++i)
	{
		if (result[i] == ptr_old)
		{
			result[i] = (void*)ptr_new;
		}
	}
	return (result);
}



void**	PointerArray_ReplaceFirst(void* const* ptrarr,
	void const* ptr_old,
	void const* ptr_new,
	t_uint n)
{
	void**	result;
	t_uint	length;

	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return (NULL);
	if CCCERROR((ptr_old == NULL), ERROR_NULLPOINTER,
		"cannot replace NULL values in pointer array, NULL is used as array terminator")
		return (NULL);
	length = PointerArray_Length((void const* const*)ptrarr);
	result = PointerArray_Duplicate(ptrarr);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if (result == NULL)
		return (result);
	for (t_uint i = 0; i < length; ++i)
	{
		if (n == 0)
			return (result);
		if (result[i] == ptr_old)
		{
			result[i] = (void*)ptr_new;
			n -= 1;
		}
	}
	return (result);
}



void**	PointerArray_ReplaceLast(void* const* ptrarr,
	void const* ptr_old,
	void const* ptr_new,
	t_uint n)
{
	void**	result;
	t_uint	length;

	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return (NULL);
	if CCCERROR((ptr_old == NULL), ERROR_NULLPOINTER,
		"cannot replace NULL values in pointer array, NULL is used as array terminator")
		return (NULL);
	length = PointerArray_Length((void const* const*)ptrarr);
	result = PointerArray_Duplicate(ptrarr);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if (result == NULL)
		return (result);
	t_uint i = length;
	while (i--)
	{
		if (n == 0)
			return (result);
		if (result[i] == ptr_old)
		{
			result[i] = (void*)ptr_new;
			n -= 1;
		}
	}
	return (result);
}
