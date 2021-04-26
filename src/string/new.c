
#include "libccc/memory.h"
#include "libccc/string.h"



t_char*	String_New(t_size n)
{
	t_char*	result;
	t_size	i;

	if (!(result = (t_char*)Memory_Alloc(n + 1)))
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



t_char*	String_New_C(t_size n, t_char c)
{
	t_char*	result;
	t_size	i;

	if (!(result = (t_char*)Memory_Alloc(n + 1)))
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
