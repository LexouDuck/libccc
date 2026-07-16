
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



s_tensor	Tensor_Product(s_tensor const* t1, s_tensor const* t2)
{
	s_tensor result = TENSOR_NULL;
	t_uint*	dims;
	t_uint	order;
	t_uint	size1;
	t_uint	size2;
	t_uint	i;
	t_uint	j;

	if CCCERROR((t1 == NULL || t2 == NULL), ERROR_NULLPOINTER, NULL)
		return (TENSOR_NULL);
	if CCCERROR((t1->values == NULL || t2->values == NULL), ERROR_NULLPOINTER, NULL)
		return (TENSOR_NULL);
	order = t1->order + t2->order;
	dims = NULL;
	if (order > 0)
	{
		dims = (t_uint*)Memory_New(order * sizeof(t_uint));
		if CCCERROR((dims == NULL), ERROR_ALLOCFAILURE, NULL)
			return (TENSOR_NULL);
		for (i = 0; i < t1->order; ++i)
			dims[i] = t1->dims[i];
		for (i = 0; i < t2->order; ++i)
			dims[t1->order + i] = t2->dims[i];
	}
	result = Tensor(order, dims, NULL);
	if (dims != NULL)
		Memory_Free(dims);
	if (result.values == NULL)
		return (result);
	// with row-major storage, concatenating the axes of `t1` and `t2` means:
	// `result.values[i * size2 + j] = t1->values[i] * t2->values[j]`
	size1 = Tensor_Size(t1);
	size2 = Tensor_Size(t2);
	for (i = 0; i < size1; ++i)
	for (j = 0; j < size2; ++j)
	{
		result.values[i * size2 + j] = t1->values[i] * t2->values[j];
	}
	return (result);
}
