
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_Replace(void* const* ptrarr, void const* old, void const* new)
{
	void**	result;
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (NULL);)
	length = PointerArray_Length(ptrarr);
	result = PointerArray_Duplicate(ptrarr);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	if (result == NULL)
		return (result);
	for (t_uint i = 0; i < length; ++i)
	{
		if (result[i] == old)
		{
			result[i] = (void*)new;
		}
	}
	return (result);
}



void**	PointerArray_ReplaceFirst(void* const* ptrarr, void const* old, void const* new, t_uint n)
{
	void**	result;
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (NULL);)
	length = PointerArray_Length(ptrarr);
	result = PointerArray_Duplicate(ptrarr);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	if (result == NULL)
		return (result);
	for (t_uint i = 0; i < length; ++i)
	{
		if (n == 0)
			return (result);
		if (result[i] == old)
		{
			result[i] = (void*)new;
			n -= 1;
		}
	}
	return (result);
}



void**	PointerArray_ReplaceLast(void* const* ptrarr, void const* old, void const* new, t_uint n)
{
	void**	result;
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (NULL);)
	length = PointerArray_Length(ptrarr);
	result = PointerArray_Duplicate(ptrarr);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	if (result == NULL)
		return (result);
	t_uint i = length;
	while (i--)
	{
		if (n == 0)
			return (result);
		if (result[i] == old)
		{
			result[i] = (void*)new;
			n -= 1;
		}
	}
	return (result);
}
