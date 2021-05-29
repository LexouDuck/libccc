
#include "libccc/monad/list.h"

#include LIBCONFIG_HANDLE_INCLUDE



_GENERIC()
void	CONCAT(List_Iterate,T_NAME)(s_list_T* list, void (*f)(T item))
{
	HANDLE_ERROR(NULLPOINTER, (f == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return;)
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

	HANDLE_ERROR(NULLPOINTER, (f == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return;)
	i = 0;
	while (list)
	{
		f(list->item, i);
		list = list->next;
		++i;
	}
}
