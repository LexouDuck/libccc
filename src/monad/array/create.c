
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
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE

/* ++C fix for variadic arg type promotion:
#if #(typeof(T) is float)
	#define T_VA_ARG	double
#elif #(typeof(T) is char)
	#define T_VA_ARG	int
#elif #(typeof(T) is short)
	#define T_VA_ARG	int
#else
	#define T_VA_ARG	T
#endif
*/

_GENERIC()
s_array(T)*	Array_Create(T)(t_uint n, ...)
{
	T			item;
	s_array(T)*	result;

	result = Array_New(T)(n, T_NULL);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	va_list	args;
	va_start(args, n);
	for (t_uint i = 0; i < n; ++i)
	{
		item = va_arg(args, T);
		result->items[i] = item;
	}
	va_end(args);
	return (result);
}
