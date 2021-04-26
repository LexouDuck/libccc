
#include "libccc/monad/list.h"


_GENERIC()
s_list_T*		CONCAT(List_Map,T_NAME)(s_list_T const* list, T (*map)(T item))
{
	s_list_T*	result = NULL;
	s_list_T*	elem;

	LIBCONFIG_HANDLE_NULLPOINTER(list, NULL)
	LIBCONFIG_HANDLE_NULLPOINTER(map, NULL)
	while (list)
	{
		elem = CONCAT(List_Item,T_NAME)(map(list->item));
		if (elem == NULL)
			break;
		CONCAT(List_Append,T_NAME)(result, elem);
		list = list->next;
	}
	return (result);
}


_GENERIC()
s_list_T*		CONCAT(List_Map_I,T_NAME)(s_list_T const* list, T (*map)(T item, t_uint index))
{
	s_list_T*	result = NULL;
	s_list_T*	elem;
	t_uint	i;

	LIBCONFIG_HANDLE_NULLPOINTER(list, NULL)
	LIBCONFIG_HANDLE_NULLPOINTER(map, NULL)
	i = 0;
	while (list)
	{
		elem = CONCAT(List_Item,T_NAME)(map(list->item, i));
		if (elem == NULL)
			break;
		CONCAT(List_Append,T_NAME)(result, elem);
		list = list->next;
		++i;
	}
	return (result);
}
