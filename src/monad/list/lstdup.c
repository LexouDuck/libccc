
#include "libccc/memory.h"
#include "libccc/monad/list.h"



s_list_T*	List_Duplicate(s_list_T const* list)
{
	s_list_T	*result = NULL;
	s_list_T	*elem = NULL;
	s_list_T	*tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
	while (list)
	{
		if (!(tmp = (s_list_T*)Memory_Duplicate(list, sizeof(s_list_T))))
			break;
		if (result == NULL)
			result = tmp;
		else
		{
//			elem->prev = elem;
			elem->next = tmp;
		}
		elem = tmp;
		list = list->next;
	}
	return (result);
}
