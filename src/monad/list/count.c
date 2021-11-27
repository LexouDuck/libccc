
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_uint	List_Count(T)(s_list(T) const* list, T item)
{
	t_uint	result = 0;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (0);)
	while (list)
	{
		if (T_EQUALS(list->item, item))
			result += 1;
		list = list->next;
	}
	return (result);
}
