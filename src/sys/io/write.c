
#include "libccc/pointer.h"

#ifndef __NOSTD__
	#include <unistd.h>
#else
	int	write(int fd, void const* buffer, size_t n);
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



inline
t_size	IO_Write_Char	(t_fd fd, t_char c)
{
	int result = 0;
	result = write(fd, &c, 1);
	HANDLE_ERROR(SYSTEM, (result < 0), return (0);)
	return (result);
}



inline
t_size	IO_Write_String	(t_fd fd, t_char const* str)
{
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
	int result = 0;
	result = write(fd, str, String_Length(str));
	HANDLE_ERROR(SYSTEM, (result < 0), return (0);)
	return (result);
}



inline
t_size	IO_Write_Data	(t_fd fd, t_u8 const* data, t_size n)
{
	HANDLE_ERROR(NULLPOINTER, (data == NULL), return (0);)
	int result = 0;
	result = write(fd, data, n);
	HANDLE_ERROR(SYSTEM, (result < 0), return (0);)
	return (result);
}



inline
t_size	IO_Write_Line	(t_fd fd, t_char const* str)
{
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
	int result = 0;
	result = write(fd, str, String_Length(str));
	HANDLE_ERROR(SYSTEM, (result < 0), return (0);)
	result = write(fd, "\n", 1);
	HANDLE_ERROR(SYSTEM, (result < 0), return (0);)
	return (result);
}



t_size	IO_Write_Lines	(t_fd fd, t_char const** strarr)
{
	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (0);)
	int result = 0;
	int i = 0;
	while (strarr[i])
	{
		result = write(fd, strarr[i], String_Length(strarr[i]));
		HANDLE_ERROR(SYSTEM, (result < 0), return (0);)
		result = write(fd, "\n", 1);
		HANDLE_ERROR(SYSTEM, (result < 0), return (0);)
		++i;
	}
	return (result);
}



t_size	IO_Write_Memory	(t_fd fd, t_u8 const* ptr, t_size n, t_u8 columns)
{
	HANDLE_ERROR(NULLPOINTER, (ptr == NULL), return (0);)
	if (n == 0 || columns == 0)
		return (0);
	int		result = 0;
	t_u8	nibble = 0;
	t_size	i = 0;
	while (i < n)
	{
		nibble = (ptr[i] & 0xF0) >> 4;
		nibble += (nibble < 10 ? '0' : 'A' - 10);
		result = write(fd, &nibble, 1);
		HANDLE_ERROR(SYSTEM, (result < 0), return (0);)
		nibble = (ptr[i] & 0x0F);
		nibble += (nibble < 10 ? '0' : 'A' - 10);
		result = write(fd, &nibble, 1);
		HANDLE_ERROR(SYSTEM, (result < 0), return (0);)
		++i;
		result = write(fd, (i % columns == 0 ? "\n" : " "), 1);
		HANDLE_ERROR(SYSTEM, (result < 0), return (0);)
	}
	return (result);
}



t_size	IO_Write_Format	(t_fd fd, t_char const* format, ...)
{
	HANDLE_ERROR(NULLPOINTER, (format == NULL), return (0);)
	int		result = 0;
	t_char* str = NULL;
	va_list args;
	va_start(args, format);
	str = String_Format_VA(format, args);
	va_end(args);
	HANDLE_ERROR(ALLOCFAILURE, (str == NULL), return (0);)
	result = write(fd, str, String_Length(str));
	HANDLE_ERROR(SYSTEM, (result < 0), return (0);)
	String_Delete(&str);
	return (result);
}
