
#include "libccc/monad/list.h"


_GENERIC()
void	CONCAT(List_Iterate,T_NAME)(s_list_T* list, void (*f)(T item))
{
	LIBCONFIG_HANDLE_NULLPOINTER(f, )
	LIBCONFIG_HANDLE_NULLPOINTER(list, )
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

	LIBCONFIG_HANDLE_NULLPOINTER(f, )
	LIBCONFIG_HANDLE_NULLPOINTER(list, )
	i = 0;
	while (list)
	{
		f(list->item, i);
		list = list->next;
		++i;
	}
}
