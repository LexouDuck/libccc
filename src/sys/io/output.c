
#ifndef __NOSTD__
	#include <unistd.h>
#else
	int	write(int fd, char const* buffer, size_t n);
#endif
#ifndef __NOSTD__
	#include <errno.h>
#else
	#undef	errno
	#define errno	(*_errno())
#endif
#ifndef __NOSTD__
	#include <stdarg.h>
#else
	typedef __gnuc_va_list va_list;
	#define va_start(v,l)	__builtin_va_start(v,l)
	#define va_end(v)		__builtin_va_end(v)
	#define va_arg(v,l)		__builtin_va_arg(v,l)
	#define va_copy(d,s)	__builtin_va_copy(d,s)
#endif

#include "libccc/sys/io.h"
#include "libccc/string.h"



inline t_io_error	IO_Output_Char(char c)
{
	return (IO_Write_Char(STDOUT, c));
}



inline t_io_error	IO_Output_String(t_char const* str)
{
	return (IO_Write_String(STDOUT, str));
}



inline t_io_error	IO_Output_Line(t_char const* str)
{
	return (IO_Write_Line(STDOUT, str));
}



inline t_io_error	IO_Output_Lines(t_char const** strarr)
{
	return (IO_Write_Lines(STDOUT, strarr));
}



inline t_io_error	IO_Output_Memory(t_u8 const* ptr, t_size n, t_u8 cols)
{
	return (IO_Write_Memory(STDOUT, ptr, n, cols));
}



t_io_error			IO_Output_Format(t_char const* format, ...)
{
	LIBCONFIG_HANDLE_NULLPOINTER(OK, format)
	int result;
	t_char* str;
	va_list args;
	va_start(args, format);
	str = String_Format_VA(format, args);
	va_end(args);
	if (str == NULL) // string already freed if need be
		return (ERROR);
	result = write(STDOUT, str, String_Length(str));
	String_Delete(&str);
	return (result ? errno : OK);
}
