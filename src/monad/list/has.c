
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_bool	List_Has(T)(s_list(T) const* list, s_list(T) const* target)
{
	if CCCERROR((list == NULL), ERROR_NULLPOINTER, NULL)
		return (FALSE);
	while (list)
	{
		if (List_Contains(T)(target, list->item))
			return (TRUE);
		list = list->next;
	}
	return (FALSE);
}



_GENERIC()
t_bool	List_HasOnly(T)(s_list(T) const* list, s_list(T) const* target)
{
	if CCCERROR((list == NULL), ERROR_NULLPOINTER, NULL)
		return (FALSE);
	while (list)
	{
		if (!List_Contains(T)(target, list->item))
			return (FALSE);
		list = list->next;
	}
	return (TRUE);
}
