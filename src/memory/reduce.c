
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



void*	Memory_Reduce(void const* ptr, t_size n,
	void* (*f)(t_u8 byte, void* acc))
{
	void*	accumulator = NULL;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, "pointer given is NULL")
		return (NULL);
	for (t_uint i = 0; i < n; ++i)
	{
		accumulator = f(((t_u8*)ptr)[i], accumulator);
	}
	return (accumulator);
}

void*	Memory_Reduce_I(void const* ptr, t_size n,
	void* (*f)(t_u8 byte, void* acc, t_uint index))
{
	void*	accumulator = NULL;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, "pointer given is NULL")
		return (NULL);
	for (t_uint i = 0; i < n; ++i)
	{
		accumulator = f(((t_u8*)ptr)[i], accumulator, i);
	}
	return (accumulator);
}



void*	Memory_Fold(void const* ptr, t_size n,
	void* (*f)(t_u8 byte, void* acc), void* initial)
{
	void*	accumulator = initial;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, "pointer given is NULL")
		return (NULL);
	for (t_uint i = 0; i < n; ++i)
	{
		accumulator = f(((t_u8*)ptr)[i], accumulator);
	}
	return (accumulator);
}

void*	Memory_Fold_I(void const* ptr, t_size n,
	void* (*f)(t_u8 byte, void* acc, t_uint index), void* initial)
{
	void*	accumulator = initial;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, "pointer given is NULL")
		return (NULL);
	for (t_uint i = 0; i < n; ++i)
	{
		accumulator = f(((t_u8*)ptr)[i], accumulator, i);
	}
	return (accumulator);
}
