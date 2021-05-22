
#include "libccc/math/algebra.h"

#include LIBCONFIG_HANDLE_INCLUDE



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
