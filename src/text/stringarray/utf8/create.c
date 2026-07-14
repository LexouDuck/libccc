
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
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8**	StringArrayUTF8_Create(t_uint n, ...)
{
	va_list		args;
	t_utf8*		item;
	t_utf8**	result;
	t_uint		i;

	result = StringArrayUTF8_New(n);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (result);
	if (n == 0)
		return (result);
	va_start(args, n);
	for (i = 0; i < n; ++i)
	{
		item = va_arg(args, t_utf8*);
		result[i] = item;
	}
	va_end(args);
	return (result);
}
