
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



s_tensor	Tensor_Scale(s_tensor const* tensor, t_float scale)
{
	s_tensor result;
	t_uint size;
	t_uint i;

	if CCCERROR((tensor == NULL), ERROR_NULLPOINTER, NULL)
		return (TENSOR_NULL);
	result = Tensor(tensor->order, tensor->dims, NULL);
	if (result.values == NULL)
		return (result);
	size = Tensor_Size(tensor);
	for (i = 0; i < size; ++i)
	{
		result.values[i] = tensor->values[i] * scale;
	}
	return (result);
}
