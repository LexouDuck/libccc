
#include "libccc/monad/list.h"


_GENERIC()
t_bool	CONCAT(List_Equals,T_NAME)(s_list_T const* list1, s_list_T const* list2)
{
	if (list1 == list2)
		return (TRUE);
	LIBCONFIG_HANDLE_NULLPOINTER(list1, FALSE)
	LIBCONFIG_HANDLE_NULLPOINTER(list2, FALSE)
	while (list1 && list2)
	{
		if (!T_EQUALS(list1->item, list2->item))
			return (FALSE);
		list1 = list1->next;
		list2 = list2->next;
	}
	return (TRUE);
}


_GENERIC()
t_bool	CONCAT(List_Equals_N,T_NAME)(s_list_T const* list1, s_list_T const* list2, t_uint n)
{
	if (list1 == list2)
		return (TRUE);
	LIBCONFIG_HANDLE_NULLPOINTER(list1, FALSE)
	LIBCONFIG_HANDLE_NULLPOINTER(list2, FALSE)
	while (list1 && list2 && n--)
	{
		if (!T_EQUALS(list1->item, list2->item))
			return (FALSE);
		list1 = list1->next;
		list2 = list2->next;
	}
	return (TRUE);
}
