
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



void*	StringArrayUTF8_Reduce(t_utf8 const* const* strarr,
	void* (*f)(t_utf8 const* str, void* acc))
{
	void*	accumulator = NULL;
	t_uint	length;
	t_uint	i;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArrayUTF8_Length(strarr);
	for (i = 0; i < length; ++i)
	{
		accumulator = f(strarr[i], accumulator);
	}
	return (accumulator);
}



void*	StringArrayUTF8_Reduce_I(t_utf8 const* const* strarr,
	void* (*f)(t_utf8 const* str, void* acc, t_uint index))
{
	void*	accumulator = NULL;
	t_uint	length;
	t_uint	i;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArrayUTF8_Length(strarr);
	for (i = 0; i < length; ++i)
	{
		accumulator = f(strarr[i], accumulator, i);
	}
	return (accumulator);
}



void*	StringArrayUTF8_Fold(t_utf8 const* const* strarr,
	void* (*f)(t_utf8 const* str, void* acc), void* initial)
{
	void*	accumulator = initial;
	t_uint	length;
	t_uint	i;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArrayUTF8_Length(strarr);
	for (i = 0; i < length; ++i)
	{
		accumulator = f(strarr[i], accumulator);
	}
	return (accumulator);
}



void*	StringArrayUTF8_Fold_I(t_utf8 const* const* strarr,
	void* (*f)(t_utf8 const* str, void* acc, t_uint index), void* initial)
{
	void*	accumulator = initial;
	t_uint	length;
	t_uint	i;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArrayUTF8_Length(strarr);
	for (i = 0; i < length; ++i)
	{
		accumulator = f(strarr[i], accumulator, i);
	}
	return (accumulator);
}
