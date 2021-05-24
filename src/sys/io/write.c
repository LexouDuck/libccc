
#include "libccc/pointer.h"

#ifndef __NOSTD__
	#include <unistd.h>
#else
	int	write(int fd, void const* buffer, size_t n);
#endif
#ifndef __NOSTD__
	#include <errno.h>
#else
	#ifndef	errno
	#define errno	(*_errno())
	extern	int*	_errno(void);
	#endif
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

#include LIBCONFIG_HANDLE_INCLUDE



inline
e_stderror	IO_Write_Char(int fd, char c)
{
	int result;
	if ((result = write(fd, &c, 1)) < 0)
		return (errno);
	return (result ? errno : OK);
}



inline
e_stderror	IO_Write_String(int fd, const t_char* str)
{
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (OK);)
	int result;
	if ((result = write(fd, str, String_Length(str))) < 0)
		return (errno);
	return (OK);
}



inline
e_stderror	IO_Write_Line(int fd, const t_char* str)
{
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (OK);)
	int result;
	if ((result = write(fd, str, String_Length(str))) < 0)
		return (errno);
	if ((result = write(fd, "\n", 1)) < 0)
		return (errno);
	return (OK);
}



e_stderror	IO_Write_Lines(int fd, const t_char** strarr)
{
	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (OK);)
	int result;
	int i = 0;
	while (strarr[i])
	{
		if ((result = write(fd, strarr[i], String_Length(strarr[i]))) < 0)
			return (errno);
		if ((result = write(fd, "\n", 1)) < 0)
			return (errno);
		++i;
	}
	return (OK);
}



e_stderror	IO_Write_Memory(int fd, t_u8 const* ptr, t_size n, t_u8 columns)
{
	HANDLE_ERROR(NULLPOINTER, (ptr == NULL), return (OK);)
	if (n == 0 || columns == 0)
		return (OK);
	int result;
	t_u8	nibble;
	t_size	i = 0;
	while (i < n)
	{
		nibble = (ptr[i] & 0xF0) >> 4;
		nibble += (nibble < 10 ? '0' : 'A' - 10);
		if ((result = write(fd, &nibble, 1)) < 0)
			return (errno);
		nibble = (ptr[i] & 0x0F);
		nibble += (nibble < 10 ? '0' : 'A' - 10);
		if ((result = write(fd, &nibble, 1)) < 0)
			return (errno);
		++i;
		if ((result = write(fd, (i % columns == 0 ? "\n" : " "), 1)) < 0)
			return (errno);
	}
	return (OK);
}



e_stderror	IO_Write_Format(t_fd fd, t_char const* format, ...)
{
	HANDLE_ERROR(NULLPOINTER, (format == NULL), return (OK);)
	int result;
	t_char* str;
	va_list args;
	va_start(args, format);
	str = String_Format_VA(format, args);
	va_end(args);
	if (str == NULL) // string already freed if need be
		return (ERROR);
	result = write(fd, str, String_Length(str));
	String_Delete(&str);
	return (result ? errno : OK);
}
