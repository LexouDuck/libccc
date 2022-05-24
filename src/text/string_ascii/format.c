
#include "libccc/memory.h"
#include "libccc/text/string_ascii.h"
#include "libccc/text/format.h"

#ifndef __NOSTD__
	#include <stdio.h>
#else
	int	vsnprintf(char* dest, size_t n, char const* format, va_list args);
#endif

#ifndef __NOSTD__
	#include <stdarg.h>
#else
	typedef __builtin_va_list va_list;
	#define va_start(v,l) __builtin_va_start(v,l)
	#define va_end(v)     __builtin_va_end(v)
	#define va_arg(v,l)   __builtin_va_arg(v,l)
	#define va_copy(d,s)  __builtin_va_copy(d,s)
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if (defined(__NOSTD__) || \
	!defined(__GNUC__) || \
	(defined(__GNUC__) && !defined(_GNU_SOURCE) && !defined(_BSD_SOURCE)))

#ifdef __NOSTD__
// MSVC implements this as `_vscprintf`, thus we just 'symlink' it here
#elif __MSVC__
#define vscprintf _vscprintf
// MacOSX implements this one and exposes it by default
#elif __APPLE__
#define vscprintf vscprintf
#endif

#ifndef 	vscprintf
static	int	vscprintf(t_ascii const* format, va_list args)
{
	va_list args_copy;

	va_copy(args_copy, args);
	int result = vsnprintf(NULL, 0, format, args_copy);
	va_end(args_copy);
	return (result);
}
#endif

#ifdef __NOSTD__
// MacOSX implements this one and exposes it by default
#elif __APPLE__
#define vasprintf vasprintf
#endif

#ifndef 	vasprintf
static	int	vasprintf(t_ascii** a_str, t_ascii const* format, va_list args)
{
	int length = vscprintf(format, args);
	if (length == -1)
		return -1;
	t_ascii* str = (t_ascii*)Memory_Allocate((size_t)length + sizeof(""));
	if CCCERROR((str == NULL), ERROR_ALLOCFAILURE, NULL)
		return (-1);
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



t_ascii*	String_Format_VA(t_ascii const* format, va_list args)
{
	int result;
	t_ascii* str = NULL;

	result = vasprintf(&str, format, args);
	if (result < 0)
	{
		if (str)
			String_Delete(&str);
		return (NULL);
	}
	return (str);
}

t_ascii*	String_Format(t_ascii const* format, ...)
{
	int result;
	t_ascii* str = NULL;
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



t_size	String_Format_N_VA(t_ascii* dest, t_size max, t_ascii const* format, va_list args)
{
	t_size result;

	result = vsnprintf(dest, max, format, args);
	return (result);
}

t_size	String_Format_N(t_ascii* dest, t_size max, t_ascii const* format, ...)
{
	t_size result;
	va_list args;

	va_start(args, format);
	result = vsnprintf(dest, max, format, args);
	va_end(args);
	return (result);
}
