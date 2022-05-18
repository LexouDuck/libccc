
#include "libccc/memory.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



t_ascii*	String_Map(t_ascii const* str, t_ascii (*map)(t_ascii c))
{
	t_ascii*	result;
	t_size	length;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (map == NULL), return (NULL);)
	length = 0;
	while (str[length])
		++length;
	result = (t_ascii*)Memory_Allocate(length + sizeof(""));
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



t_ascii*	String_Map_I(t_ascii const* str, t_ascii (*map)(t_ascii c, t_size index))
{
	t_ascii*	result;
	t_size	length;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (map == NULL), return (NULL);)
	length = 0;
	while (str[length])
		++length;
	result = (t_ascii*)Memory_Allocate(length + sizeof(""));
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



t_ascii*	String_Map_InPlace(t_ascii** a_str, t_ascii (*f)(t_ascii))
{
	t_ascii*	tmp;

	HANDLE_ERROR(NULLPOINTER, (f == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (a_str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (*a_str == NULL), return (NULL);)
	tmp = String_Map(*a_str, f);
	String_Delete(a_str);
	*a_str = tmp;
	return (tmp);
}
