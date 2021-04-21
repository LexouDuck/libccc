
#include "libccc/monad/list.h"


_GENERIC()
s_list_T const*	CONCAT(List_Find,T_NAME)(s_list_T const* list, T item)
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


_GENERIC()
s_list_T const*	CONCAT(List_Find_F,T_NAME)(s_list_T const* list, t_bool (*match)(T item))
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


_GENERIC()
t_sint	CONCAT(List_IndexOf,T_NAME)(s_list_T const* list, T item)
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


_GENERIC()
t_sint	CONCAT(List_IndexOf_F,T_NAME)(s_list_T const* list, t_bool (*match)(T item))
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
