
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_uint	List_Count(T)(s_list(T) const* list, T item)
{
	t_uint	result = 0;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (0);
	while (list)
	{
		if (T_EQUALS(list->item, item))
			result += 1;
		list = list->next;
	}
	return (result);
}
