
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



s_tensor	Tensor_Contract(s_tensor const* t1, t_uint axis1, s_tensor const* t2, t_uint axis2)
{
	s_tensor result = TENSOR_NULL;
	t_uint*	dims;
	t_float	sum;
	t_uint	order;
	t_uint	n;			// the size of the shared/contracted axis
	t_uint	stride1;	// the distance (in values) between two consecutive indices along `axis1`, within `t1`
	t_uint	stride2;	// the distance (in values) between two consecutive indices along `axis2`, within `t2`
	t_uint	size1;		// the amount of kept-axes value combinations of `t1` (ie: its total size, divided by `n`)
	t_uint	size2;		// the amount of kept-axes value combinations of `t2` (ie: its total size, divided by `n`)
	t_uint	base1;
	t_uint	base2;
	t_uint	i;
	t_uint	a;
	t_uint	b;
	t_uint	k;

	if CCCERROR((t1 == NULL || t2 == NULL), ERROR_NULLPOINTER, NULL)
		return (TENSOR_NULL);
	if CCCERROR((t1->values == NULL || t2->values == NULL), ERROR_NULLPOINTER, NULL)
		return (TENSOR_NULL);
	if CCCERROR((axis1 >= t1->order), ERROR_INDEX2LARGE, 
		"axis index is beyond the order of the first tensor")
		return (TENSOR_NULL);
	if CCCERROR((axis2 >= t2->order), ERROR_INDEX2LARGE, 
		"axis index is beyond the order of the second tensor")
		return (TENSOR_NULL);
	if CCCERROR((t1->dims[axis1] != t2->dims[axis2]), ERROR_INVALIDARGS, 
		"the two axes to contract must have the same size")
		return (TENSOR_NULL);
	order = t1->order + t2->order - 2;
	dims = NULL;
	if (order > 0)
	{
		dims = (t_uint*)Memory_New(order * sizeof(t_uint));
		if CCCERROR((dims == NULL), ERROR_ALLOCFAILURE, NULL)
			return (TENSOR_NULL);
		k = 0;
		for (i = 0; i < t1->order; ++i)
		{
			if (i != axis1)
				dims[k++] = t1->dims[i];
		}
		for (i = 0; i < t2->order; ++i)
		{
			if (i != axis2)
				dims[k++] = t2->dims[i];
		}
	}
	result = Tensor(order, dims, NULL);
	if (dims != NULL)
		Memory_Free(dims);
	if (result.values == NULL)
		return (result);
	n = t1->dims[axis1];
	stride1 = 1;
	for (i = axis1 + 1; i < t1->order; ++i)
		stride1 *= t1->dims[i];
	stride2 = 1;
	for (i = axis2 + 1; i < t2->order; ++i)
		stride2 *= t2->dims[i];
	size1 = Tensor_Size(t1) / n;
	size2 = Tensor_Size(t2) / n;
	// for each combination of kept-axes indices `a` of `t1` and `b` of `t2`,
	// the flat offset of the value with the contracted axis set to `k` is
	// `base + k * stride`, where `base` re-inserts a gap for the contracted axis
	for (a = 0; a < size1; ++a)
	{
		base1 = (a / stride1) * (stride1 * n) + (a % stride1);
		for (b = 0; b < size2; ++b)
		{
			base2 = (b / stride2) * (stride2 * n) + (b % stride2);
			sum = 0;
			for (k = 0; k < n; ++k)
			{
				sum += (t1->values[base1 + k * stride1] * t2->values[base2 + k * stride2]);
			}
			result.values[a * size2 + b] = sum;
		}
	}
	return (result);
}
