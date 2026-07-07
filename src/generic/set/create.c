
#include <stdarg.h>

#include "libccc/memory.h"
#include "libccc/generic/set.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_set(T)*	Set_Create(T)(t_uint n, ...)
{
	s_set(T)*	result;
	T	item;

	result = Set_New(T)();
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	va_list	args;
	va_start(args, n);
	for (t_uint i = 0; i < n; ++i)
	{
		item = va_arg(args, T);
		// using Set_Add() ensures value unicity (any duplicate values given are simply ignored)
		if (Set_Add(T)(result, item) == NULL)
		{
			va_end(args);
			Set_Free(T)(result);
			return (NULL);
		}
	}
	va_end(args);
	return (result);
}
