
#include "libccc/monad/list.h"


_GENERIC()
s_list_T*	CONCAT(List_Get,T_NAME)(s_list_T const* list, t_uint index)
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
			list = list->next;
	}
	return ((s_list_T*)list);
}
