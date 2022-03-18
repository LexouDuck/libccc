
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*	List_RemoveAt(T)(s_list(T)* list, t_uint index)
{
	s_list(T)*	elem;
	s_list(T)*	tmp;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
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
	HANDLE_ERROR_SF(INDEX2LARGE, (elem == NULL || elem->next == NULL), return (list);,
		"index given ("SF_UINT") is beyond end of list (length: "SF_UINT")",
		index, List_Length(T)(list))
	tmp = elem->next;
	elem->next = tmp->next;
#if LIBCONFIG_LIST_DOUBLYLINKED
	elem->next->prev = elem;
#endif
	Memory_Free(tmp);
	return (list);
}



_GENERIC()
s_list(T)*	List_RemoveAt_F(T)(s_list(T)* list, t_uint index, void (*delete)(T))
{
	s_list(T)*	elem;
	s_list(T)*	tmp;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
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
	HANDLE_ERROR_SF(INDEX2LARGE, (elem == NULL || elem->next == NULL), return (list);,
		"index given ("SF_UINT") is beyond end of list (length: "SF_UINT")",
		index, List_Length(T)(list))
	delete(elem->item);
	tmp = elem->next;
	elem->next = tmp->next;
#if LIBCONFIG_LIST_DOUBLYLINKED
	elem->next->prev = elem;
#endif
	Memory_Free(tmp);
	return (list);
}
