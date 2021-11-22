
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list_T*	CONCAT(List_Reverse,T_NAME)(s_list_T const* list)
{
	s_list_T*	result = NULL;
	s_list_T*	previous;
	s_list_T*	current;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	result = CONCAT(List_Duplicate,T_NAME)(list);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	previous = result;
	result = result->next;
	current = result;
	previous->next = NULL;
	while (result != NULL)
	{
		result = result->next;
#if LIBCONFIG_LIST_DOUBLYLINKED
		current->prev = result;
#endif
		current->next = previous;
		previous = current;
		current = result;
	}
	result = previous;
	return (result);
}
