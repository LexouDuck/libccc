
#include "libccc/monad/list.h"


_GENERIC()
t_bool	CONCAT(List_T,_Contains)(s_list_T const* list, T item)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
	while (list)
	{
		if (T_EQUALS(list->item, item))
			return (TRUE);
		list = list->next;
	}
	return (FALSE);
}
