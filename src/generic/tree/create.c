
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
#include "libccc/generic/tree.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_tree(T)*	Tree_Create(T)(T value, t_size n, ...)
{
	s_tree(T)*	result;

	result = Tree_New(T)(value);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	va_list	args;
	va_start(args, n);
	for (t_size i = 0; i < n; ++i)
	{
		if (Tree_Append(T)(result, Tree_Item(T)(va_arg(args, T))) == NULL)
		{
			va_end(args);
			Tree_Free(T)(result);
			return (NULL);
		}
	}
	va_end(args);
	return (result);
}
