
#include "libccc/memory.h"
#include "libccc/monad/list.h"


_GENERIC()
s_list_T*	CONCAT(List_T,_RemoveAt)(s_list_T* list, t_uint index)
{
	s_list_T*	elem;
	s_list_T*	tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
	elem = list;
	if (index == 0)
	{
		list = list->next;
		Memory_Free(elem);
		return (list);
	}
	for (t_uint	i = 0; elem && i < index - 1; ++i)
	{
		elem = elem->next;
	}
	if (elem == NULL || elem->next == NULL)
		return (list);
	tmp = elem->next;
	elem->next = tmp->next;
#if LIBCONFIG_LIST_DOUBLYLINKED
	elem->next->prev = elem;
#endif
	Memory_Free(tmp);
	return (list);
}


_GENERIC()
s_list_T*	CONCAT(List_T,_RemoveAt_F)(s_list_T* list, t_uint index, void (*delete)(T))
{
	s_list_T*	elem;
	s_list_T*	tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
	elem = list;
	if (index == 0)
	{
		list = list->next;
		Memory_Free(elem);
		return (list);
	}
	for (t_uint	i = 0; elem && i < index - 1; ++i)
	{
		elem = elem->next;
	}
	if (elem == NULL || elem->next == NULL)
		return (list);
	delete(elem->item);
	tmp = elem->next;
	elem->next = tmp->next;
#if LIBCONFIG_LIST_DOUBLYLINKED
	elem->next->prev = elem;
#endif
	Memory_Free(tmp);
	return (list);
}
