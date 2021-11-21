
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
inline
s_array_T	CONCAT(Array_Item,T_NAME)(T item)
{
	T* result = (T*)Memory_New(sizeof(T));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL),
		return ((s_array_T){ .length = 0, .items = NULL });)
	*result = item;
	return ((s_array_T){ .length = 1, .items = result });
}
