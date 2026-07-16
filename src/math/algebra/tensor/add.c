
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



//! Returns `TRUE` if the two given tensors have the same order and axis sizes
static
t_bool	Tensor_SameDims(s_tensor const* t1, s_tensor const* t2)
{
	t_uint i;

	if (t1->order != t2->order)
		return (FALSE);
	for (i = 0; i < t1->order; ++i)
	{
		if (t1->dims[i] != t2->dims[i])
			return (FALSE);
	}
	return (TRUE);
}



s_tensor	Tensor_Add(s_tensor const* t1, s_tensor const* t2)
{
	s_tensor result;
	t_uint size;
	t_uint i;

	if CCCERROR((t1 == NULL || t2 == NULL), ERROR_NULLPOINTER, NULL)
		return (TENSOR_NULL);
	if CCCERROR((!Tensor_SameDims(t1, t2)), ERROR_INVALIDARGS, 
		"tensors must have the same order and dimensions to be added")
		return (TENSOR_NULL);
	result = Tensor(t1->order, t1->dims, NULL);
	if (result.values == NULL)
		return (result);
	size = Tensor_Size(t1);
	for (i = 0; i < size; ++i)
	{
		result.values[i] = t1->values[i] + t2->values[i];
	}
	return (result);
}
