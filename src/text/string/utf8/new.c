
#include "libccc/memory.h"
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8*	StringUTF8_New(t_size n)
{
	t_utf8*	result;
	t_size	i;

	result = (t_utf8*)Memory_Allocate(n + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i < n; ++i)
	{
		result[i] = '\0';
	}
	result[n] = '\0';
	return (result);
}



t_utf8*	StringUTF8_New_C(t_size n, t_utf8 c)
{
	t_utf8*	result;
	t_size	i;

	result = (t_utf8*)Memory_Allocate(n + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i < n; ++i)
	{
		result[i] = c;
	}
	result[n] = '\0';
	return (result);
}
