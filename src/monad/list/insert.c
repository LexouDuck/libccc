
#include "libccc/memory.h"
#include "libccc/monad/list.h"


_GENERIC()
s_list_T*	CONCAT(List_Insert,T_NAME)(s_list_T* list, T item, t_uint index)
{
	s_list_T*	elem;
	s_list_T*	new;
	s_list_T*	tmp;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, list)
	if (!(new = (s_list_T*)Memory_Alloc(sizeof(s_list_T))))
		return (list);
	if (list == NULL || index == 0)
	{
		new->item = item;
		new->next = list;
		return (new);
	}
	elem = list;
	for (t_uint i = 0; i < index; ++i)
	{
		elem = elem->next;
	}
#if LIBCONFIG_LIST_DOUBLYLINKED
	new->prev = elem;
#endif
	tmp = elem->next;
	elem->next = new;
	new->next = tmp;
	return (list);
}
