
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

#ifndef __NOSTD__
	#include <stdio.h>
#else
	int	vsnprintf(char* dest, size_t n, char const* format, va_list args);
#endif

#include LIBCONFIG_HANDLE_INCLUDE



#ifndef __APPLE__

	#ifndef vscprintf
static int	vscprintf(t_char const* format, va_list args)
{
	va_list args_copy;

	va_copy(args_copy, args);
	int result = vsnprintf(NULL, 0, format, args_copy);
	va_end(args_copy);
	return (result);
}
	#endif

	#ifndef vasprintf
static int	vasprintf(t_char** a_str, t_char const* format, va_list args)
{
	int length = vscprintf(format, args);
	if (length == -1)
		return -1;
	t_char* str = (t_char*)Memory_Allocate((size_t)length + sizeof(""));
	HANDLE_ERROR(ALLOCFAILURE, (str == NULL), return (-1);)
	int result = vsnprintf(str, length + 1, format, args);
	if (result == -1)
	{
		String_Delete(&str);
		return (-1);
	}
	*a_str = str;
	return (result);
}
	#endif

#endif



t_char*	String_Format_VA(t_char const* format, va_list args)
{
	int result;
	t_char* str = NULL;

	result = vasprintf(&str, format, args);
	if (result < 0)
	{
		if (str)
			String_Delete(&str);
		return (NULL);
	}
	return (str);
}

t_char*	String_Format(t_char const* format, ...)
{
	int result;
	t_char* str = NULL;
	va_list args;

	va_start(args, format);
	result = vasprintf(&str, format, args);
	va_end(args);
	if (result < 0)
	{
		if (str)
			String_Delete(&str);
		return (NULL);
	}
	return (str);
}



t_size	String_Format_N_VA(t_char* dest, t_size max, t_char const* format, va_list args)
{
	t_size result;

	result = vsnprintf(dest, max, format, args);
	return (result);
}

t_size	String_Format_N(t_char* dest, t_size max, t_char const* format, ...)
{
	t_size result;
	va_list args;

	va_start(args, format);
	result = vsnprintf(dest, max, format, args);
	va_end(args);
	return (result);
}
