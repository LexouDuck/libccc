
#include "libccc/monad/list.h"

#include LIBCONFIG_HANDLE_INCLUDE



_GENERIC()
t_sint	CONCAT(List_Compare,T_NAME)(s_list_T const* list1, s_list_T const* list2, t_sint (*compare)(T item1, T item2))
{
	t_sint	result;

	HANDLE_ERROR(NULLPOINTER, (compare == NULL), return (ERROR);)
	if (list1 == list2)
		return (0);
	HANDLE_ERROR(NULLPOINTER, (list1 == NULL), return (ERROR);)
	HANDLE_ERROR(NULLPOINTER, (list2 == NULL), return (ERROR);)
	while (list1 && list2)
	{
		result = compare(list1->item, list2->item);
		if (result != 0)
			return (result);
		list1 = list1->next;
		list2 = list2->next;
	}
	return (0);
}



_GENERIC()
t_sint	CONCAT(List_Compare_N,T_NAME)(s_list_T const* list1, s_list_T const* list2, t_sint (*compare)(T item1, T item2), t_uint n)
{
	t_sint	result;

	HANDLE_ERROR(NULLPOINTER, (compare == NULL), return (ERROR);)
	if (list1 == list2)
		return (0);
	HANDLE_ERROR(NULLPOINTER, (list1 == NULL), return (ERROR);)
	HANDLE_ERROR(NULLPOINTER, (list2 == NULL), return (ERROR);)
	while (list1 && list2 && n--)
	{
		result = compare(list1->item, list2->item);
		if (result != 0)
			return (result);
		list1 = list1->next;
		list2 = list2->next;
	}
	return (0);
}
