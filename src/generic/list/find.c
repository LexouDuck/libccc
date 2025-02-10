
#include "libccc/generic/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T) const*	List_Find(T)(s_list(T) const* list, T item)
{
	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (NULL);
	while (list)
	{
		if (T_EQUALS(list->item, item))
			return (list);
		list = list->next;
	}
	CCCERROR(TRUE, ERROR_NOTFOUND, NULL);
	return (NULL);
}



_GENERIC()
s_list(T) const*	List_Find_F(T)(s_list(T) const* list, t_bool (*match)(T item))
{
	if CCCERROR((match == NULL), ERROR_NULLPOINTER, "match() function given is NULL")
		return (NULL);
	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (NULL);
	while (list)
	{
		if (match(list->item))
			return (list);
		list = list->next;
	}
	CCCERROR(TRUE, ERROR_NOTFOUND, NULL);
	return (NULL);
}



_GENERIC()
t_sint	List_IndexOf(T)(s_list(T) const* list, T item)
{
	t_uint	i;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (ERROR);
	i = 0;
	while (list)
	{
		if (T_EQUALS(list->item, item))
			return (i);
		list = list->next;
		++i;
	}
	CCCERROR(TRUE, ERROR_NOTFOUND, NULL);
	return (ERROR);
}



_GENERIC()
t_sint	List_IndexOf_F(T)(s_list(T) const* list, t_bool (*match)(T item))
{
	t_uint	i;

	if CCCERROR((match == NULL), ERROR_NULLPOINTER, "match() function given is NULL")
		return (ERROR);
	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (ERROR);
	i = 0;
	while (list)
	{
		if (match(list->item))
			return (i);
		list = list->next;
		++i;
	}
	CCCERROR(TRUE, ERROR_NOTFOUND, NULL);
	return (ERROR);
}
