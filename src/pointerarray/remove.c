
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void	PointerArray_Remove(void** ptrarr, void const* ptr)
{
	t_sint	index;

	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return;
	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER,
		"pointer given is NULL, which is used for the pointer array terminator")
		return;
	index = PointerArray_IndexOf((void const* const*)ptrarr, ptr);
	if (index == ERROR)
		return;
	PointerArray_RemoveAt(ptrarr, index);
}



void	PointerArray_Remove_F(void** ptrarr, void const* ptr, void (*del)(void*))
{
	t_sint	index;

	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is null")
		return;
	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return;
	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER,
		"pointer given is NULL, which is used for the pointer array terminator")
		return;
	index = PointerArray_IndexOf((void const* const*)ptrarr, ptr);
	if (index == ERROR)
		return;
	PointerArray_RemoveAt_F(ptrarr, index, del);
}



void	PointerArray_RemoveAll(void** ptrarr, void const* ptr)
{
	t_uint	i;
	t_uint	amount;
	t_uint	length;

	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return;
	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER,
		"pointer given is NULL, which is used for the pointer array terminator")
		return;
	length = PointerArray_Length((void const* const*)ptrarr);
	if (length == 0)
		return;
	amount = 0;
	for (i = 0; i < length; ++i)
	{
		if (ptrarr[i] == ptr)
		{
			++amount;
		}
	}
	if (length == amount)
	{
		ptrarr[0] = NULL;
		return;
	}
	amount = 0;
	for (i = 0; i < length; ++i)
	{
		if (ptrarr[i] == ptr)
		{
			++amount;
			continue;
		}
		ptrarr[i] = ptrarr[i + amount];
	}
	ptrarr[i] = NULL;
}



void	PointerArray_RemoveAll_F(void** ptrarr, void const* ptr, void (*del)(void*))
{
	t_uint	i;
	t_uint	amount;
	t_uint	length;

	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is null")
		return;
	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return;
	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER,
		"pointer given is NULL, which is used for the pointer array terminator")
		return;
	length = PointerArray_Length((void const* const*)ptrarr);
	if (ptrarr[0] == NULL)
		return;
	amount = 0;
	for (i = 0; i < length; ++i)
	{
		if (ptrarr[i] == ptr)
		{
			++amount;
		}
	}
	if (length == amount)
	{
		ptrarr[0] = NULL;
		return;
	}
	amount = 0;
	for (i = 0; i < length; ++i)
	{
		if (ptrarr[i] == ptr)
		{
			del(ptrarr[i]);
			++amount;
			continue;
		}
		ptrarr[i] = ptrarr[i + amount];
	}
	ptrarr[i] = NULL;
}
