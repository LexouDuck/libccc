
#include "libccc/monad/list.h"



s_list_T const*	CONCAT(List_T,_Find)(s_list_T const* list, T item)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
	while (list)
	{
		if (list->item == item)
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
		if (list->item == item)
			return (i);
		list = list->next;
		++i;
	}
	return (ERROR);
}
