
#include "libccc/memory.h"
#include "libccc/monad/list.h"


_GENERIC()
s_list_T*	CONCAT(List_Item,T_NAME)(T item)
{
	s_list_T*	result;

	result = (s_list_T*)Memory_New(sizeof(s_list_T));
	if (result == NULL)
		return (NULL);
	result->item = item;
	return (result);
}
