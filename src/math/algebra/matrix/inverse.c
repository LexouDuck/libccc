
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



s_matrix2d		Matrix2D_Inverse(s_matrix2d const* matrix)
{
	s_matrix2d result = MATRIX2D_NULL;
	s_vector2d u = matrix->u;
	s_vector2d v = matrix->v;
	t_float tmp;

	tmp = Matrix2D_Determinant(matrix);
	if (tmp == 0)
		return (result);
	tmp = 1 / tmp;
	result.u.x =  v.y * tmp;
	result.u.y = -u.y * tmp;
	result.v.x = -v.x * tmp;
	result.v.y =  u.x * tmp;
	return (result);
}



s_matrix3d		Matrix3D_Inverse(s_matrix3d const* matrix)
{
	s_matrix3d result = MATRIX3D_NULL;
	s_vector3d u = matrix->u;
	s_vector3d v = matrix->v;
	s_vector3d w = matrix->w;
	t_float tmp;

	tmp = Matrix3D_Determinant(matrix);
	if (tmp == 0)
		return (result);
	tmp = 1 / tmp;
	result.u.x = (v.y * w.z - w.y * v.z) * tmp;
	result.u.y = (w.y * u.z - u.y * w.z) * tmp;
	result.u.z = (u.y * v.z - v.y * u.z) * tmp;
	result.v.x = (v.z * w.x - w.z * v.x) * tmp;
	result.v.y = (w.z * u.x - u.z * w.x) * tmp;
	result.v.z = (u.z * v.x - v.z * u.x) * tmp;
	result.w.x = (v.x * w.y - w.x * v.y) * tmp;
	result.w.y = (w.x * u.y - u.x * w.y) * tmp;
	result.w.z = (u.x * v.y - v.x * u.y) * tmp;
	return (result);
}


s_matrix4d		Matrix4D_Inverse(s_matrix4d const* matrix)
{
	s_matrix4d result = MATRIX4D_NULL;
	s_vector4d u = matrix->u;
	s_vector4d v = matrix->v;
	s_vector4d w = matrix->w;
	s_vector4d t = matrix->t;
	t_float tmp;
	// 2x2 sub-determinants of the two upper rows (u,v) and the two lower rows (w,t)
	t_float s01 = u.x * v.y - u.y * v.x;
	t_float s02 = u.x * v.z - u.z * v.x;
	t_float s03 = u.x * v.t - u.t * v.x;
	t_float s12 = u.y * v.z - u.z * v.y;
	t_float s13 = u.y * v.t - u.t * v.y;
	t_float s23 = u.z * v.t - u.t * v.z;
	t_float c01 = w.x * t.y - w.y * t.x;
	t_float c02 = w.x * t.z - w.z * t.x;
	t_float c03 = w.x * t.t - w.t * t.x;
	t_float c12 = w.y * t.z - w.z * t.y;
	t_float c13 = w.y * t.t - w.t * t.y;
	t_float c23 = w.z * t.t - w.t * t.z;

	tmp = (s01 * c23 - s02 * c13 + s03 * c12 + s12 * c03 - s13 * c02 + s23 * c01);
	if (tmp == 0)
		return (result);
	tmp = 1 / tmp;
	result.u.x = (v.y * c23 - v.z * c13 + v.t * c12) * tmp;
	result.u.y = (u.z * c13 - u.y * c23 - u.t * c12) * tmp;
	result.u.z = (t.y * s23 - t.z * s13 + t.t * s12) * tmp;
	result.u.t = (w.z * s13 - w.y * s23 - w.t * s12) * tmp;
	result.v.x = (v.z * c03 - v.x * c23 - v.t * c02) * tmp;
	result.v.y = (u.x * c23 - u.z * c03 + u.t * c02) * tmp;
	result.v.z = (t.z * s03 - t.x * s23 - t.t * s02) * tmp;
	result.v.t = (w.x * s23 - w.z * s03 + w.t * s02) * tmp;
	result.w.x = (v.x * c13 - v.y * c03 + v.t * c01) * tmp;
	result.w.y = (u.y * c03 - u.x * c13 - u.t * c01) * tmp;
	result.w.z = (t.x * s13 - t.y * s03 + t.t * s01) * tmp;
	result.w.t = (w.y * s03 - w.x * s13 - w.t * s01) * tmp;
	result.t.x = (v.y * c02 - v.x * c12 - v.z * c01) * tmp;
	result.t.y = (u.x * c12 - u.y * c02 + u.z * c01) * tmp;
	result.t.z = (t.y * s02 - t.x * s12 - t.z * s01) * tmp;
	result.t.t = (w.x * s12 - w.y * s02 + w.z * s01) * tmp;
	return (result);
}


s_matrix		Matrix_Inverse(s_matrix const* matrix)
{
	s_matrix result;
	t_float*	m;
	t_float	tmp;
	t_uint	pivot;
	t_uint	n;
	t_uint	i;
	t_uint	j;
	t_uint	k;

	if CCCERROR((matrix == NULL || matrix->values == NULL), ERROR_NULLPOINTER, NULL)
		return (MATRIX_NULL);
	if CCCERROR((matrix->rows != matrix->cols), ERROR_INVALIDARGS, 
		"the matrix must be square to compute its inverse")
		return (MATRIX_NULL);
	n = matrix->rows;
	m = (t_float*)Memory_Duplicate(matrix->values, n * n * sizeof(t_float));
	if CCCERROR((m == NULL), ERROR_ALLOCFAILURE, NULL)
		return (MATRIX_NULL);
	result = Matrix_Identity(n);
	if (result.values == NULL)
	{
		Memory_Free(m);
		return (result);
	}
	// Gauss-Jordan elimination with partial pivoting: reduces `m` to the
	// identity matrix, applying every row operation to `result` as well,
	// which thereby ends up holding the inverse matrix
	for (k = 0; k < n; ++k)
	{
		pivot = k;
		for (i = k + 1; i < n; ++i)
		{
			if (Float_Abs(m[i * n + k]) > Float_Abs(m[pivot * n + k]))
				pivot = i;
		}
		if (m[pivot * n + k] == 0) // the matrix is singular: return a zero-filled matrix
		{
			Memory_Free(m);
			Memory_Clear(result.values, n * n * sizeof(t_float));
			return (result);
		}
		if (pivot != k)
		{
			for (j = 0; j < n; ++j)
			{
				tmp = m[k * n + j];
				m[k * n + j] = m[pivot * n + j];
				m[pivot * n + j] = tmp;
				tmp = result.values[k * n + j];
				result.values[k * n + j] = result.values[pivot * n + j];
				result.values[pivot * n + j] = tmp;
			}
		}
		tmp = 1 / m[k * n + k];
		for (j = 0; j < n; ++j)
		{
			m[k * n + j] *= tmp;
			result.values[k * n + j] *= tmp;
		}
		for (i = 0; i < n; ++i)
		{
			if (i == k)
				continue;
			tmp = m[i * n + k];
			if (tmp == 0)
				continue;
			for (j = 0; j < n; ++j)
			{
				m[i * n + j] -= tmp * m[k * n + j];
				result.values[i * n + j] -= tmp * result.values[k * n + j];
			}
		}
	}
	Memory_Free(m);
	return (result);
}
