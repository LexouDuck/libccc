
#include "libccc/monad/list.h"



s_list_T*	List_Find(s_list_T const* lst, void const* query)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL)
		return (NULL);
#endif
	if (query == NULL)
		return (NULL);
	while (lst)
	{
		if (lst->item == query)
			return ((s_list_T*)lst);
		lst = lst->next;
	}
	return (NULL);
}
