
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

#include "libft_string.h"



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
