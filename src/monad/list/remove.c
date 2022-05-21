
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*	List_Remove(T)(s_list(T)* list, T item)
{
	s_list(T)*	elem;
	s_list(T)*	tmp;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	elem = list;
	while (elem)
	{
		if (T_EQUALS(elem->item, item))
		{
			tmp = elem->next;
			elem->next = tmp->next;
#if LIBCONFIG_LIST_DOUBLYLINKED
			elem->next->prev = elem;
#endif
			Memory_Free(tmp);
			return (list);
		}
		elem = elem->next;
	}
	return (list);
}



_GENERIC()
s_list(T)*	List_Remove_F(T)(s_list(T)* list, T item, void (*del)(T))
{
	s_list(T)*	elem;
	s_list(T)*	tmp;

	if CCCERROR((del == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	if CCCERROR((list == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	elem = list;
	while (elem)
	{
		if (T_EQUALS(elem->item, item))
		{
			del(elem->item);
			tmp = elem->next;
			elem->next = tmp->next;
#if LIBCONFIG_LIST_DOUBLYLINKED
			elem->next->prev = elem;
#endif
			Memory_Free(tmp);
			return (list);
		}
		elem = elem->next;
	}
	return (list);
}



_GENERIC()
s_list(T)*	List_RemoveAll(T)(s_list(T)* list, T item)
{
	s_list(T)*	elem;
	s_list(T)*	tmp;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	elem = list;
	while (elem)
	{
		if (T_EQUALS(elem->item, item))
		{
			tmp = elem->next;
			elem->next = tmp->next;
#if LIBCONFIG_LIST_DOUBLYLINKED
			elem->next->prev = elem;
#endif
			Memory_Free(tmp);
		}
		elem = elem->next;
	}
	return (list);
}



_GENERIC()
s_list(T)*	List_RemoveAll_F(T)(s_list(T)* list, T item, void (*del)(T))
{
	s_list(T)*	elem;
	s_list(T)*	tmp;

	if CCCERROR((del == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	if CCCERROR((list == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	elem = list;
	while (elem)
	{
		if (T_EQUALS(elem->item, item))
		{
			del(elem->item);
			tmp = elem->next;
			elem->next = tmp->next;
#if LIBCONFIG_LIST_DOUBLYLINKED
			elem->next->prev = elem;
#endif
			Memory_Free(tmp);
		}
		elem = elem->next;
	}
	return (list);
}
