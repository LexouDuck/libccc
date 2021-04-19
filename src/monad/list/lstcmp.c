
#include "libccc/monad/list.h"



t_sint	CONCAT(List_T,_Compare)(s_list_T const* list1, s_list_T const* list2, t_sint (*compare)(T item1, T item2))
{
	t_sint	result;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list1 == list2)
		return (0);
	if (list1 == NULL || list2 == NULL || compare == NULL)
		return (ERROR);
#endif
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



t_sint	CONCAT(List_T,_Compare_N)(s_list_T const* list1, s_list_T const* list2, t_sint (*compare)(T item1, T item2), t_uint n)
{
	t_sint	result;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list1 == list2)
		return (0);
	if (list1 == NULL || list2 == NULL || compare == NULL)
		return (ERROR);
#endif
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
