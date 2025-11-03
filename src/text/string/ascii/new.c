
#include "libccc/memory.h"
#include "libccc/text/string/ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_ascii*	StringASCII_New(t_size n)
{
	t_ascii*	result;
	t_size	i;

	result = (t_ascii*)Memory_Allocate(n + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i < n; ++i)
	{
		result[i] = '\0';
	}
	result[n] = '\0';
	return (result);
}



t_ascii*	StringASCII_New_C(t_size n, t_ascii c)
{
	t_ascii*	result;
	t_size	i;

	result = (t_ascii*)Memory_Allocate(n + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i < n; ++i)
	{
		result[i] = c;
	}
	result[n] = '\0';
	return (result);
}
