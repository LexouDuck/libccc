
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void	PointerArray_Remove(void** ptrarr, void const* ptr)
{
	t_sint	index;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return;)
	index = PointerArray_IndexOf((void const* const*)ptrarr, ptr);
	if (index == ERROR)
		return;
	PointerArray_RemoveAt(ptrarr, index);
}



void	PointerArray_Remove_F(void** ptrarr, void const* ptr,
	void (*delete)(void*))
{
	t_sint	index;

	HANDLE_ERROR(NULLPOINTER, (delete == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return;)
	index = PointerArray_IndexOf((void const* const*)ptrarr, ptr);
	if (index == ERROR)
		return;
	PointerArray_RemoveAt_F(ptrarr, index, delete);
}



void	PointerArray_RemoveAll(void** ptrarr, void const* ptr)
{
	t_uint	i;
	t_uint	amount;
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return;)
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



void	PointerArray_RemoveAll_F(void** ptrarr, void const* ptr,
	void (*delete)(void*))
{
	t_uint	i;
	t_uint	amount;
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (delete == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (ptr    == NULL), return;)
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
			delete(ptrarr[i]);
			++amount;
			continue;
		}
		ptrarr[i] = ptrarr[i + amount];
	}
	ptrarr[i] = NULL;
}
