
#ifndef __NOSTD__
	#include <stdarg.h>
#else
	typedef __builtin_va_list va_list;
	#define va_start(v,l)	__builtin_va_start(v,l)
	#define va_end(v)		__builtin_va_end(v)
	#define va_arg(v,l)		__builtin_va_arg(v,l)
	#define va_copy(d,s)	__builtin_va_copy(d,s)
#endif

#include "libccc/memory.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_dict(T)*	Dict_Create(T)(t_uint n, ...)
{
	s_dict(T)*	result;
	t_char*	key;
	T		value;

	result = Dict_New(T)();
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	va_list	args;
	va_start(args, n);
	for (t_uint i = 0; i < n; ++i)
	{
		key = va_arg(args, t_char*);
		value = va_arg(args, T);
		// using Dict_Set() ensures key unicity (a repeated key keeps only the last value given)
		if (Dict_Set(T)(result, key, value) == NULL)
		{
			va_end(args);
			Dict_Free(T)(result);
			return (NULL);
		}
	}
	va_end(args);
	return (result);
}
