
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

#include "libccc/memory.h"
#include "libccc/string.h"



#ifndef __APPLE__

	#ifndef vscprintf
static int	vscprintf(char const* format, va_list args)
{
	va_list args_copy;

	va_copy(args_copy, args);
	int result = vsnprintf(NULL, 0, format, args_copy);
	va_end(args_copy);
	return (result);
}
	#endif

	#ifndef vasprintf
static int	vasprintf(char* *a_str, char const* format, va_list args)
{
	int length = vscprintf(format, args);
	if (length == -1)
		return -1;
	char *str = (char*)Memory_Alloc((size_t)length + 1);
	if (!str)
		return -1;
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



char*	String_Format_VA(char const* format, va_list args)
{
	int result;
	char* str = NULL;

	result = vasprintf(&str, format, args);
	if (result < 0)
	{
		if (str)
			String_Delete(&str);
		return (NULL);
	}
	return (str);
}

char*	String_Format(char const* format, ...)
{
	int result;
	char* str = NULL;
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



t_size	String_Format_N_VA(char* dest, t_size max, char const* format, va_list args)
{
	t_size result;

	result = vsnprintf(dest, max, format, args);
	return (result);
}

t_size	String_Format_N(char* dest, t_size max, char const* format, ...)
{
	t_size result;
	va_list args;

	va_start(args, format);
	result = vsnprintf(dest, max, format, args);
	va_end(args);
	return (result);
}
