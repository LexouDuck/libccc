
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list_T*	CONCAT(List_Filter,T_NAME)(s_list_T const* list, t_bool (*filter)(T item))
{
	s_list_T*	result = NULL;
	s_list_T*	item;

	HANDLE_ERROR(NULLPOINTER, (filter == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	while (list)
	{
		if (filter(list->item))
		{
			item = CONCAT(List_Item,T_NAME)(list->item);
			CONCAT(List_Append,T_NAME)(result, item);
		}
		list = list->next;
	}
	return (result);
}



_GENERIC()
s_list_T*	CONCAT(List_Filter_I,T_NAME)(s_list_T const* list, t_bool (*filter)(T item, t_uint index))
{
	s_list_T*	result = NULL;
	s_list_T*	item;
	t_uint	i;

	HANDLE_ERROR(NULLPOINTER, (filter == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	i = 0;
	while (list)
	{
		if (filter(list->item, i))
		{
			item = CONCAT(List_Item,T_NAME)(list->item);
			CONCAT(List_Append,T_NAME)(result, item);
		}
		list = list->next;
		++i;
	}
	return (result);
}
