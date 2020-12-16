
/*
**	Functions used from <stdlib.h>:
**	-	int	write(int fd, char* buffer, size_t n);
*/
#include <unistd.h>
/*
**	Functions used from <stdio.h>:
**	-	int vasprintf(char* const* result, const char* format, va_list args);
*/
#include <stdio.h>
/*
**	Functions used from <stdarg.h>:
**	-	void va_start(va_list args, last);
**	-	void va_end(va_list args);
*/
#include <stdarg.h>

#include "libft_io.h"
#include "libft_string.h"
#include "libft_convert.h"



inline int	Write_Char(int fd, char c)
{
	if (write(fd, &c, 1) < 0)
		return (ERROR);
	return (OK);
}



inline int	Write_String(int fd, const char* str)
{
	if (str == NULL)
		return (OK);
	if (write(fd, str, ft_strlen(str)) < 0)
		return (ERROR);
	return (OK);
}



inline int	Write_Line(int fd, const char* str)
{
	if (str == NULL)
		return (OK);
	if (write(fd, str, ft_strlen(str)) < 0)	return (ERROR);
	if (write(fd, "\n", 1) < 0)				return (ERROR);
	return (OK);
}



int		Write_Lines(int fd, const char** strarr)
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



int		Write_Memory(int fd, t_u8 const* ptr, t_size n, t_u8 cols)
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



int		Write_Format(t_fd fd, char const* format, ...)
{
	va_list args;
	int result;

	char * str = NULL;
	va_start(args, format);
	result = vasprintf(&str, format, args);
	va_end(args);
	if (str == NULL || result == -1) // string already freed if need be
		return (-1);
	if (write(fd, str, result) < 0)
	{
		String_Delete(&str);
		return (-1);
	}
	String_Delete(&str);
	return (result);
}
