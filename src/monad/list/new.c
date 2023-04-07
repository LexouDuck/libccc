
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*	List_New(T)(t_uint n, T value)
{
	s_list(T)*	result = NULL;
	s_list(T)*	elem;
	s_list(T)*	newitem;

	if CCCERROR((n == 0), ERROR_LENGTH2SMALL, NULL)
		return (NULL);
	for (t_uint i = 0; i < n; ++i)
	{
		newitem = (s_list(T)*)Memory_Allocate(sizeof(s_list(T)));
		if CCCERROR((newitem == NULL), ERROR_ALLOCFAILURE, NULL)
			break;
#if LIBCONFIG_LIST_DOUBLYLINKED
		newitem->prev = NULL;
#endif
		newitem->next = NULL;
		newitem->item = value;
		if (i == 0)
		{
			elem = newitem;
			result = newitem;
		}
		else
		{
#if LIBCONFIG_LIST_DOUBLYLINKED
			newitem->prev = elem;
#endif
			elem->next = newitem;
			elem = elem->next;
		}
	}
	return (result);
}
