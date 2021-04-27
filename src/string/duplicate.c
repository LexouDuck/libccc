
#include "libccc/memory.h"
#include "libccc/string.h"



t_char*	String_Duplicate(t_char const* str)
{
	t_char*	result;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, str)
	i = 0;
	while (str[i])
		++i;
	if (!(result = String_New(i)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}



t_char*	String_Duplicate_C(t_char const* str, t_char const c)
{
	t_char*	result;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, str)
	i = 0;
	while (str[i] && str[i] != c)
		++i;
	if (!(result = String_New(i)))
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}



t_char*	String_Duplicate_N(t_char const* str, t_size n)
{
	t_char*	result;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, str)
	i = 0;
	while (str[i] && i < n)
		++i;
	if (!(result = String_New(i)))
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}
