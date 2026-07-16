
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



s_tensor	Tensor_Trace(s_tensor const* tensor, t_uint axis1, t_uint axis2)
{
	s_tensor result = TENSOR_NULL;
	t_uint*	dims;
	t_float	sum;
	t_uint	order;
	t_uint	axis_lo;	// the smaller of the two axis indices to trace over
	t_uint	axis_hi;	// the larger of the two axis indices to trace over
	t_uint	n;			// the size of the two traced axes
	t_uint	stride_lo;	// the distance (in values) between two consecutive indices along `axis_lo`
	t_uint	stride_hi;	// the distance (in values) between two consecutive indices along `axis_hi`
	t_uint	size;		// the amount of kept-axes value combinations (ie: the total size, divided by `n * n`)
	t_uint	base;
	t_uint	i;
	t_uint	a;
	t_uint	k;

	if CCCERROR((tensor == NULL || tensor->values == NULL), ERROR_NULLPOINTER, NULL)
		return (TENSOR_NULL);
	if CCCERROR((axis1 >= tensor->order), ERROR_INDEX2LARGE, 
		"axis index is beyond the order of the tensor")
		return (TENSOR_NULL);
	if CCCERROR((axis2 >= tensor->order), ERROR_INDEX2LARGE, 
		"axis index is beyond the order of the tensor")
		return (TENSOR_NULL);
	if CCCERROR((axis1 == axis2), ERROR_INVALIDARGS, 
		"the two axes to trace over must be different")
		return (TENSOR_NULL);
	if CCCERROR((tensor->dims[axis1] != tensor->dims[axis2]), ERROR_INVALIDARGS, 
		"the two axes to trace over must have the same size")
		return (TENSOR_NULL);
	axis_lo = (axis1 < axis2 ? axis1 : axis2);
	axis_hi = (axis1 < axis2 ? axis2 : axis1);
	order = tensor->order - 2;
	dims = NULL;
	if (order > 0)
	{
		dims = (t_uint*)Memory_New(order * sizeof(t_uint));
		if CCCERROR((dims == NULL), ERROR_ALLOCFAILURE, NULL)
			return (TENSOR_NULL);
		k = 0;
		for (i = 0; i < tensor->order; ++i)
		{
			if (i != axis_lo && i != axis_hi)
				dims[k++] = tensor->dims[i];
		}
	}
	result = Tensor(order, dims, NULL);
	if (dims != NULL)
		Memory_Free(dims);
	if (result.values == NULL)
		return (result);
	n = tensor->dims[axis_lo];
	stride_lo = 1;
	for (i = axis_lo + 1; i < tensor->order; ++i)
		stride_lo *= tensor->dims[i];
	stride_hi = 1;
	for (i = axis_hi + 1; i < tensor->order; ++i)
		stride_hi *= tensor->dims[i];
	size = Tensor_Size(tensor) / (n * n);
	// for each combination of kept-axes indices `a`, the flat offset of the
	// value with both traced axes set to `k` is `base + k * (stride_lo + stride_hi)`,
	// where `base` re-inserts a gap for each of the two traced axes, innermost first
	for (a = 0; a < size; ++a)
	{
		base = (a / stride_hi) * (stride_hi * n) + (a % stride_hi);
		base = (base / stride_lo) * (stride_lo * n) + (base % stride_lo);
		sum = 0;
		for (k = 0; k < n; ++k)
		{
			sum += tensor->values[base + k * (stride_lo + stride_hi)];
		}
		result.values[a] = sum;
	}
	return (result);
}
