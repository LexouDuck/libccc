
#include "libccc/monad/list.h"

#include LIBCONFIG_HANDLE_INCLUDE



_GENERIC()
t_bool	CONCAT(List_Contains,T_NAME)(s_list_T const* list, T item)
{
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	while (list)
	{
		if (T_EQUALS(list->item, item))
			return (TRUE);
		list = list->next;
	}
	return (FALSE);
}
