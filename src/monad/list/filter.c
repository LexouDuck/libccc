
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*	List_Filter(T)(s_list(T) const* list, t_bool (*filter)(T item))
{
	s_list(T)*	result = NULL;
	s_list(T)*	item;

	if CCCERROR((filter == NULL), ERROR_NULLPOINTER, "filter() function given is NULL")
		return (NULL);
	if CCCERROR((list == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	while (list)
	{
		if (filter(list->item))
		{
			item = List_Item(T)(list->item);
			List_Append(T)(result, item);
		}
		list = list->next;
	}
	return (result);
}



_GENERIC()
s_list(T)*	List_Filter_I(T)(s_list(T) const* list, t_bool (*filter)(T item, t_uint index))
{
	s_list(T)*	result = NULL;
	s_list(T)*	item;
	t_uint	i;

	if CCCERROR((filter == NULL), ERROR_NULLPOINTER, "filter() function given is NULL")
		return (NULL);
	if CCCERROR((list == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	i = 0;
	while (list)
	{
		if (filter(list->item, i))
		{
			item = List_Item(T)(list->item);
			List_Append(T)(result, item);
		}
		list = list->next;
		++i;
	}
	return (result);
}
