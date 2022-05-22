
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
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArray_Create(t_uint n, ...)
{
	va_list		args;
	t_char*		item;
	t_char**	result;

	result = (t_char**)StringArray_New(n);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (result);
	if (n == 0)
		return (result);
	va_start(args, n);
	for (t_uint i = 0; i < n; ++i)
	{
		item = va_arg(args, t_char*);
		result[i] = item;
	}
	va_end(args);
	return (result);
}
