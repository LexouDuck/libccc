
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void	PointerArray_Iterate(void** ptrarr,
	void* (*f)(void* ptr))
{
	t_uint	i;
	void*	tmp;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return;
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

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return;
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
