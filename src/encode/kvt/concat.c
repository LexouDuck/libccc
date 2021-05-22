
#include "libccc.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_HANDLE_INCLUDE



s_kvt*	KVT_Concat(s_kvt const* a, s_kvt const* b)
{
	s_kvt*	result;
	s_kvt*	concat;

	result = KVT_Duplicate(a, TRUE);
	concat = KVT_Duplicate(b, TRUE);
	if (KVT_AddToArray_Item(result, concat))
	{
		KVT_Delete(result);
		KVT_Delete(concat);
		KVT_SetError(ERROR_KVT_ALLOCATIONFAILURE);
		return (NULL);
	}
	return (result);
}
