
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



s_matrix2d	Matrix2D_Multiply(s_matrix2d const* m1, s_matrix2d const* m2)
{
	s_matrix2d result;
	s_vector2d tmp;

	tmp = m1->u;
	result.u = (s_vector2d)
	{
		(tmp.x * m2->u.x) + (tmp.y * m2->v.x),
		(tmp.x * m2->u.y) + (tmp.y * m2->v.y),
	};
	tmp = m1->v;
	result.v = (s_vector2d)
	{
		(tmp.x * m2->u.x) + (tmp.y * m2->v.x),
		(tmp.x * m2->u.y) + (tmp.y * m2->v.y),
	};
	return (result);
}



s_matrix3d	Matrix3D_Multiply(s_matrix3d const* m1, s_matrix3d const* m2)
{
	s_matrix3d result;
	s_vector3d tmp;

	tmp = m1->u;
	result.u = (s_vector3d)
	{
		(tmp.x * m2->u.x) + (tmp.y * m2->v.x) + (tmp.z * m2->w.x),
		(tmp.x * m2->u.y) + (tmp.y * m2->v.y) + (tmp.z * m2->w.y),
		(tmp.x * m2->u.z) + (tmp.y * m2->v.z) + (tmp.z * m2->w.z),
	};
	tmp = m1->v;
	result.v = (s_vector3d)
	{
		(tmp.x * m2->u.x) + (tmp.y * m2->v.x) + (tmp.z * m2->w.x),
		(tmp.x * m2->u.y) + (tmp.y * m2->v.y) + (tmp.z * m2->w.y),
		(tmp.x * m2->u.z) + (tmp.y * m2->v.z) + (tmp.z * m2->w.z),
	};
	tmp = m1->w;
	result.w = (s_vector3d)
	{
		(tmp.x * m2->u.x) + (tmp.y * m2->v.x) + (tmp.z * m2->w.x),
		(tmp.x * m2->u.y) + (tmp.y * m2->v.y) + (tmp.z * m2->w.y),
		(tmp.x * m2->u.z) + (tmp.y * m2->v.z) + (tmp.z * m2->w.z),
	};
	return (result);
}


s_matrix4d	Matrix4D_Multiply(s_matrix4d const* m1, s_matrix4d const* m2)
{
	s_matrix4d result;
	s_vector4d tmp;

	tmp = m1->u;
	result.u = (s_vector4d)
	{
		(tmp.x * m2->u.x) + (tmp.y * m2->v.x) + (tmp.z * m2->w.x) + (tmp.t * m2->t.x),
		(tmp.x * m2->u.y) + (tmp.y * m2->v.y) + (tmp.z * m2->w.y) + (tmp.t * m2->t.y),
		(tmp.x * m2->u.z) + (tmp.y * m2->v.z) + (tmp.z * m2->w.z) + (tmp.t * m2->t.z),
		(tmp.x * m2->u.t) + (tmp.y * m2->v.t) + (tmp.z * m2->w.t) + (tmp.t * m2->t.t),
	};
	tmp = m1->v;
	result.v = (s_vector4d)
	{
		(tmp.x * m2->u.x) + (tmp.y * m2->v.x) + (tmp.z * m2->w.x) + (tmp.t * m2->t.x),
		(tmp.x * m2->u.y) + (tmp.y * m2->v.y) + (tmp.z * m2->w.y) + (tmp.t * m2->t.y),
		(tmp.x * m2->u.z) + (tmp.y * m2->v.z) + (tmp.z * m2->w.z) + (tmp.t * m2->t.z),
		(tmp.x * m2->u.t) + (tmp.y * m2->v.t) + (tmp.z * m2->w.t) + (tmp.t * m2->t.t),
	};
	tmp = m1->w;
	result.w = (s_vector4d)
	{
		(tmp.x * m2->u.x) + (tmp.y * m2->v.x) + (tmp.z * m2->w.x) + (tmp.t * m2->t.x),
		(tmp.x * m2->u.y) + (tmp.y * m2->v.y) + (tmp.z * m2->w.y) + (tmp.t * m2->t.y),
		(tmp.x * m2->u.z) + (tmp.y * m2->v.z) + (tmp.z * m2->w.z) + (tmp.t * m2->t.z),
		(tmp.x * m2->u.t) + (tmp.y * m2->v.t) + (tmp.z * m2->w.t) + (tmp.t * m2->t.t),
	};
	tmp = m1->t;
	result.t = (s_vector4d)
	{
		(tmp.x * m2->u.x) + (tmp.y * m2->v.x) + (tmp.z * m2->w.x) + (tmp.t * m2->t.x),
		(tmp.x * m2->u.y) + (tmp.y * m2->v.y) + (tmp.z * m2->w.y) + (tmp.t * m2->t.y),
		(tmp.x * m2->u.z) + (tmp.y * m2->v.z) + (tmp.z * m2->w.z) + (tmp.t * m2->t.z),
		(tmp.x * m2->u.t) + (tmp.y * m2->v.t) + (tmp.z * m2->w.t) + (tmp.t * m2->t.t),
	};
	return (result);
}


s_matrix	Matrix_Multiply(s_matrix const* m1, s_matrix const* m2)
{
	s_matrix result;
	t_float tmp;
	t_uint i;
	t_uint j;
	t_uint k;

	if CCCERROR((m1 == NULL || m2 == NULL), ERROR_NULLPOINTER, NULL)
		return (MATRIX_NULL);
	if CCCERROR((m1->cols != m2->rows), ERROR_INVALIDARGS, 
		"the first matrix must have as many columns as the second matrix has rows")
		return (MATRIX_NULL);
	result = Matrix(m1->rows, m2->cols, NULL);
	if (result.values == NULL)
		return (result);
	for (i = 0; i < m1->rows; ++i)
	for (k = 0; k < m1->cols; ++k)
	{
		tmp = m1->values[i * m1->cols + k];
		for (j = 0; j < m2->cols; ++j)
		{
			result.values[i * result.cols + j] += (tmp * m2->values[k * m2->cols + j]);
		}
	}
	return (result);
}
