
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



s_tensor	Tensor_Reshape(s_tensor const* tensor, t_uint order, t_uint const* dims)
{
	t_uint size;
	t_uint i;

	if CCCERROR((tensor == NULL || tensor->values == NULL), ERROR_NULLPOINTER, NULL)
		return (TENSOR_NULL);
	if CCCERROR((order > 0 && dims == NULL), ERROR_NULLPOINTER, 
		"array of axis sizes given is NULL")
		return (TENSOR_NULL);
	size = 1;
	for (i = 0; i < order; ++i)
	{
		size *= dims[i];
	}
	if CCCERROR((size != Tensor_Size(tensor)), ERROR_INVALIDARGS, 
		"the new dimensions must hold the same total amount of values as the tensor")
		return (TENSOR_NULL);
	return (Tensor(order, dims, tensor->values));
}
