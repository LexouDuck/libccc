
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list_T*	CONCAT(List_Remove,T_NAME)(s_list_T* list, T item)
{
	s_list_T*	elem;
	s_list_T*	tmp;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
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
s_list_T*	CONCAT(List_Remove_F,T_NAME)(s_list_T* list, T item, void (*delete)(T))
{
	s_list_T*	elem;
	s_list_T*	tmp;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
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
