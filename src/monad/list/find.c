
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T) const*	List_Find(T)(s_list(T) const* list, T item)
{
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	while (list)
	{
		if (T_EQUALS(list->item, item))
			return (list);
		list = list->next;
	}
	HANDLE_ERROR(NOTFOUND, (TRUE), return (NULL);)
}



_GENERIC()
s_list(T) const*	List_Find_F(T)(s_list(T) const* list, t_bool (*match)(T item))
{
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	while (list)
	{
		if (match(list->item))
			return (list);
		list = list->next;
	}
	HANDLE_ERROR(NOTFOUND, (TRUE), return (NULL);)
}



_GENERIC()
t_sint	List_IndexOf(T)(s_list(T) const* list, T item)
{
	t_uint	i;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (ERROR);)
	i = 0;
	while (list)
	{
		if (T_EQUALS(list->item, item))
			return (i);
		list = list->next;
		++i;
	}
	HANDLE_ERROR(NOTFOUND, (TRUE), return (ERROR);)
}



_GENERIC()
t_sint	List_IndexOf_F(T)(s_list(T) const* list, t_bool (*match)(T item))
{
	t_uint	i;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (ERROR);)
	i = 0;
	while (list)
	{
		if (match(list->item))
			return (i);
		list = list->next;
		++i;
	}
	HANDLE_ERROR(NOTFOUND, (TRUE), return (ERROR);)
}
