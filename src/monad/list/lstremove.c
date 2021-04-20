
#include "libccc/memory.h"
#include "libccc/monad/list.h"



s_list_T*	CONCAT(List_T,_Remove)(s_list_T* list, t_uint index)
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
	for (t_uint	i = 0; elem && i < index; ++i)
	{
		elem = elem->next;
	}
	if (elem == NULL || elem->next == NULL)
		return (list);
	tmp = elem->next;
	elem->next = tmp->next;
//	elem->next->prev = elem;
	Memory_Free(tmp);
	return (list);
}



s_list_T*	CONCAT(List_T,_RemoveAll)(s_list_T* list, T item)
{
	s_list_T*	elem;
	s_list_T*	tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
	elem = list;
	for (t_uint	i = 0; elem; ++i)
	{
		if (T_EQUALS(elem->item, item))
		{
			tmp = elem->next;
			elem->next = tmp->next;
		//	elem->next->prev = elem;
			Memory_Free(tmp);
		}
		elem = elem->next;
	}
	return (list);
}
