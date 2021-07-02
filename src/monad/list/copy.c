
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list_T*	CONCAT(List_Copy,T_NAME)(s_list_T* dest, s_list_T const* src, t_uint n)
{
	s_list_T*	list;

	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (NULL);)
	list = dest;
	while (list && n--)
	{
		list->item = src->item;
		src = src->next;
		list = list->next;
	}
	return (dest);
}
