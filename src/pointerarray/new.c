
#include "libccc/memory.h"
#include "libccc/pointerarray.h"



void**		PointerArray_New(t_size n)
{
	void**		result;

	if (!(result = (void**)Memory_New(sizeof(void**) * (n + 1))))
		return (NULL);
	return (result);
}
