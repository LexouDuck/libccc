
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



s_matrix2d	Matrix2D_Transpose(s_matrix2d const* matrix)
{
	s_matrix2d result;

	result.u.x = matrix->u.x;
	result.u.y = matrix->v.x;

	result.v.x = matrix->u.y;
	result.v.y = matrix->v.y;
	return (result);
}



s_matrix3d	Matrix3D_Transpose(s_matrix3d const* matrix)
{
	s_matrix3d result;

	result.u.x = matrix->u.x;
	result.u.y = matrix->v.x;
	result.u.z = matrix->w.x;

	result.v.x = matrix->u.y;
	result.v.y = matrix->v.y;
	result.v.z = matrix->w.y;

	result.w.x = matrix->u.z;
	result.w.y = matrix->v.z;
	result.w.z = matrix->w.z;
	return (result);
}


s_matrix4d	Matrix4D_Transpose(s_matrix4d const* matrix)
{
	s_matrix4d result;

	result.u.x = matrix->u.x;
	result.u.y = matrix->v.x;
	result.u.z = matrix->w.x;
	result.u.t = matrix->t.x;

	result.v.x = matrix->u.y;
	result.v.y = matrix->v.y;
	result.v.z = matrix->w.y;
	result.v.t = matrix->t.y;

	result.w.x = matrix->u.z;
	result.w.y = matrix->v.z;
	result.w.z = matrix->w.z;
	result.w.t = matrix->t.z;

	result.t.x = matrix->u.t;
	result.t.y = matrix->v.t;
	result.t.z = matrix->w.t;
	result.t.t = matrix->t.t;
	return (result);
}


s_matrix	Matrix_Transpose(s_matrix const* matrix)
{
	s_matrix result;
	t_uint i;
	t_uint j;

	if CCCERROR((matrix == NULL), ERROR_NULLPOINTER, NULL)
		return (MATRIX_NULL);
	result = Matrix(matrix->cols, matrix->rows, NULL);
	if (result.values == NULL)
		return (result);
	for (i = 0; i < matrix->rows; ++i)
	for (j = 0; j < matrix->cols; ++j)
	{
		result.values[j * result.cols + i] = matrix->values[i * matrix->cols + j];
	}
	return (result);
}
