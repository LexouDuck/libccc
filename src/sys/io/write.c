
/*
**	Functions used from <stdlib.h>:
**	-	t_io_error	write(int fd, char* buffer, size_t n);
*/
#include <unistd.h>
/*
**	Functions used from <stdarg.h>:
**	-	void va_start(va_list args, last);
**	-	void va_end(va_list args);
*/
#include <stdarg.h>
#include <errno.h>

#include "libccc/sys/io.h"
#include "libccc/string.h"



inline t_io_error	IO_Write_Char(int fd, char c)
{
	int result;
	if ((result = write(fd, &c, 1)) < 0)
		return (errno);
	return (result ? errno : OK);
}



inline t_io_error	IO_Write_String(int fd, const char* str)
{
	LIBCONFIG_HANDLE_NULLPOINTER(OK, str)
	int result;
	if ((result = write(fd, str, String_Length(str))) < 0)
		return (errno);
	return (OK);
}



inline t_io_error	IO_Write_Line(int fd, const char* str)
{
	LIBCONFIG_HANDLE_NULLPOINTER(OK, str)
	int result;
	if ((result = write(fd, str, String_Length(str))) < 0)
		return (errno);
	if ((result = write(fd, "\n", 1)) < 0)
		return (errno);
	return (OK);
}



t_io_error		IO_Write_Lines(int fd, const char** strarr)
{
	LIBCONFIG_HANDLE_NULLPOINTER(OK, strarr)
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



t_io_error		IO_Write_Memory(int fd, t_u8 const* ptr, t_size n, t_u8 columns)
{
	LIBCONFIG_HANDLE_NULLPOINTER(OK, ptr)
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



t_io_error		IO_Write_Format(t_fd fd, char const* format, ...)
{
	LIBCONFIG_HANDLE_NULLPOINTER(OK, format)
	int result;
	char* str;
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
