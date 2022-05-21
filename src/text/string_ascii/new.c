
#include "libccc/memory.h"
#include "libccc/text/string_ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_ascii*	String_New(t_size n)
{
	t_ascii*	result;
	t_size	i;

	result = (t_ascii*)Memory_Allocate(n + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		result[i] = '\0';
		++i;
	}
	result[n] = '\0';
	return (result);
}



t_ascii*	String_New_C(t_size n, t_ascii c)
{
	t_ascii*	result;
	t_size	i;

	result = (t_ascii*)Memory_Allocate(n + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		result[i] = c;
		++i;
	}
	result[n] = '\0';
	return (result);
}
