
#include "libccc/memory.h"
#include "libccc/generic/set.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_set(T)*	Set_New(T)(void)
{
	s_set(T)*	result;

	result = (s_set(T)*)Memory_New(sizeof(s_set(T)));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result->length = 0;
	result->items = NULL;
	return (result);
}



_GENERIC()
s_set(T)*	Set_Item(T)(T item)
{
	s_set(T)*	result;

	result = Set_New(T)();
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if (Set_Add(T)(result, item) == NULL)
	{
		Set_Free(T)(result);
		return (NULL);
	}
	return (result);
}
