
#include "libccc/monad/list.h"


_GENERIC()
s_list_T*	CONCAT(List_Append,T_NAME)(s_list_T* list, s_list_T* elem)
{
	s_list_T*	i;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, list)
	if (elem == NULL)
		return (list);
	i = list;
	while (i->next != NULL)
	{
		i = i->next;
	}
#if LIBCONFIG_LIST_DOUBLYLINKED
	elem->prev = i;
#endif
	i->next = elem;
	return (list);
}
