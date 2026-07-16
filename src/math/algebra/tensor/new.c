
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



s_tensor	Tensor(t_uint order, t_uint const* dims, t_float const* values)
{
	s_tensor result = TENSOR_NULL;
	t_uint size;
	t_uint i;

	if (order == 0)
	{
		result.values = (t_float*)Memory_New(sizeof(t_float));
		if CCCERROR((result.values == NULL), ERROR_ALLOCFAILURE, NULL)
			return (TENSOR_NULL);
		if (values != NULL)
			result.values[0] = values[0];
		return (result);
	}
	if CCCERROR((dims == NULL), ERROR_NULLPOINTER, 
		"array of axis sizes given is NULL")
		return (TENSOR_NULL);
	size = 1;
	for (i = 0; i < order; ++i)
	{
		if (dims[i] == 0)
			return (TENSOR_NULL);
		size *= dims[i];
	}
	result.dims = (t_uint*)Memory_Duplicate(dims, order * sizeof(t_uint));
	if CCCERROR((result.dims == NULL), ERROR_ALLOCFAILURE, NULL)
		return (TENSOR_NULL);
	result.values = (t_float*)Memory_New(size * sizeof(t_float));
	if CCCERROR((result.values == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Free(result.dims);
		return (TENSOR_NULL);
	}
	result.order = order;
	if (values != NULL)
		Memory_Copy(result.values, values, size * sizeof(t_float));
	return (result);
}



s_tensor*	Tensor_New(t_uint order, t_uint const* dims, t_float const* values)
{
	s_tensor* result;

	result = (s_tensor*)Memory_New(sizeof(s_tensor));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	*result = Tensor(order, dims, values);
	if CCCERROR((result->values == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Delete((void**)&result);
		return (NULL);
	}
	return (result);
}
