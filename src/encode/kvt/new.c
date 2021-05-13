
#include "libccc/memory.h"
#include "libccc/encode/common.h"



s_kvt*	KVT_Item(void)
{
	s_kvt*	result = (s_kvt*)Memory_New(sizeof(s_kvt));
	if (result == NULL)
	{
		KVT_SetError(ERROR_KVT_ALLOCATIONFAILURE);
	}
	return (result);
}
