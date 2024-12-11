
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*	List_RemoveAt(T)(s_list(T)* list, t_uint index)
{
	s_list(T)*	elem;
	s_list(T)*	tmp;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (NULL);
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
	if CCCERROR((elem == NULL || elem->next == NULL), ERROR_INDEX2LARGE, 
		"index given (" SF_UINT ") is beyond end of list (length: " SF_UINT ")",
		index, List_Length(T)(list))
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
s_list(T)*	List_RemoveAt_F(T)(s_list(T)* list, t_uint index, void (*del)(T))
{
	s_list(T)*	elem;
	s_list(T)*	tmp;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (NULL);
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
	if CCCERROR((elem == NULL || elem->next == NULL), ERROR_INDEX2LARGE, 
		"index given (" SF_UINT ") is beyond end of list (length: " SF_UINT ")",
		index, List_Length(T)(list))
		return (list);
	del(elem->item);
	tmp = elem->next;
	elem->next = tmp->next;
#if LIBCONFIG_LIST_DOUBLYLINKED
	elem->next->prev = elem;
#endif
	Memory_Free(tmp);
	return (list);
}
