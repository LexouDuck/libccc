
/*
**	Functions used from <stdlib.h>:
**	-	int	write(int fd, char* buffer, size_t n);
*/
#include <unistd.h>
/*
**	Functions used from <stdarg.h>:
**	-	void va_start(va_list args, last);
**	-	void va_end(va_list args);
*/
#include <stdarg.h>

#include "libft_io.h"
#include "libft_string.h"
#include "libft_convert.h"



inline int	IO_Write_Char(int fd, char c)
{
	if (write(fd, &c, 1) < 0)
		return (ERROR);
	return (OK);
}



inline int	IO_Write_String(int fd, const char* str)
{
	if (str == NULL)
		return (OK);
	if (write(fd, str, ft_strlen(str)) < 0)
		return (ERROR);
	return (OK);
}



inline int	IO_Write_Line(int fd, const char* str)
{
	if (str == NULL)
		return (OK);
	if (write(fd, str, ft_strlen(str)) < 0)	return (ERROR);
	if (write(fd, "\n", 1) < 0)				return (ERROR);
	return (OK);
}



int		IO_Write_Lines(int fd, const char** strarr)
{
	if (strarr == NULL)
		return (OK);
	int i = 0;
	while (strarr[i])
	{
		if (write(fd, strarr[i], ft_strlen(strarr[i])) < 0)	return (ERROR);
		if (write(fd, "\n", 1) < 0)							return (ERROR);
		++i;
	}
	return (OK);
}



int		IO_Write_Memory(int fd, t_u8 const* ptr, t_size n, t_u8 cols)
{
	if (ptr == NULL || n == 0 || cols == 0)
		return (OK);
	t_u8	nibble;
	t_size	i = 0;
	while (i < n)
	{
		nibble = (ptr[i] & 0xF0) >> 4;
		nibble += (nibble < 10 ? '0' : 'A' - 10);
		if (write(fd, &nibble, 1) < 0)	return (ERROR);
		nibble = (ptr[i] & 0x0F);
		nibble += (nibble < 10 ? '0' : 'A' - 10);
		if (write(fd, &nibble, 1) < 0)	return (ERROR);
		++i;
		if (write(fd, (i % cols == 0 ? "\n" : " "), 1) < 0)	return (ERROR);
	}
	return (OK);
}



int		IO_Write_Format(t_fd fd, char const* format, ...)
{
	int result;
	char* str;
	va_list args;

	va_start(args, format);
	str = String_Format_VA(format, args);
	va_end(args);
	if (str == NULL) // string already freed if need be
		return (-1);
	result = write(fd, str, String_Length(str));
	String_Delete(&str);
	return (result);
}
