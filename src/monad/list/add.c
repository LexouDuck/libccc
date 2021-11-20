
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	CONCAT(List_Add,T_NAME)(s_list_T* list, s_list_T* elem)
{
	s_list_T*	i;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (elem);)
	HANDLE_ERROR(NULLPOINTER, (elem == NULL), return (list);)
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
