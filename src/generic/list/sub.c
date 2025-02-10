
#include "libccc/memory.h"
#include "libccc/generic/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*		List_Sub(T)(s_list(T) const* list, t_uint index, t_uint n)
{
	s_list(T)*	result = NULL;
	s_list(T)*	elem = NULL;
	s_list(T)*	tmp;
	t_uint		length;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (NULL);
	length = List_Length(T)(list);
	if CCCERROR((index >= length), ERROR_INDEX2LARGE, NULL)
		return (NULL);
	if CCCERROR((index + n > length), ERROR_LENGTH2LARGE, NULL)
		return (NULL);
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
		if CCCERROR((tmp == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			List_Free(T)(tmp);
			return (NULL);
		}
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
