
#include "libccc/monad/list.h"



t_bool	CONCAT(List_T,_Equals)(s_list_T const* list1, s_list_T const* list2)
{
//#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list1 == list2)
		return (TRUE);
	if (list1 == NULL || list2 == NULL)
		return (FALSE);
//#endif
	while (list1 && list2)
	{
		if (!T_EQUALS(list1->item, list2->item))
			return (FALSE);
		list1 = list1->next;
		list2 = list2->next;
	}
	return (TRUE);
}



t_bool	CONCAT(List_T,_Equals_N)(s_list_T const* list1, s_list_T const* list2, t_uint n)
{
//#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list1 == list2)
		return (TRUE);
	if (list1 == NULL || list2 == NULL)
		return (FALSE);
//#endif
	while (list1 && list2 && n--)
	{
		if (!T_EQUALS(list1->item, list2->item))
			return (FALSE);
		list1 = list1->next;
		list2 = list2->next;
	}
	return (TRUE);
}
