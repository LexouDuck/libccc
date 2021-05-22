
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_HANDLE_INCLUDE



_GENERIC()
s_list_T*	CONCAT(List_Duplicate,T_NAME)(s_list_T const* list)
{
	s_list_T*	result = NULL;
	s_list_T*	elem = NULL;
	s_list_T*	tmp;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	while (list)
	{
		if (!(tmp = (s_list_T*)Memory_Duplicate(list, sizeof(s_list_T))))
			break;
		if (result == NULL)
			result = tmp;
		else
		{
#if LIBCONFIG_LIST_DOUBLYLINKED
			tmp->prev = elem;
#endif
			elem->next = tmp;
		}
		elem = tmp;
		list = list->next;
	}
	return (result);
}
