
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_HANDLE_INCLUDE



_GENERIC()
s_list_T*	CONCAT(List_Insert,T_NAME)(s_list_T* list, T item, t_uint index)
{
	s_list_T*	elem;
	s_list_T*	new;
	s_list_T*	tmp;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	new = (s_list_T*)Memory_Allocate(sizeof(s_list_T));
	HANDLE_ERROR(ALLOCFAILURE, (new == NULL), return (list);)
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
