
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_sint	List_Compare(T)(s_list(T) const* list1, s_list(T) const* list2, t_sint (*compare)(T item1, T item2))
{
	t_sint	result;

	if CCCERROR((compare == NULL), ERROR_NULLPOINTER, "compare() function given is NULL")
		return (ERROR);
	if (list1 == list2)
		return (0);
	if CCCERROR((list1 == NULL), ERROR_NULLPOINTER, NULL) return (ERROR);
	if CCCERROR((list2 == NULL), ERROR_NULLPOINTER, NULL) return (ERROR);
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
t_sint	List_Compare_N(T)(s_list(T) const* list1, s_list(T) const* list2, t_sint (*compare)(T item1, T item2), t_uint n)
{
	t_sint	result;

	if CCCERROR((compare == NULL), ERROR_NULLPOINTER, "compare() function given is NULL")
		return (ERROR);
	if (list1 == list2)
		return (0);
	if CCCERROR((list1 == NULL), ERROR_NULLPOINTER, NULL) return (ERROR);
	if CCCERROR((list2 == NULL), ERROR_NULLPOINTER, NULL) return (ERROR);
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
