
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void	PointerArray_Iterate(void** ptrarr,
	void* (*f)(void* ptr))
{
	t_uint	i;
	void*	tmp;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (f == NULL), return;)
	i = 0;
	while (ptrarr[i])
	{
		tmp = f(ptrarr[i]);
		if (tmp != ptrarr[i])
			Memory_Delete(ptrarr + i);
		ptrarr[i] = tmp;
		++i;
	}
}



void	PointerArray_Iterate_I(void** ptrarr,
	void* (*f)(void* ptr, t_uint index))
{
	t_uint	i;
	void*	tmp;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (f == NULL), return;)
	i = 0;
	while (ptrarr[i])
	{
		tmp = f(ptrarr[i], i);
		if (tmp != ptrarr[i])
			Memory_Delete(ptrarr + i);
		ptrarr[i] = tmp;
		++i;
	}
}
