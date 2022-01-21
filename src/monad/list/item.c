
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*	List_Item(T)(T item)
{
	s_list(T)*	result;

	result = (s_list(T)*)Memory_New(sizeof(s_list(T)));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	result->item = item;
	return (result);
}
