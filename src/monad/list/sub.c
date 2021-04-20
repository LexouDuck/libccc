
#include "libccc/memory.h"
#include "libccc/monad/list.h"



s_list_T*		CONCAT(List_T,_Sub)(s_list_T const* list, t_uint index, t_uint n)
{
	s_list_T*	result = NULL;
	s_list_T*	elem = NULL;
	s_list_T*	tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return (NULL);
#endif
	if (n == 0)
		return (NULL);
	while (list && index--)
	{
		list = list->next;
	}
	if (list == NULL)
		return (NULL);
	elem = result;
	list = list->next;
	while (list && n--)
	{
		if (!(tmp = (s_list_T*)Memory_Duplicate(list, sizeof(s_list_T))))
			break;
		if (result == NULL)
			result = tmp;
		else
		{
//			elem->prev = elem;
			elem->next = tmp;
		}
		elem = tmp;
		list = list->next;
	}
	return (result);
}
