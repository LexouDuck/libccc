
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_bool	CONCAT(List_Equals,T_NAME)(s_list_T const* list1, s_list_T const* list2)
{
	if (list1 == list2)
		return (TRUE);
	HANDLE_ERROR(NULLPOINTER, (list1 == NULL), return (FALSE);)
	HANDLE_ERROR(NULLPOINTER, (list2 == NULL), return (FALSE);)
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
	HANDLE_ERROR(NULLPOINTER, (list1 == NULL), return (FALSE);)
	HANDLE_ERROR(NULLPOINTER, (list2 == NULL), return (FALSE);)
	while (list1 && list2 && n--)
	{
		if (!T_EQUALS(list1->item, list2->item))
			return (FALSE);
		list1 = list1->next;
		list2 = list2->next;
	}
	return (TRUE);
}
