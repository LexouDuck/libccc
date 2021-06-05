
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list_T*	CONCAT(List_Prepend,T_NAME)(s_list_T* list, s_list_T* elem)
{
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	if (elem == NULL)
		return (list);
#if LIBCONFIG_LIST_DOUBLYLINKED
	elem->prev = NULL;
#endif
	elem->next = list;
	return (elem);
}
