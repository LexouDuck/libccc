
#include "libccc/memory.h"



void**		PointerArray_New(t_size n)
{
	void**		result;

	if (!(result = (void**)c_memnew(sizeof(void**) * (n + 1))))
		return (NULL);
	return (result);
}
