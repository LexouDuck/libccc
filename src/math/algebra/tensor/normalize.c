
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



s_tensor	Tensor_Normalize(s_tensor const* tensor)
{
	s_tensor result;
	t_float	norm;
	t_uint size;
	t_uint i;

	if CCCERROR((tensor == NULL), ERROR_NULLPOINTER, NULL)
		return (TENSOR_NULL);
	result = Tensor(tensor->order, tensor->dims, NULL);
	if (result.values == NULL)
		return (result);
	norm = Tensor_Norm(tensor);
	if (norm > 0)
	{
		norm = 1 / Float_SquareRoot(norm); // TODO InvSqRt function ?
		size = Tensor_Size(tensor);
		for (i = 0; i < size; ++i)
		{
			result.values[i] = tensor->values[i] * norm;
		}
	}
	return (result);
}
