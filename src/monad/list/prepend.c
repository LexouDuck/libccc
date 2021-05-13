
#include "libccc/monad/list.h"


_GENERIC()
s_list_T*	CONCAT(List_Prepend,T_NAME)(s_list_T* list, s_list_T* elem)
{
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, list)
	if (elem == NULL)
		return (list);
#if LIBCONFIG_LIST_DOUBLYLINKED
	elem->prev = NULL;
#endif
	elem->next = list;
	return (elem);
}
