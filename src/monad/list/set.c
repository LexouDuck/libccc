
#include "libccc/monad/list.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
T*	List_Set(T)(s_list(T)* list, t_uint index, T item)
{
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	for (t_uint	i = 0; i < index; ++i)
	{
		HANDLE_ERROR_SF(INDEX2LARGE, (list->next == NULL), return (NULL);,
			"index given ("SF_UINT") is beyond end of list (length: "SF_UINT")",
			index, List_Length(T)(list))
		list = list->next;
	}
	list->item = item;
	return ((T*)&list->item);
}
