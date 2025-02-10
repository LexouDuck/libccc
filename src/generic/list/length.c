
#include "libccc/generic/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_uint	List_Length(T)(s_list(T) const* list)
{
	t_uint	result;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (0);
	result = 0;
	while (list)
	{
		++result;
		list = list->next;
	}
	return (result);
}
