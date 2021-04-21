
#include "libccc/monad/list.h"


_GENERIC()
s_list_T*	CONCAT(List_T,_Set)(s_list_T* list, t_uint index, T item)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
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
