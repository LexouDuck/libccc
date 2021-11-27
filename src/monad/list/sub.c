
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*		List_Sub(T)(s_list(T) const* list, t_uint index, t_uint n)
{
	s_list(T)*	result = NULL;
	s_list(T)*	elem = NULL;
	s_list(T)*	tmp;
	t_uint		length;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	length = List_Length(T)(list);
	HANDLE_ERROR(INDEX2LARGE, (index >= length),    return (NULL);)
	HANDLE_ERROR(LENGTH2LARGE, (index + n > length), return (NULL);)
	if (n == 0)
		n = length - index;
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
		tmp = (s_list(T)*)Memory_Duplicate(list, sizeof(s_list(T)));
		HANDLE_ERROR(ALLOCFAILURE, (tmp == NULL),
		{
			List_Free(T)(tmp);
			return (NULL);
		})
		if (result == NULL)
			result = tmp;
		else
		{
#if LIBCONFIG_LIST_DOUBLYLINKED
			elem->prev = elem;
#endif
			elem->next = tmp;
		}
		elem = tmp;
		list = list->next;
	}
	return (result);
}
