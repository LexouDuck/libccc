
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



void	PointerArray_Free_F(void** ptrarr, void (*del)(void* ptr))
{
	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if (ptrarr == NULL)
		return;
	for (t_uint i = 0; ptrarr[i]; ++i)
	{
		del(ptrarr[i]);
	}
	Memory_Free(ptrarr);
}



void	PointerArray_Delete(void** *a_ptrarr)
{
	if CCCERROR((a_ptrarr == NULL), ERROR_NULLPOINTER, "pointer array address given is NULL")
		return;
	if (*a_ptrarr == NULL)
		return;
	for (t_uint i = 0; (*a_ptrarr)[i]; ++i)
	{
		Memory_Free((*a_ptrarr)[i]);
	}
	Memory_Delete((void**)a_ptrarr);
}



void	PointerArray_Delete_F(void** *a_ptrarr, void (*del)(void* ptr))
{
	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if CCCERROR((a_ptrarr == NULL), ERROR_NULLPOINTER, "pointer array address given is NULL")
		return;
	if (*a_ptrarr == NULL)
		return;
	for (t_uint i = 0; (*a_ptrarr)[i]; ++i)
	{
		del((*a_ptrarr)[i]);
	}
	Memory_Delete((void**)a_ptrarr);
}
