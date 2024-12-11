
#include "libccc.h"
#include "libccc/pointer.h"

#ifndef __NOSTD__
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/unistd.h"
	#else
	#include <unistd.h>
	#endif
#else
	int	write(int fd, char const* buffer, size_t n);
#endif
#ifndef __NOSTD__
	#include <stdarg.h>
#else
	typedef __builtin_va_list va_list;
	#define va_start(v,l)	__builtin_va_start(v,l)
	#define va_end(v)		__builtin_va_end(v)
	#define va_arg(v,l)		__builtin_va_arg(v,l)
	#define va_copy(d,s)	__builtin_va_copy(d,s)
#endif

#include "libccc/sys/io.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



extern inline
t_size	IO_Output_Char(t_char c)
{
	return (IO_Write_Char(STDOUT, c));
}



extern inline
t_size	IO_Output_String(t_char const* str)
{
	return (IO_Write_String(STDOUT, str));
}



extern inline
t_size	IO_Output_Line(t_char const* str)
{
	return (IO_Write_Line(STDOUT, str));
}



extern inline
t_size	IO_Output_Lines(t_char const** strarr)
{
	return (IO_Write_Lines(STDOUT, strarr));
}



extern inline
t_size	IO_Output_Memory(t_u8 const* ptr, t_size n, t_u8 cols)
{
	return (IO_Write_Memory(STDOUT, ptr, n, cols));
}



t_size	IO_Output_Format(t_char const* format, ...)
{
	if CCCERROR((format == NULL), ERROR_NULLPOINTER, "format string given is NULL")
		return (0);
	int result;
	t_char* str;
	va_list args;
	va_start(args, format);
	str = String_Format_VA(format, args);
	va_end(args);
	if CCCERROR((str == NULL), ERROR_ALLOCFAILURE, NULL) return (0);
	result = write(STDOUT, str, String_Length(str));
	String_Delete(&str);
	if CCCERROR((result < 0), ERROR_SYSTEM, 
		"call to write() failed on fd=stdout, for formatted string \"%s\"", format)
		return (0);
	return (0);
}
