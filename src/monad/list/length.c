
#include "libccc/monad/list.h"


_GENERIC()
t_uint	CONCAT(List_Length,T_NAME)(s_list_T const* list)
{
	t_uint	result;

	LIBCONFIG_HANDLE_NULLPOINTER(list, 0)
	result = 0;
	while (list)
	{
		++result;
		list = list->next;
	}
	return (result);
}
