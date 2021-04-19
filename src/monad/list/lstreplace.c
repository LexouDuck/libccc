
#include "libccc/monad/list.h"



s_list_T*	CONCAT(List_T,_Replace)(s_list_T const* list, T old, T new)
{
	s_list_T*	result = NULL;
	s_list_T*	elem;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
	while (list)
	{
		elem = CONCAT(List_T,_Item)(list->item == old ? new : list->item);
		if (elem == NULL)
			break;
		CONCAT(List_T,_Append)(result, elem);
		list = list->next;
	}
	return (result);
}
