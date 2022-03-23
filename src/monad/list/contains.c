
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_bool	List_Contains(T)(s_list(T) const* list, T item)
{
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (FALSE);)
	while (list)
	{
		if (T_EQUALS(list->item, item))
			return (TRUE);
		list = list->next;
	}
	return (FALSE);
}
