
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



s_tensor	Tensor_Duplicate(s_tensor const* tensor)
{
	if CCCERROR((tensor == NULL), ERROR_NULLPOINTER, NULL)
		return (TENSOR_NULL);
	return (Tensor(tensor->order, tensor->dims, tensor->values));
}
