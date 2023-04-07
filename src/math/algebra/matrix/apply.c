
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
