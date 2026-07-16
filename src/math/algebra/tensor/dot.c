
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



t_float		Tensor_Dot(s_tensor const* t1, s_tensor const* t2)
{
	t_float	result = 0;
	t_uint size;
	t_uint i;

	if CCCERROR((t1 == NULL || t2 == NULL), ERROR_NULLPOINTER, NULL)
		return (0);
	if CCCERROR((t1->order != t2->order), ERROR_INVALIDARGS, 
		"tensors must have the same order and dimensions to compute a dot product")
		return (0);
	for (i = 0; i < t1->order; ++i)
	{
		if CCCERROR((t1->dims[i] != t2->dims[i]), ERROR_INVALIDARGS, 
			"tensors must have the same order and dimensions to compute a dot product")
			return (0);
	}
	size = Tensor_Size(t1);
	for (i = 0; i < size; ++i)
	{
		result += (t1->values[i] * t2->values[i]);
	}
	return (result);
}
