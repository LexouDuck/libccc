
#include "libccc/monad/list.h"


_GENERIC()
void	CONCAT(List_Iterate,T_NAME)(s_list_T* list, void (*f)(T item))
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL || f == NULL)
		return;
#endif
	while (list)
	{
		f(list->item);
		list = list->next;
	}
}


_GENERIC()
void	CONCAT(List_Iterate_I,T_NAME)(s_list_T* list, void (*f)(T item, t_uint index))
{
	t_uint i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL || f == NULL)
		return;
#endif
	i = 0;
	while (list)
	{
		f(list->item, i);
		list = list->next;
		++i;
	}
}
