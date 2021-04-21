
#include "libccc/memory.h"
#include "libccc/monad/list.h"


_GENERIC()
s_list_T*	CONCAT(List_T,_Remove)(s_list_T* list, T item)
{
	s_list_T*	elem;
	s_list_T*	tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
	elem = list;
	while (elem)
	{
		if (T_EQUALS(elem->item, item))
		{
			tmp = elem->next;
			elem->next = tmp->next;
#if LIBCONFIG_LIST_DOUBLYLINKED
			elem->next->prev = elem;
#endif
			Memory_Free(tmp);
			return (list);
		}
		elem = elem->next;
	}
	return (list);
}


_GENERIC()
s_list_T*	CONCAT(List_T,_Remove_F)(s_list_T* list, T item, void (*delete)(T))
{
	s_list_T*	elem;
	s_list_T*	tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
	elem = list;
	while (elem)
	{
		if (T_EQUALS(elem->item, item))
		{
			delete(elem->item);
			tmp = elem->next;
			elem->next = tmp->next;
#if LIBCONFIG_LIST_DOUBLYLINKED
			elem->next->prev = elem;
#endif
			Memory_Free(tmp);
			return (list);
		}
		elem = elem->next;
	}
	return (list);
}
