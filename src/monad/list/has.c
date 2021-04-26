
#include "libccc/monad/list.h"


_GENERIC()
t_bool	CONCAT(List_Has,T_NAME)(s_list_T const* list, s_list_T const* target)
{
	LIBCONFIG_HANDLE_NULLPOINTER(list, FALSE)
	while (list)
	{
		if (CONCAT(List_Contains,T_NAME)(target, list->item))
			return (TRUE);
		list = list->next;
	}
	return (FALSE);
}


_GENERIC()
t_bool	CONCAT(List_HasOnly,T_NAME)(s_list_T const* list, s_list_T const* target)
{
	LIBCONFIG_HANDLE_NULLPOINTER(list, FALSE)
	while (list)
	{
		if (!CONCAT(List_Contains,T_NAME)(target, list->item))
			return (FALSE);
		list = list->next;
	}
	return (TRUE);
}
