
#include <stdarg.h>

#include "libccc/memory.h"
#include "libccc/monad/list.h"


_GENERIC()
s_list_T*	CONCAT(List_New,T_NAME)(t_uint n, ...)
{
	va_list		list;
	T			item;
	s_list_T*	result = NULL;
	s_list_T*	elem;
	s_list_T*	new;

	if (n == 0)
		return (NULL);
	va_start(list, n);
	for (t_uint i = 0; i < n; ++i)
	{
		item = va_arg(list, T);
		if (!(new = (s_list_T*)Memory_Alloc(sizeof(s_list_T))))
			break;
#if LIBCONFIG_LIST_DOUBLYLINKED
		new->prev = NULL;
#endif
		new->next = NULL;
		new->item = item;
		if (i == 0)
		{
			elem = new;
			result = new;
		}
		else
		{
#if LIBCONFIG_LIST_DOUBLYLINKED
			new->prev = elem;
#endif
			elem->next = new;
			elem = elem->next;
		}
	}
	va_end(list);
	return (result);
}
