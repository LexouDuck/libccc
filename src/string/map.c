
#include "libccc/memory.h"
#include "libccc/string.h"

#include LIBCONFIG_HANDLE_INCLUDE



t_char*	String_Map(t_char const* str, t_char (*map)(t_char c))
{
	t_char*	result;
	t_size	length;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (map == NULL), return (NULL);)
	length = 0;
	while (str[length])
		++length;
	result = (t_char*)Memory_Alloc(length + sizeof(""));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
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

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (map == NULL), return (NULL);)
	length = 0;
	while (str[length])
		++length;
	result = (t_char*)Memory_Alloc(length + sizeof(""));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
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

	HANDLE_ERROR(NULLPOINTER, (f == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (a_str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (*a_str == NULL), return (NULL);)
	tmp = String_Map(*a_str, f);
	String_Delete(a_str);
	*a_str = tmp;
	return (tmp);
}
