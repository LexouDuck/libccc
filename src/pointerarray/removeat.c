
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void	PointerArray_RemoveAt(void** ptrarr, t_uint index)
{
	void**	result;
	t_uint	length;

	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return;
	length = PointerArray_Length((void const* const*)ptrarr);
	if CCCERROR((length <= index), ERROR_INDEX2LARGE, 
		"index given (" SF_UINT ") is beyond end of ptrarr (length: " SF_UINT ")", index, length)	
		return;
	length -= 1;
	if (length == 0)
	{
		Memory_Free(ptrarr);
		ptrarr = NULL;
		return;
	}
//	result = (void const**)Memory_Allocate(sizeof(void const*) * length);
//	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
//		return;
	result = ptrarr;
	for (t_uint i = index; i < length; ++i)
	{
		result[i] = ptrarr[i + 1];
	}
//	Memory_Free(ptrarr);
//	ptrarr = result;
}


void	PointerArray_RemoveAt_F(void** ptrarr, t_uint index, void (*del)(void*))
{
	void**	result;
	t_uint	length;

	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return;
	length = PointerArray_Length((void const* const*)ptrarr);
	if CCCERROR((length <= index), ERROR_INDEX2LARGE, 
		"index given (" SF_UINT ") is beyond end of ptrarr (length: " SF_UINT ")", index, length)	
		return;
	length -= 1;
	if (length == 0)
	{
		Memory_Free(ptrarr);
		ptrarr = NULL;
		return;
	}
//	result = (void const**)Memory_Allocate(length * sizeof(void const*));
//	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
//		return;
	result = ptrarr;
	for (t_uint i = index; i < length; ++i)
	{
		if (i == index)
		{
			del(ptrarr[i]);
			result[i] = ptrarr[i + 1];
		}
		else result[i] = ptrarr[i + 1];
	}
//	Memory_Free(ptrarr);
//	ptrarr = result;
}
