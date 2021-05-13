
#include "libccc/monad/list.h"


_GENERIC()
s_list_T*	CONCAT(List_Copy,T_NAME)(s_list_T* dest, s_list_T const* src, t_uint n)
{
	s_list_T*	list;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, dest)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, src)
	list = dest;
	while (list && n--)
	{
		list->item = src->item;
		src = src->next;
		list = list->next;
	}
	return (dest);
}
