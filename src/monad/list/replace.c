
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
			return (result);
		}
		elem = elem->next;
	}
	return (result);
}



_GENERIC()
s_list_T*	CONCAT(List_ReplaceAll,T_NAME)(s_list_T const* list, T old, T new)
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
