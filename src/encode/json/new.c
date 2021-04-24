
#include "libccc/memory.h"
#include "libccc/encode/json.h"



inline s_json* JSON_New_Item(void)
{
	return ((s_json*)Memory_New(sizeof(s_json)));
}
