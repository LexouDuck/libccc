
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



inline
void	PointerArray_Free(void** ptrarr)
{
	for (t_uint i = 0; ptrarr[i]; ++i)
	{
		String_Free(ptrarr[i]);
	}
	Memory_Free(ptrarr);
}



void	PointerArray_Delete(void** *a_ptrarr)
{
	HANDLE_ERROR(NULLPOINTER, (a_ptrarr == NULL), return;)
	if (*a_ptrarr)
	{
		for (t_uint i = 0; (*a_ptrarr)[i]; ++i)
		{
			String_Free((*a_ptrarr)[i]);
		}
		Memory_Delete((void**)a_ptrarr);
	}
}
