
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*	List_Reverse(T)(s_list(T) const* list)
{
	s_list(T)*	result = NULL;
	s_list(T)*	previous;
	s_list(T)*	current;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (NULL);
	result = List_Duplicate(T)(list);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
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
