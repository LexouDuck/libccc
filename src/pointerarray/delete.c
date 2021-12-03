
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void	PointerArray_Free(void** ptrarr)
{
	if (ptrarr == NULL)
		return;
	for (t_uint i = 0; ptrarr[i]; ++i)
	{
		Memory_Free(ptrarr[i]);
	}
	Memory_Free(ptrarr);
}



void	PointerArray_Free_F(void** ptrarr, void (*delete)(void* ptr))
{
	if (ptrarr == NULL)
		return;
	for (t_uint i = 0; ptrarr[i]; ++i)
	{
		delete(ptrarr[i]);
	}
	Memory_Free(ptrarr);
}



void	PointerArray_Delete(void** *a_ptrarr)
{
	HANDLE_ERROR(NULLPOINTER, (a_ptrarr == NULL), return;)
	if (*a_ptrarr == NULL)
		return;
	for (t_uint i = 0; (*a_ptrarr)[i]; ++i)
	{
		Memory_Free((*a_ptrarr)[i]);
	}
	Memory_Delete((void**)a_ptrarr);
}



void	PointerArray_Delete_F(void** *a_ptrarr, void (*delete)(void* ptr))
{
	HANDLE_ERROR(NULLPOINTER, (a_ptrarr == NULL), return;)
	if (*a_ptrarr == NULL)
		return;
	for (t_uint i = 0; (*a_ptrarr)[i]; ++i)
	{
		delete((*a_ptrarr)[i]);
	}
	Memory_Delete((void**)a_ptrarr);
}
