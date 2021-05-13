
#include "libccc/monad/list.h"


_GENERIC()
t_uint	CONCAT(List_Count,T_NAME)(s_list_T const* list, T item)
{
	t_uint	result = 0;

	LIBCONFIG_HANDLE_NULLPOINTER(0, list)
	while (list)
	{
		if (T_EQUALS(list->item, item))
			result += 1;
		list = list->next;
	}
	return (result);
}
