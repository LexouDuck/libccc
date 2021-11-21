
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list_T*	CONCAT(List_New,T_NAME)(t_uint n, T value)
{
	s_list_T*	result = NULL;
	s_list_T*	elem;
	s_list_T*	new;

	HANDLE_ERROR(LENGTH2SMALL, (n == 0), return (NULL);)
	for (t_uint i = 0; i < n; ++i)
	{
		new = (s_list_T*)Memory_Allocate(sizeof(s_list_T));
		HANDLE_ERROR(ALLOCFAILURE, (new == NULL), break;)
#if LIBCONFIG_LIST_DOUBLYLINKED
		new->prev = NULL;
#endif
		new->next = NULL;
		new->item = value;
		if (i == 0)
		{
			elem = new;
			result = new;
		}
		else
		{
#if LIBCONFIG_LIST_DOUBLYLINKED
			new->prev = elem;
#endif
			elem->next = new;
			elem = elem->next;
		}
	}
	return (result);
}
