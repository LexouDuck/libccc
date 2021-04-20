
#include "libccc/monad/list.h"



s_list_T*	CONCAT(List_T,_Copy)(s_list_T* dest, s_list_T const* src, t_uint n)
{
	s_list_T*	list;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (dest == NULL || src == NULL)
		return (NULL);
#endif
	list = dest;
	while (list && n--)
	{
		list->item = src->item;
		src = src->next;
		list = list->next;
	}
	return (dest);
}
