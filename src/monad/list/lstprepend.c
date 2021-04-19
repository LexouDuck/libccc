
#include "libccc/monad/list.h"



s_list_T*	List_Prepend(s_list_T* list, s_list_T* elem)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
	if (elem == NULL)
		return (list);
//	elem->prev = NULL;
	elem->next = list;
	return (elem);
}
