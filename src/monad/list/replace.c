
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list_T*	CONCAT(List_Replace,T_NAME)(s_list_T const* list, T old, T new)
{
	s_list_T*	result = NULL;
	s_list_T*	elem;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	result = CONCAT(List_Duplicate,T_NAME)(list);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	elem = result;
	while (elem)
	{
		if (T_EQUALS(elem->item, old))
		{
			elem->item = new;
		}
		elem = elem->next;
	}
	return (result);
}



_GENERIC()
s_list_T*	CONCAT(List_ReplaceFirst,T_NAME)(s_list_T const* list, T old, T new, t_uint n)
{
	s_list_T*	result = NULL;
	s_list_T*	elem;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	result = CONCAT(List_Duplicate,T_NAME)(list);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	elem = result;
	while (elem)
	{
		if (n == 0)
			return (result);
		if (T_EQUALS(elem->item, old))
		{
			elem->item = new;
			n -= 1;
		}
		elem = elem->next;
	}
	return (result);
}



_GENERIC()
s_list_T*	CONCAT(List_ReplaceLast,T_NAME)(s_list_T const* list, T old, T new, t_uint n)
{
	s_list_T*	result = NULL;
	s_list_T*	elem;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	result = CONCAT(List_Duplicate,T_NAME)(list);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
#if LIBCONFIG_LIST_DOUBLYLINKED
	elem = result->prev;
	while (elem)
	{
		if (n == 0)
			return (result);
		if (T_EQUALS(elem->item, old))
		{
			elem->item = new;
			n -= 1;
		}
		elem = elem->prev;
	}
#else
	t_uint total = 0;
	for (elem = result; elem != NULL; elem = elem->next)
	{
		if (T_EQUALS(elem->item, old))
			total += 1;
	}
	for (elem = result; elem != NULL; elem = elem->next)
	{
		if (n == 0)
			return (result);
		if (T_EQUALS(elem->item, old))
		{
			if (total == n)
			{
				elem->item = new;
				n -= 1;
			}
			total -= 1;
		}
	}
#endif
	return (result);
}
