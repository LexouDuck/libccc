
#include "libccc/generic/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_bool	List_Equals(T)(s_list(T) const* list1, s_list(T) const* list2)
{
	if (list1 == list2)
		return (TRUE);
	if CCCERROR((list1 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if CCCERROR((list2 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
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
t_bool	List_Equals_N(T)(s_list(T) const* list1, s_list(T) const* list2, t_uint n)
{
	if (list1 == list2)
		return (TRUE);
	if CCCERROR((list1 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if CCCERROR((list2 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	while (list1 && list2 && n--)
	{
		if (!T_EQUALS(list1->item, list2->item))
			return (FALSE);
		list1 = list1->next;
		list2 = list2->next;
	}
	return (TRUE);
}
