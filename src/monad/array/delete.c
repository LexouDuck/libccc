
#include "libccc/memory.h"
#include "libccc/monad/array.h"


_GENERIC()
void	CONCAT(Array_Delete,T_NAME)(s_array_T* array)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL)
		return;
#endif
	Memory_Free(array->items);
	array->items = NULL;
	array->length = 0;
}
