
#include "libccc/monad/list.h"


_GENERIC()
s_list_T*		CONCAT(List_T,_Map)(s_list_T const* list, T (*map)(T item))
{
	s_list_T*	result = NULL;
	s_list_T*	elem;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL || map == NULL)
		return (NULL);
#endif
	while (list)
	{
		elem = CONCAT(List_T,_Item)(map(list->item));
		if (elem == NULL)
			break;
		CONCAT(List_T,_Append)(result, elem);
		list = list->next;
	}
	return (result);
}


_GENERIC()
s_list_T*		CONCAT(List_T,_Map_I)(s_list_T const* list, T (*map)(T item, t_uint index))
{
	s_list_T*	result = NULL;
	s_list_T*	elem;
	t_uint	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL || map == NULL)
		return (NULL);
#endif
	i = 0;
	while (list)
	{
		elem = CONCAT(List_T,_Item)(map(list->item, i));
		if (elem == NULL)
			break;
		CONCAT(List_T,_Append)(result, elem);
		list = list->next;
		++i;
	}
	return (result);
}
