
#include "libccc/monad/list.h"



s_list_T const*	CONCAT(List_T,_Find)(s_list_T const* list, T item)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
	while (list)
	{
		if (T_EQUALS(list->item, item))
			return (list);
		list = list->next;
	}
	return (NULL);
}



s_list_T const*	CONCAT(List_T,_Find_F)(s_list_T const* list, t_bool (*match)(T item))
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
	while (list)
	{
		if (match(list->item))
			return (list);
		list = list->next;
	}
	return (NULL);
}



t_sint	CONCAT(List_T,_IndexOf)(s_list_T const* list, T item)
{
	t_uint	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (ERROR);
#endif
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



t_sint	CONCAT(List_T,_IndexOf_F)(s_list_T const* list, t_bool (*match)(T item))
{
	t_uint	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (ERROR);
#endif
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
