
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_Concat(void* const* ptrarr1, void* const* ptrarr2)
{
	void**	result;
	t_size	length1;
	t_size	length2;
	t_size	i;

	if CCCERROR((ptrarr1 == NULL), ERROR_NULLPOINTER, "left-hand-side array given is NULL")
		return (NULL);
	if CCCERROR((ptrarr2 == NULL), ERROR_NULLPOINTER, "right-hand-side array given is NULL")
		return (NULL);
	length1 = PointerArray_Length((void const* const*)ptrarr1);
	length2 = PointerArray_Length((void const* const*)ptrarr2);
	result = (void**)Memory_Allocate(sizeof(void*) * (length1 + length2 + 1));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (i < length1)
	{
		result[i] = ptrarr1[i];
		++i;
	}
	i = 0;
	while (i < length2)
	{
		result[length1 + i] = ptrarr2[i];
		++i;
	}
	result[length1 + length2] = NULL;
	return (result);
}



void**	PointerArray_Append(void** *a_dest, void* const* src)
{
	void**	tmp;

	if CCCERROR((a_dest == NULL), ERROR_NULLPOINTER, "destination array address given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "array to append given is NULL")
		return (NULL);
	tmp = PointerArray_Concat((void* const*)*a_dest, src);
	PointerArray_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



void**	PointerArray_Prepend(void* const* src, void** *a_dest)
{
	void**	tmp;

	if CCCERROR((a_dest == NULL), ERROR_NULLPOINTER, "destination array address given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "array to prepend given is NULL")
		return (NULL);
	tmp = PointerArray_Concat(src, (void* const*)*a_dest);
	PointerArray_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



void**	PointerArray_Merge(void** *a_ptrarr1, void** *a_ptrarr2)
{
	void**	result;

	if CCCERROR((a_ptrarr1 == NULL), ERROR_NULLPOINTER, "left-hand-side array given is NULL")
		return (NULL);
	if CCCERROR((a_ptrarr2 == NULL), ERROR_NULLPOINTER, "right-hand-side array given is NULL")
		return (NULL);
	result = PointerArray_Concat((void* const*)*a_ptrarr1, (void* const*)*a_ptrarr2);
	PointerArray_Delete(a_ptrarr1);
	PointerArray_Delete(a_ptrarr2);
	*a_ptrarr1 = result;
	*a_ptrarr2 = result;
	return (result);
}
