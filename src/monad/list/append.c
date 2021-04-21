
#include "libccc/monad/list.h"


_GENERIC()
s_list_T*	CONCAT(List_T,_Append)(s_list_T* list, s_list_T* elem)
{
	s_list_T*	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
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
