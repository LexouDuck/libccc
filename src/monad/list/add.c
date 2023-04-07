
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*	List_Add(T)(s_list(T)* list, T item)
{
	s_list(T)*	i;

	if (list == NULL)
		return (List_Item(T)(item));
	i = list;
	while (i->next != NULL)
	{
		i = i->next;
	}
	i->next = List_Item(T)(item);
#if LIBCONFIG_LIST_DOUBLYLINKED
	i->next->prev = i;
#endif
	return (list);
}
