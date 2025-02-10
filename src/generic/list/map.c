
#include "libccc/generic/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*		List_Map(T)(s_list(T) const* list, T (*map)(T item))
{
	s_list(T)*	result = NULL;
	s_list(T)*	elem;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (NULL);
	while (list)
	{
		elem = List_Item(T)(map(list->item));
		if (elem == NULL)
			break;
		List_Append(T)(result, elem);
		list = list->next;
	}
	return (result);
}



_GENERIC()
s_list(T)*		List_Map_I(T)(s_list(T) const* list, T (*map)(T item, t_uint index))
{
	s_list(T)*	result = NULL;
	s_list(T)*	elem;
	t_uint	i;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (NULL);
	i = 0;
	while (list)
	{
		elem = List_Item(T)(map(list->item, i));
		if (elem == NULL)
			break;
		List_Append(T)(result, elem);
		list = list->next;
		++i;
	}
	return (result);
}
