
#include "libccc/monad/list.h"


_GENERIC()
t_uint	CONCAT(List_T,_Count)(s_list_T const* list, T item)
{
	t_uint	result = 0;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (0);
#endif
	while (list)
	{
		if (T_EQUALS(list->item, item))
			result += 1;
		list = list->next;
	}
	return (result);
}
