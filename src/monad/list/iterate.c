
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	List_Iterate(T)(s_list(T)* list, void (*f)(T item))
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
void	List_Iterate_I(T)(s_list(T)* list, void (*f)(T item, t_uint index))
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
