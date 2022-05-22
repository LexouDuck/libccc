
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*	List_Duplicate(T)(s_list(T) const* list)
{
	s_list(T)*	result = NULL;
	s_list(T)*	elem = NULL;
	s_list(T)*	tmp;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	while (list)
	{
		if (!(tmp = (s_list(T)*)Memory_Duplicate(list, sizeof(s_list(T)))))
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
