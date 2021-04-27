
#include "libccc/memory.h"
#include "libccc/string.h"



t_char*	String_Map(t_char const* str, t_char (*map)(t_char c))
{
	t_char*	result;
	t_size	length;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, str)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, map)
	length = 0;
	while (str[length])
		++length;
	if (!(result = (t_char*)Memory_Alloc(length + sizeof(""))))
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = map(str[i]);
		++i;
	}
	result[i] = '\0';
	return (result);
}



t_char*	String_Map_I(t_char const* str, t_char (*map)(t_char c, t_size index))
{
	t_char*	result;
	t_size	length;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, str)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, map)
	length = 0;
	while (str[length])
		++length;
	if (!(result = (t_char*)Memory_Alloc(length + sizeof(""))))
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = map(str[i], i);
		++i;
	}
	result[i] = '\0';
	return (result);
}



t_char*	String_Map_InPlace(t_char** a_str, t_char (*f)(t_char))
{
	t_char*	tmp;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, f)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, a_str)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, *a_str)
	tmp = String_Map(*a_str, f);
	String_Delete(a_str);
	*a_str = tmp;
	return (tmp);
}
