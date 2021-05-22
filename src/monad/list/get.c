
#include "libccc/monad/list.h"

#include LIBCONFIG_HANDLE_INCLUDE



_GENERIC()
s_list_T*	CONCAT(List_Get,T_NAME)(s_list_T const* list, t_uint index)
{
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	for (t_uint	i = 0; i < index; ++i)
	{
		if (list->next == NULL)
			return (NULL);
		else
			list = list->next;
	}
	return ((s_list_T*)list);
}
