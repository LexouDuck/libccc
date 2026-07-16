
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



void	Tensor_Free(s_tensor* tensor)
{
	if CCCERROR((tensor == NULL), ERROR_NULLPOINTER, NULL)
		return;
	if (tensor->dims != NULL)
		Memory_Free(tensor->dims);
	if (tensor->values != NULL)
		Memory_Free(tensor->values);
	tensor->dims = NULL;
	tensor->values = NULL;
	tensor->order = 0;
}



void	Tensor_Delete(s_tensor* *a_tensor)
{
	if CCCERROR((a_tensor == NULL), ERROR_NULLPOINTER, NULL)
		return;
	if (*a_tensor == NULL)
		return;
	Tensor_Free(*a_tensor);
	Memory_Delete((void**)a_tensor);
}
