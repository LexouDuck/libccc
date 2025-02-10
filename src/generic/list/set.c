
#include "libccc/generic/list.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
T*	List_Set(T)(s_list(T)* list, t_uint index, T item)
{
	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (NULL);
	for (t_uint	i = 0; i < index; ++i)
	{
		if CCCERROR((list->next == NULL), ERROR_INDEX2LARGE, 
			"index given (" SF_UINT ") is beyond end of list (length: " SF_UINT ")",
			index, List_Length(T)(list))
			return (NULL);
		list = list->next;
	}
	list->item = item;
	return ((T*)&list->item);
}
