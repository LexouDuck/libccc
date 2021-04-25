
#include "libccc/memory.h"
#include "libccc/encode/common.h"



inline s_kvt* KVT_New_Item(void)
{
	return ((s_kvt*)Memory_New(sizeof(s_kvt)));
}
