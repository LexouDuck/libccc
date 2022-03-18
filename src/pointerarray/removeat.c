
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void	PointerArray_RemoveAt(void** ptrarr, t_uint index)
{
	void**	result;
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return;)
	length = PointerArray_Length((void const* const*)ptrarr);
	HANDLE_ERROR_SF(INDEX2LARGE, (length <= index), return;,
		"index given ("SF_UINT") is beyond end of ptrarr (length: "SF_UINT")",
		index, length)
	length -= 1;
	if (length == 0)
	{
		Memory_Free(ptrarr);
		ptrarr = NULL;
		return;
	}
//	result = (void const**)Memory_Allocate(sizeof(void const*) * length);
//	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return;)
	result = ptrarr;
	for (t_uint i = index; i < length; ++i)
	{
		result[i] = ptrarr[i + 1];
	}
//	Memory_Free(ptrarr);
//	ptrarr = result;
}


void	PointerArray_RemoveAt_F(void** ptrarr, t_uint index, void (*delete)(void*))
{
	void**	result;
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (delete == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return;)
	length = PointerArray_Length((void const* const*)ptrarr);
	HANDLE_ERROR_SF(INDEX2LARGE, (length <= index), return;,
		"index given ("SF_UINT") is beyond end of ptrarr (length: "SF_UINT")",
		index, length)
	length -= 1;
	if (length == 0)
	{
		Memory_Free(ptrarr);
		ptrarr = NULL;
		return;
	}
//	result = (void const**)Memory_Allocate(length * sizeof(void const*));
//	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return;)
	result = ptrarr;
	for (t_uint i = index; i < length; ++i)
	{
		if (i == index)
		{
			delete(ptrarr[i]);
			result[i] = ptrarr[i + 1];
		}
		else result[i] = ptrarr[i + 1];
	}
//	Memory_Free(ptrarr);
//	ptrarr = result;
}
