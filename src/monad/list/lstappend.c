
#include "libccc/monad/list.h"



s_list_T*	List_Append(s_list_T* list, s_list_T* elem)
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
//	elem->prev = i;
	i->next = elem;
	return (list);
}
