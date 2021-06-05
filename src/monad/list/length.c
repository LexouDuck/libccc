
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_uint	CONCAT(List_Length,T_NAME)(s_list_T const* list)
{
	t_uint	result;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (0);)
	result = 0;
	while (list)
	{
		++result;
		list = list->next;
	}
	return (result);
}
