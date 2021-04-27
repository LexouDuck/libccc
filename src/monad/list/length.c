
#include "libccc/monad/list.h"


_GENERIC()
t_uint	CONCAT(List_Length,T_NAME)(s_list_T const* list)
{
	t_uint	result;

	LIBCONFIG_HANDLE_NULLPOINTER(0, list)
	result = 0;
	while (list)
	{
		++result;
		list = list->next;
	}
	return (result);
}
