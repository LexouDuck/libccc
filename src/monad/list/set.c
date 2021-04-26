
#include "libccc/monad/list.h"


_GENERIC()
s_list_T*	CONCAT(List_Set,T_NAME)(s_list_T* list, t_uint index, T item)
{
	LIBCONFIG_HANDLE_NULLPOINTER(list, NULL)
	for (t_uint	i = 0; i < index; ++i)
	{
		if (list->next == NULL)
			return (NULL);
		else
		{
			list->item = item;
			return (list);
		}
		list = list->next;
	}
	return (NULL);
}
