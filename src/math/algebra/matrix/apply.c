
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



s_vector2d	Matrix2D_Apply(s_matrix2d const* matrix, s_vector2d const* vector)
{
	s_vector2d result = VECTOR2D_NULL;
	s_vector2d const* tmp;
	t_float x;
	t_float y;

	x = vector->x;
	y = vector->y;
	tmp = &matrix->u;
	result.x += (x * tmp->x);
	result.y += (x * tmp->y);
	tmp = &matrix->v;
	result.x += (y * tmp->x);
	result.y += (y * tmp->y);
	return (result);
}

s_vector3d	Matrix3D_Apply(s_matrix3d const* matrix, s_vector3d const* vector)
{
	s_vector3d result = VECTOR3D_NULL;
	s_vector3d const* tmp;
	t_float x;
	t_float y;
	t_float z;

	x = vector->x;
	y = vector->y;
	z = vector->z;
	tmp = &matrix->u;
	result.x += (x * tmp->x);
	result.y += (x * tmp->y);
	result.z += (x * tmp->z);
	tmp = &matrix->v;
	result.x += (y * tmp->x);
	result.y += (y * tmp->y);
	result.z += (y * tmp->z);
	tmp = &matrix->w;
	result.x += (z * tmp->x);
	result.y += (z * tmp->y);
	result.z += (z * tmp->z);
	return (result);
}


s_vector4d	Matrix4D_Apply(s_matrix4d const* matrix, s_vector4d const* vector)
{
	s_vector4d result = VECTOR4D_NULL;
	s_vector4d const* tmp;
	t_float x;
	t_float y;
	t_float z;
	t_float t;

	x = vector->x;
	y = vector->y;
	z = vector->z;
	t = vector->t;
	tmp = &matrix->u;
	result.x += (x * tmp->x);
	result.y += (x * tmp->y);
	result.z += (x * tmp->z);
	result.t += (x * tmp->t);
	tmp = &matrix->v;
	result.x += (y * tmp->x);
	result.y += (y * tmp->y);
	result.z += (y * tmp->z);
	result.t += (y * tmp->t);
	tmp = &matrix->w;
	result.x += (z * tmp->x);
	result.y += (z * tmp->y);
	result.z += (z * tmp->z);
	result.t += (z * tmp->t);
	tmp = &matrix->t;
	result.x += (t * tmp->x);
	result.y += (t * tmp->y);
	result.z += (t * tmp->z);
	result.t += (t * tmp->t);
	return (result);
}


s_vector	Matrix_Apply(s_matrix const* matrix, s_vector const* vector)
{
	s_vector result;
	t_float tmp;
	t_uint i;
	t_uint j;

	if CCCERROR((matrix == NULL || vector == NULL), ERROR_NULLPOINTER, NULL)
		return (VECTOR_NULL);
	if CCCERROR((vector->dims != matrix->rows), ERROR_INVALIDARGS, 
		"the vector must have as many dimensions as the matrix has rows")
		return (VECTOR_NULL);
	result = Vector(matrix->cols, NULL);
	if (result.values == NULL)
		return (result);
	for (i = 0; i < matrix->rows; ++i)
	{
		tmp = vector->values[i];
		for (j = 0; j < matrix->cols; ++j)
		{
			result.values[j] += (tmp * matrix->values[i * matrix->cols + j]);
		}
	}
	return (result);
}
