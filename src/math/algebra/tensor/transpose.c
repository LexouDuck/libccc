
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



s_tensor	Tensor_Transpose(s_tensor const* tensor, t_uint const* permutation)
{
	s_tensor result = TENSOR_NULL;
	t_uint*	buffer;	// one single scratch allocation, used for 4 arrays of `order` items each
	t_uint*	perm;	// the permutation to apply (either given, or reversed axis order)
	t_uint*	dims;	// the axis sizes of the resulting tensor
	t_uint*	strides;// the strides of the resulting tensor, stored per *source* axis index
	t_uint*	coords;	// the current coordinates within the source tensor
	t_uint	order;
	t_uint	size;
	t_uint	index;
	t_uint	tmp;
	t_uint	i;
	t_uint	j;

	if CCCERROR((tensor == NULL || tensor->values == NULL), ERROR_NULLPOINTER, NULL)
		return (TENSOR_NULL);
	order = tensor->order;
	if (order == 0)
		return (Tensor_Duplicate(tensor));
	buffer = (t_uint*)Memory_New(4 * order * sizeof(t_uint));
	if CCCERROR((buffer == NULL), ERROR_ALLOCFAILURE, NULL)
		return (TENSOR_NULL);
	perm    = buffer;
	dims    = buffer + order;
	strides = buffer + order * 2;
	coords  = buffer + order * 3;
	for (i = 0; i < order; ++i)
	{
		perm[i] = (permutation ? permutation[i] : (order - 1 - i));
	}
	// validate that `perm` is a valid permutation (using `dims` as scratch space)
	for (i = 0; i < order; ++i)
		dims[i] = 0;
	for (i = 0; i < order; ++i)
	{
		if CCCERROR((perm[i] >= order), ERROR_INDEX2LARGE, 
			"permutation axis index is beyond the order of the tensor")
			{ Memory_Free(buffer); return (TENSOR_NULL); }
		if CCCERROR((dims[perm[i]] != 0), ERROR_INVALIDARGS, 
			"invalid permutation: each axis index must occur exactly once")
			{ Memory_Free(buffer); return (TENSOR_NULL); }
		dims[perm[i]] = 1;
	}
	// axis `i` of the result is axis `perm[i]` of the source
	for (i = 0; i < order; ++i)
	{
		dims[i] = tensor->dims[perm[i]];
	}
	// compute the result strides, indexed by *source* axis: for the source
	// axis `perm[i]`, moving by one means moving by the result's stride of axis `i`
	tmp = 1;
	i = order;
	while (i--)
	{
		strides[perm[i]] = tmp;
		tmp *= dims[i];
	}
	result = Tensor(order, dims, NULL);
	if (result.values == NULL)
	{
		Memory_Free(buffer);
		return (result);
	}
	// iterate over every source value (odometer-style), writing each to its permuted position
	for (i = 0; i < order; ++i)
		coords[i] = 0;
	size = Tensor_Size(tensor);
	for (i = 0; i < size; ++i)
	{
		index = 0;
		for (j = 0; j < order; ++j)
		{
			index += coords[j] * strides[j];
		}
		result.values[index] = tensor->values[i];
		j = order;
		while (j-- && (++coords[j] == tensor->dims[j]))
		{
			coords[j] = 0;
		}
	}
	Memory_Free(buffer);
	return (result);
}
