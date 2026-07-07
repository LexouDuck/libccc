
#include "libccc/memory.h"
#include "libccc/generic/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*	List_Remove(T)(s_list(T)* list, T item)
{
	s_list(T)*	prev;
	s_list(T)*	elem;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (NULL);
	prev = NULL;
	elem = list;
	while (elem)
	{
		if (T_EQUALS(elem->item, item))
		{
			if (prev == NULL)
				list = elem->next;
			else
			{
				prev->next = elem->next;
#if LIBCONFIG_LIST_DOUBLYLINKED
				if (elem->next)
					elem->next->prev = prev;
#endif
			}
			Memory_Free(elem);
			return (list);
		}
		prev = elem;
		elem = elem->next;
	}
	return (list);
}

_GENERIC()
s_list(T)*	List_Remove_F(T)(s_list(T)* list, T item, void (*del)(T))
{
	s_list(T)*	prev;
	s_list(T)*	elem;

	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return (NULL);
	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (NULL);
	prev = NULL;
	elem = list;
	while (elem)
	{
		if (T_EQUALS(elem->item, item))
		{
			del(elem->item);
			if (prev == NULL)
				list = elem->next;
			else
			{
				prev->next = elem->next;
#if LIBCONFIG_LIST_DOUBLYLINKED
				if (elem->next)
					elem->next->prev = prev;
#endif
			}
			Memory_Free(elem);
			return (list);
		}
		prev = elem;
		elem = elem->next;
	}
	return (list);
}



_GENERIC()
s_list(T)*	List_RemoveAll(T)(s_list(T)* list, T item)
{
	s_list(T)*	prev;
	s_list(T)*	elem;
	s_list(T)*	next;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (NULL);
	prev = NULL;
	elem = list;
	while (elem)
	{
		next = elem->next;
		if (T_EQUALS(elem->item, item))
		{
			if (prev == NULL)
				list = next;
			else
			{
				prev->next = next;
#if LIBCONFIG_LIST_DOUBLYLINKED
				if (next)
					next->prev = prev;
#endif
			}
			Memory_Free(elem);
		}
		else
			prev = elem;
		elem = next;
	}
	return (list);
}

_GENERIC()
s_list(T)*	List_RemoveAll_F(T)(s_list(T)* list, T item, void (*del)(T))
{
	s_list(T)*	prev;
	s_list(T)*	elem;
	s_list(T)*	next;

	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return (NULL);
	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (NULL);
	prev = NULL;
	elem = list;
	while (elem)
	{
		next = elem->next;
		if (T_EQUALS(elem->item, item))
		{
			del(elem->item);
			if (prev == NULL)
				list = next;
			else
			{
				prev->next = next;
#if LIBCONFIG_LIST_DOUBLYLINKED
				if (next)
					next->prev = prev;
#endif
			}
			Memory_Free(elem);
		}
		else
			prev = elem;
		elem = next;
	}
	return (list);
}
