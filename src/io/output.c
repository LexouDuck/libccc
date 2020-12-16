
/*
**	Functions used from <stdlib.h>:
**	-	int	write(int fd, char* buffer, size_t n);
*/
#include <unistd.h>
/*
**	Functions used from <stdio.h>:
**	-	int vprintf(const char *format, va_list args);
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



inline int	Output_Char(char c)
{
	return (IO_Write_Char(STDOUT, c));
}



inline int	Output_String(char const* str)
{
	return (IO_Write_String(STDOUT, str));
}



inline int	Output_Line(char const* str)
{
	return (IO_Write_Line(STDOUT, str));
}



inline int	Output_Lines(char const* *strarr)
{
	return (IO_Write_Lines(STDOUT, strarr));
}



inline int	Output_Memory(t_u8 const* ptr, t_size n, t_u8 cols)
{
	return (IO_Write_Memory(STDOUT, ptr, n, cols));
}



int			Output_Format(char const* format, ...)
{
	va_list args;
	int result;

	va_start(args, format);
	result = vprintf(format, args);
	va_end(args);
	return (result);
}
