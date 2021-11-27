
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*	List_New(T)(t_uint n, T value)
{
	s_list(T)*	result = NULL;
	s_list(T)*	elem;
	s_list(T)*	new;

	HANDLE_ERROR(LENGTH2SMALL, (n == 0), return (NULL);)
	for (t_uint i = 0; i < n; ++i)
	{
		new = (s_list(T)*)Memory_Allocate(sizeof(s_list(T)));
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
