
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_Concat(void* const* ptrarr1, void* const* ptrarr2)
{
	void**	result;
	t_size	length1;
	t_size	length2;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (ptrarr1 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (ptrarr2 == NULL), return (NULL);)
	length1 = PointerArray_Length(ptrarr1);
	length2 = PointerArray_Length(ptrarr2);
	result = (void**)Memory_Allocate(sizeof(void*) * (length1 + length2 + 1));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
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

	HANDLE_ERROR(NULLPOINTER, (a_dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (NULL);)
	tmp = PointerArray_Concat((void* const*)*a_dest, src);
	PointerArray_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



void**	PointerArray_Prepend(void* const* src, void** *a_dest)
{
	void**	tmp;

	HANDLE_ERROR(NULLPOINTER, (a_dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (NULL);)
	tmp = PointerArray_Concat(src, (void* const*)*a_dest);
	PointerArray_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



void**	PointerArray_Merge(void** *a_ptrarr1, void** *a_ptrarr2)
{
	void**	result;

	HANDLE_ERROR(NULLPOINTER, (a_ptrarr1 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (a_ptrarr2 == NULL), return (NULL);)
	result = PointerArray_Concat((void* const*)*a_ptrarr1, (void* const*)*a_ptrarr2);
	PointerArray_Delete(a_ptrarr1);
	PointerArray_Delete(a_ptrarr2);
	*a_ptrarr1 = result;
	*a_ptrarr2 = result;
	return (result);
}
