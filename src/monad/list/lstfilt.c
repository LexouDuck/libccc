
#include "libccc/monad/list.h"



s_list_T*	CONCAT(List_T,_Filter)(s_list_T const* list, t_bool (*filter)(T item))
{
	s_list_T*	result = NULL;
	s_list_T*	elem;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL || filter == NULL)
		return (NULL);
#endif
	while (list)
	{
		if (filter(list->item))
		{
			elem = CONCAT(List_T,_Item)(list->item);
			CONCAT(List_T,_Append)(result, elem);
		}
		list = list->next;
	}
	return (result);
}



s_list_T*	CONCAT(List_T,_Filter_I)(s_list_T const* list, t_bool (*filter)(T item, t_uint index))
{
	s_list_T*	result = NULL;
	s_list_T*	elem;
	t_uint	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL || filter == NULL)
		return (NULL);
#endif
	i = 0;
	while (list)
	{
		if (filter(list->item, i))
		{
			elem = CONCAT(List_T,_Item)(list->item);
			CONCAT(List_T,_Append)(result, elem);
		}
		list = list->next;
		++i;
	}
	return (result);
}
