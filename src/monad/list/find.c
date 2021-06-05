
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list_T const*	CONCAT(List_Find,T_NAME)(s_list_T const* list, T item)
{
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	while (list)
	{
		if (T_EQUALS(list->item, item))
			return (list);
		list = list->next;
	}
	return (NULL);
}



_GENERIC()
s_list_T const*	CONCAT(List_Find_F,T_NAME)(s_list_T const* list, t_bool (*match)(T item))
{
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	while (list)
	{
		if (match(list->item))
			return (list);
		list = list->next;
	}
	return (NULL);
}



_GENERIC()
t_sint	CONCAT(List_IndexOf,T_NAME)(s_list_T const* list, T item)
{
	t_uint	i;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (ERROR);)
	i = 0;
	while (list)
	{
		if (T_EQUALS(list->item, item))
			return (i);
		list = list->next;
		++i;
	}
	return (ERROR);
}



_GENERIC()
t_sint	CONCAT(List_IndexOf_F,T_NAME)(s_list_T const* list, t_bool (*match)(T item))
{
	t_uint	i;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (ERROR);)
	i = 0;
	while (list)
	{
		if (match(list->item))
			return (i);
		list = list->next;
		++i;
	}
	return (ERROR);
}
