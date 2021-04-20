
#include "libccc/monad/list.h"



t_bool	CONCAT(List_T,_Has)(s_list_T const* list, s_list_T const* target)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
	while (list)
	{
		if (CONCAT(List_T,_Contains)(target, list->item))
			return (TRUE);
		list = list->next;
	}
	return (FALSE);
}



t_bool	CONCAT(List_T,_HasOnly)(s_list_T const* list, s_list_T const* target)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
	while (list)
	{
		if (!CONCAT(List_T,_Contains)(target, list->item))
			return (FALSE);
		list = list->next;
	}
	return (TRUE);
}
