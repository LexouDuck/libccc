
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

#include "libft_memory.h"
#include "libft_string.h"



#ifndef vasprintf
int		vscprintf(char const* format, va_list ap)
{
	va_list ap_copy;
	va_copy(ap_copy, ap);
	int result = vsnprintf(NULL, 0, format, ap_copy);
	va_end(ap_copy);
	return (result);
}

int		vasprintf(char* *a_str, char const* format, va_list ap)
{
	int len = vscprintf(format, ap);
	if (len == -1)
		return -1;
	char *str = (char*)Memory_Alloc((size_t)len + 1);
	if (!str)
		return -1;
	int result = vsnprintf(str, len + 1, format, ap);
	if (result == -1)
	{
		String_Delete(&str);
		return (-1);
	}
	*a_str = str;
	return (result);
}
#endif



char*	String_Build_VA(char const* format, va_list ap)
{
	int result;
	char* str = NULL;

	result = vasprintf(&str, format, ap);
	if (result < 0)
		return (NULL);
	return (str);
}



char*	String_Build(char const* format, ...)
{
	va_list args;
	int result;
	char* str = NULL;

	va_start(args, format);
	result = vasprintf(&str, format, args);
	va_end(args);
	if (result < 0)
		return (NULL);
	return (str);
}
