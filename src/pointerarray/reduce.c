
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void*	PointerArray_Reduce(void const* const* ptrarr,
	void* (*f)(void const* ptr, void* acc))
{
	void*	accumulator = NULL;
	t_size	length;

	HANDLE_ERROR(NULLPOINTER, (f == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (NULL);)
	length = PointerArray_Length(ptrarr);
	for (t_uint i = 0; i < length; ++i)
	{
		accumulator = f(ptrarr[i], accumulator);
	}
	return (accumulator);
}

void*	PointerArray_Reduce_I(void const* const* ptrarr,
	void* (*f)(void const* ptr, void* acc, t_uint index))
{
	void*	accumulator = NULL;
	t_size	length;

	HANDLE_ERROR(NULLPOINTER, (f == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (NULL);)
	length = PointerArray_Length(ptrarr);
	for (t_uint i = 0; i < length; ++i)
	{
		accumulator = f(ptrarr[i], accumulator, i);
	}
	return (accumulator);
}



void*	PointerArray_Fold(void const* const* ptrarr,
	void* (*f)(void const* ptr, void* acc), void* initial)
{
	void*	accumulator = initial;
	t_size	length;

	HANDLE_ERROR(NULLPOINTER, (f == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (NULL);)
	length = PointerArray_Length(ptrarr);
	for (t_uint i = 0; i < length; ++i)
	{
		accumulator = f(ptrarr[i], accumulator);
	}
	return (accumulator);
}

void*	PointerArray_Fold_I(void const* const* ptrarr,
	void* (*f)(void const* ptr, void* acc, t_uint index), void* initial)
{
	void*	accumulator = initial;
	t_size	length;

	HANDLE_ERROR(NULLPOINTER, (f == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (NULL);)
	length = PointerArray_Length(ptrarr);
	for (t_uint i = 0; i < length; ++i)
	{
		accumulator = f(ptrarr[i], accumulator, i);
	}
	return (accumulator);
}
