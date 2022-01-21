
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
inline
s_array(T)	Array_Item(T)(T item)
{
	T* result = (T*)Memory_New(sizeof(T));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL),
		return ((s_array(T)){ .length = 0, .items = NULL });)
	*result = item;
	return ((s_array(T)){ .length = 1, .items = result });
}
