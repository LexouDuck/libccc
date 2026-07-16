
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
t_float	Matrix2D_Determinant(s_matrix2d const* matrix)
{
	return (
		matrix->u.x * matrix->v.y -
		matrix->u.y * matrix->v.x);
}



_INLINE()
t_float	Matrix3D_Determinant(s_matrix3d const* matrix)
{
	return (
		matrix->u.x * (matrix->v.y * matrix->w.z - matrix->v.z * matrix->w.y) -
		matrix->u.y * (matrix->v.x * matrix->w.z - matrix->v.z * matrix->w.x) +
		matrix->u.z * (matrix->v.x * matrix->w.y - matrix->v.y * matrix->w.x));
}


t_float	Matrix4D_Determinant(s_matrix4d const* matrix)
{
	s_vector4d u = matrix->u;
	s_vector4d v = matrix->v;
	s_vector4d w = matrix->w;
	s_vector4d t = matrix->t;

	return (
		(u.x * v.y - u.y * v.x) * (w.z * t.t - w.t * t.z) -
		(u.x * v.z - u.z * v.x) * (w.y * t.t - w.t * t.y) +
		(u.x * v.t - u.t * v.x) * (w.y * t.z - w.z * t.y) +
		(u.y * v.z - u.z * v.y) * (w.x * t.t - w.t * t.x) -
		(u.y * v.t - u.t * v.y) * (w.x * t.z - w.z * t.x) +
		(u.z * v.t - u.t * v.z) * (w.x * t.y - w.y * t.x));
}


t_float	Matrix_Determinant(s_matrix const* matrix)
{
	t_float*	m;
	t_float	result;
	t_float	tmp;
	t_uint	pivot;
	t_uint	n;
	t_uint	i;
	t_uint	j;
	t_uint	k;

	if CCCERROR((matrix == NULL || matrix->values == NULL), ERROR_NULLPOINTER, NULL)
		return (0);
	if CCCERROR((matrix->rows != matrix->cols), ERROR_INVALIDARGS, 
		"the matrix must be square to compute its determinant")
		return (0);
	n = matrix->rows;
	m = (t_float*)Memory_Duplicate(matrix->values, n * n * sizeof(t_float));
	if CCCERROR((m == NULL), ERROR_ALLOCFAILURE, NULL)
		return (0);
	// LU decomposition with partial pivoting: the determinant is the product of the pivots
	result = 1;
	for (k = 0; k < n; ++k)
	{
		pivot = k;
		for (i = k + 1; i < n; ++i)
		{
			if (Float_Abs(m[i * n + k]) > Float_Abs(m[pivot * n + k]))
				pivot = i;
		}
		if (m[pivot * n + k] == 0)
		{
			Memory_Free(m);
			return (0);
		}
		if (pivot != k)
		{
			for (j = 0; j < n; ++j)
			{
				tmp = m[k * n + j];
				m[k * n + j] = m[pivot * n + j];
				m[pivot * n + j] = tmp;
			}
			result = -result;
		}
		result *= m[k * n + k];
		for (i = k + 1; i < n; ++i)
		{
			tmp = m[i * n + k] / m[k * n + k];
			for (j = k + 1; j < n; ++j)
			{
				m[i * n + j] -= tmp * m[k * n + j];
			}
		}
	}
	Memory_Free(m);
	return (result);
}
