
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



s_tensor	Tensor_FromVector(s_vector const* vector)
{
	t_uint dims[1];

	if CCCERROR((vector == NULL || vector->values == NULL), ERROR_NULLPOINTER, NULL)
		return (TENSOR_NULL);
	dims[0] = vector->dims;
	return (Tensor(1, dims, vector->values));
}



s_tensor	Tensor_FromMatrix(s_matrix const* matrix)
{
	t_uint dims[2];

	if CCCERROR((matrix == NULL || matrix->values == NULL), ERROR_NULLPOINTER, NULL)
		return (TENSOR_NULL);
	dims[0] = matrix->rows;
	dims[1] = matrix->cols;
	return (Tensor(2, dims, matrix->values));
}



s_vector	Tensor_ToVector(s_tensor const* tensor)
{
	if CCCERROR((tensor == NULL || tensor->values == NULL), ERROR_NULLPOINTER, NULL)
		return (VECTOR_NULL);
	if CCCERROR((tensor->order != 1), ERROR_INVALIDARGS, 
		"the tensor must have an order of exactly 1 to be converted to a vector")
		return (VECTOR_NULL);
	return (Vector(tensor->dims[0], tensor->values));
}



s_matrix	Tensor_ToMatrix(s_tensor const* tensor)
{
	if CCCERROR((tensor == NULL || tensor->values == NULL), ERROR_NULLPOINTER, NULL)
		return (MATRIX_NULL);
	if CCCERROR((tensor->order != 2), ERROR_INVALIDARGS, 
		"the tensor must have an order of exactly 2 to be converted to a matrix")
		return (MATRIX_NULL);
	return (Matrix(tensor->dims[0], tensor->dims[1], tensor->values));
}
