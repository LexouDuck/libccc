
#include "libccc/monad/list.h"

#include LIBCONFIG_HANDLE_INCLUDE



_GENERIC()
s_list_T*	CONCAT(List_Filter,T_NAME)(s_list_T const* list, t_bool (*filter)(T item))
{
	s_list_T*	result = NULL;
	s_list_T*	elem;

	HANDLE_ERROR(NULLPOINTER, (filter == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	while (list)
	{
		if (filter(list->item))
		{
			elem = CONCAT(List_Item,T_NAME)(list->item);
			CONCAT(List_Append,T_NAME)(result, elem);
		}
		list = list->next;
	}
	return (result);
}



_GENERIC()
s_list_T*	CONCAT(List_Filter_I,T_NAME)(s_list_T const* list, t_bool (*filter)(T item, t_uint index))
{
	s_list_T*	result = NULL;
	s_list_T*	elem;
	t_uint	i;

	HANDLE_ERROR(NULLPOINTER, (filter == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	i = 0;
	while (list)
	{
		if (filter(list->item, i))
		{
			elem = CONCAT(List_Item,T_NAME)(list->item);
			CONCAT(List_Append,T_NAME)(result, elem);
		}
		list = list->next;
		++i;
	}
	return (result);
}
