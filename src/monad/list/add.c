
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list_T*	CONCAT(List_Add,T_NAME)(s_list_T* list, T item)
{
	s_list_T*	i;

	if (list == NULL)
		return (List_Item(item));
	i = list;
	while (i->next != NULL)
	{
		i = i->next;
	}
	i->next = List_Item(item);
#if LIBCONFIG_LIST_DOUBLYLINKED
	i->next->prev = i;
#endif
	return (list);
}
