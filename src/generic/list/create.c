
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
#include "libccc/generic/list.h"

#include LIBCONFIG_ERROR_INCLUDE

/* ++C fix for variadic arg type promotion:
#if (#typeof(T) is #float)
	#define T_VA_ARG	double
#elif (#typeof(T) is #char)
	#define T_VA_ARG	int
#elif (#typeof(T) is #short)
	#define T_VA_ARG	int
#else
	#define T_VA_ARG	T
#endif
*/

_GENERIC()
s_list(T)*	List_Create(T)(t_uint n, ...)
{
	va_list		args;
	T			item;
	s_list(T)*	result = NULL;
	s_list(T)*	elem;
	s_list(T)*	newitem;

	if CCCERROR((n == 0), ERROR_LENGTH2SMALL, NULL)
		return (NULL);
	va_start(args, n);
	for (t_uint i = 0; i < n; ++i)
	{
		item = va_arg(args, T);
		newitem = (s_list(T)*)Memory_Allocate(sizeof(s_list(T)));
		if CCCERROR((newitem == NULL), ERROR_ALLOCFAILURE, NULL)
			break;
#if LIBCONFIG_LIST_DOUBLYLINKED
		newitem->prev = NULL;
#endif
		newitem->next = NULL;
		newitem->item = item;
		if (i == 0)
		{
			elem = newitem;
			result = newitem;
		}
		else
		{
#if LIBCONFIG_LIST_DOUBLYLINKED
			newitem->prev = elem;
#endif
			elem->next = newitem;
			elem = elem->next;
		}
	}
	va_end(args);
	return (result);
}
