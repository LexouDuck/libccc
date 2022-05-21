
#include "libccc/memory.h"
#include "libccc/text/stringascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_ascii*	String_Map(t_ascii const* str, t_ascii (*map)(t_ascii c))
{
	t_ascii*	result;
	t_size	length;
	t_size	i;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string address given is NULL")
		return (NULL);
	length = 0;
	while (str[length])
		++length;
	result = (t_ascii*)Memory_Allocate(length + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
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



t_ascii*	String_Map_I(t_ascii const* str, t_ascii (*map)(t_ascii c, t_size index))
{
	t_ascii*	result;
	t_size	length;
	t_size	i;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string address given is NULL")
		return (NULL);
	length = 0;
	while (str[length])
		++length;
	result = (t_ascii*)Memory_Allocate(length + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
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



t_ascii*	String_Map_InPlace(t_ascii** a_str, t_ascii (*map)(t_ascii))
{
	t_ascii*	tmp;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((a_str == NULL), ERROR_NULLPOINTER, "string address given is NULL")
		return (NULL);
//	if CCCERROR((*a_str == NULL), ERROR_NULLPOINTER, NULL)
//		return (NULL);
	tmp = String_Map(*a_str, map);
	String_Delete(a_str);
	*a_str = tmp;
	return (tmp);
}
