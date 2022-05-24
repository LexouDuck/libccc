
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	List_Iterate(T)(s_list(T)* list, void (*f)(T item))
{
	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return;
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

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return;
	i = 0;
	while (list)
	{
		f(list->item, i);
		list = list->next;
		++i;
	}
}
