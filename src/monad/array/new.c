
#include <stdarg.h>

#include "libccc/memory.h"
#include "libccc/monad/array.h"


_GENERIC()
s_array_T	CONCAT(Array_New,T_NAME)(t_uint n, ...)
{
	va_list		args;
	T			item;
	s_array_T	result;

	result.length = n;
	result.items = NULL;
	if (n == 0)
		return (result);
	result.items = (T*)Memory_Alloc(sizeof(T) * n);
	if (result.items == NULL)
		return (result);
	va_start(args, n);
	for (t_uint i = 1; i <= n; ++i)
	{
		item = va_arg(args, T);
		result.items[i - 1] = item;
	}
	va_end(args);
	return (result);
}
