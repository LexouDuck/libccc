
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void*	StringArray_Reduce(t_char const* const* strarr,
	void* (*f)(t_char const* str, void* acc))
{
	void*	accumulator = NULL;
	t_size	length;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArray_Length(strarr);
	for (t_uint i = 0; i < length; ++i)
	{
		accumulator = f(strarr[i], accumulator);
	}
	return (accumulator);
}

void*	StringArray_Reduce_I(t_char const* const* strarr,
	void* (*f)(t_char const* str, void* acc, t_uint index))
{
	void*	accumulator = NULL;
	t_size	length;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArray_Length(strarr);
	for (t_uint i = 0; i < length; ++i)
	{
		accumulator = f(strarr[i], accumulator, i);
	}
	return (accumulator);
}



void*	StringArray_Fold(t_char const* const* strarr,
	void* (*f)(t_char const* str, void* acc), void* initial)
{
	void*	accumulator = initial;
	t_size	length;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArray_Length(strarr);
	for (t_uint i = 0; i < length; ++i)
	{
		accumulator = f(strarr[i], accumulator);
	}
	return (accumulator);
}

void*	StringArray_Fold_I(t_char const* const* strarr,
	void* (*f)(t_char const* str, void* acc, t_uint index), void* initial)
{
	void*	accumulator = initial;
	t_size	length;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArray_Length(strarr);
	for (t_uint i = 0; i < length; ++i)
	{
		accumulator = f(strarr[i], accumulator, i);
	}
	return (accumulator);
}
