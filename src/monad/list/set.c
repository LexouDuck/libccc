
#include "libccc/monad/list.h"
#include "libccc/string.h"

#include LIBCONFIG_HANDLE_INCLUDE



_GENERIC()
T*	CONCAT(List_Set,T_NAME)(s_list_T* list, t_uint index, T item)
{
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	for (t_uint	i = 0; i < index; ++i)
	{
		HANDLE_ERROR_SF(INDEX2LARGE, (list->next == NULL), return (NULL);,
			", index given ("SF_UINT") is beyond end of list (length: "SF_UINT")",
			index, CONCAT(List_Length,T_NAME)(list))
		list = list->next;
	}
	list->item = item;
	return ((T*)&list->item);
}
