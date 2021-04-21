
#include "libccc/monad/list.h"


_GENERIC()
s_list_T*	CONCAT(List_Prepend,T_NAME)(s_list_T* list, s_list_T* elem)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
	if (elem == NULL)
		return (list);
#if LIBCONFIG_LIST_DOUBLYLINKED
	elem->prev = NULL;
#endif
	elem->next = list;
	return (elem);
}
