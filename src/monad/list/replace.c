
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*	List_Replace(T)(s_list(T) const* list, T item_old, T item_new)
{
	s_list(T)*	result = NULL;
	s_list(T)*	elem;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	result = List_Duplicate(T)(list);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	elem = result;
	while (elem)
	{
		if (T_EQUALS(elem->item, item_old))
		{
			elem->item = item_new;
		}
		elem = elem->next;
	}
	return (result);
}



_GENERIC()
s_list(T)*	List_ReplaceFirst(T)(s_list(T) const* list, T item_old, T item_new, t_uint n)
{
	s_list(T)*	result = NULL;
	s_list(T)*	elem;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	result = List_Duplicate(T)(list);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	elem = result;
	while (elem)
	{
		if (n == 0)
			return (result);
		if (T_EQUALS(elem->item, item_old))
		{
			elem->item = item_new;
			n -= 1;
		}
		elem = elem->next;
	}
	return (result);
}



_GENERIC()
s_list(T)*	List_ReplaceLast(T)(s_list(T) const* list, T item_old, T item_new, t_uint n)
{
	s_list(T)*	result = NULL;
	s_list(T)*	elem;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	result = List_Duplicate(T)(list);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
#if LIBCONFIG_LIST_DOUBLYLINKED
	elem = result->prev;
	while (elem)
	{
		if (n == 0)
			return (result);
		if (T_EQUALS(elem->item, item_old))
		{
			elem->item = item_new;
			n -= 1;
		}
		elem = elem->prev;
	}
#else
	t_uint total = 0;
	for (elem = result; elem != NULL; elem = elem->next)
	{
		if (T_EQUALS(elem->item, item_old))
			total += 1;
	}
	for (elem = result; elem != NULL; elem = elem->next)
	{
		if (n == 0)
			return (result);
		if (T_EQUALS(elem->item, item_old))
		{
			if (total == n)
			{
				elem->item = item_new;
				n -= 1;
			}
			total -= 1;
		}
	}
#endif
	return (result);
}
